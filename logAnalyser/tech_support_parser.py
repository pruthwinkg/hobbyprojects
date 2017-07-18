#*******************************************************************************
# Author: Pruthwin Kadmaje Giridhara
#         pkadmaje@cisco.com
# Date: 06/20/2017 
#*******************************************************************************

from collections import *
import logging
import xml.etree.ElementTree

# Macros to define the different readtypes supported
READ_TECH_FULL = 0x00000001    # Try reading full file into buffer
READ_TECH_OFFSET = 0x00000002  # Read line with offset mentioned
READ_TECH_CHUNKS = 0x00000003  # Read in chunks


class StringTypes(object):
    '''
        Defines the various StringTypes supported for querying
    '''
    IPV4 = 0
    IPV6 = 1 
    MAC  = 2
    ADJ  = 3
    COUNTERS = 4 
    ERRORS = 5
    TRACES = 6

class ConfFileManager(object):
    def __init__(self, confFile):
        self.confFile = confFile
        try:
            self.conf = xml.etree.ElementTree.parse(self.confFile).getroot()
        except IOError:
            print "Error: can\'t find file <%s> or error in read data" %(self.confFile)
        else:    
            print "Read the conf file <%s> successfully" %(self.confFile)

        self.appName = self.getAppName()        
        self.getLoggerConfig()
        self.logLevels = {'dbg_all': logging.DEBUG,
                          'dbg_info': logging.INFO,
                          'dbg_warn' : logging.WARNING, 
                          'dbg_error': logging.ERROR, 
                          'dbg_critical': logging.CRITICAL}
        self.initLogger()
        cliConfig = namedtuple('cliConfig', 'name hdr_len')
        self.cliConfig = cliConfig

        self.getOutputConfig()
        self.initOutput()

    def initLogger(self):
        # Logger support    
        self.logger = logging.getLogger(self.appName + 'logger')
        hdlr = logging.FileHandler(self.logger_loc + self.appName + '.log', 'w')
        formatter = logging.Formatter('%(asctime)s %(levelname)s %(funcName)s [%(lineno)d]: %(message)s')
        hdlr.setFormatter(formatter)
        self.logger.addHandler(hdlr) 
        self.logger.setLevel(self.logLevels.get(self.logger_lvl, logging.ERROR))
        if self.logger_en == 'disable':
            self.logger.setLevel(logging.CRITICAL + 1)

        self.logger.info('Logger initialized successfully')
        self.logger.debug('Logger config: [en = %s, lvl = %s, loc = %s]' 
                %(self.logger_en, self.logger_lvl, self.logger_loc))

    def initOutput(self):
        '''
         The output uses the same logger infra to dump the output to a file
         The level is set to logging.INFO

         Example: self.output.info("Message.....")
        '''
        self.output = logging.getLogger(self.appName + 'output')
        if self.output_type == 'console':
            hdlr = logging.StreamHandler()
        else:
            hdlr = logging.FileHandler(self.output_loc, 'w')
        self.output.addHandler(hdlr)
        self.output.setLevel(logging.INFO)
        if self.output_en == 'disable':
            self.output.setLevel(logging.CRITICAL + 1)
                
        self.logger.info('Output initialized successfully')
        self.logger.info('Output config: [en = %s, type = %s, loc = %s]' 
                %(self.output_en, self.output_type, self.output_loc))
       

    def getAppName(self):
        appName = self.conf.find('appName')
        if appName is None:
            return 'tech_support'
        return appName.text

    def getCliConfig(self, cli=None):
        '''
            This function returns the cli config for the 'cli' passed.
            Else it turns, the configs for all the clis defined in the config file.
        '''
        cliConfigList = []
        
        for _cli in self.conf.findall('cli'):
            cliName = _cli.get('name')
            cliHdrLen = _cli.find('header_len').text
            cliConfigList.append(self.cliConfig(name=cliName, hdr_len=cliHdrLen))
            self.logger.debug("Name: " + cliName + " hdr: " + str(cliHdrLen))

        if cli == None:
            return cliConfigList
        else:
            for index, _cli in enumerate(cliConfigList):
                if cli == _cli.name:
                    return cliConfigList[index]
            return None                   
            
    def getCliIdentifiers(self):
        cliIdentifiers = []
        for cliID in self.conf.findall('cli_identifiers'):
             cliIdentifiers.extend([d.strip(' \t\n\r') for d in cliID.text.split(",")])
        return ['`' + x for x in cliIdentifiers]

    def getLoggerConfig(self):
        self.loggerRoot = self.conf.find('logger')        
        if self.loggerRoot.find('log_en') is not None:
            self.logger_en = self.loggerRoot.find('log_en').text.strip(' \t\n\r') 
        else:
            self.logger_en = 'disable'
        if self.loggerRoot.find('log_lvl') is not None:
            self.logger_lvl = self.loggerRoot.find('log_lvl').text.strip(' \t\n\r')
        else:
            self.logger_lvl = 'dbg_error'
        if self.loggerRoot.find('log_loc') is not None:
            self.logger_loc = self.loggerRoot.find('log_loc').text.strip(' \t\n\r')
        else:
            self.logger_loc = './' # Use same directory

    def getOutputConfig(self):
        self.outputRoot = self.conf.find('output')
        if self.outputRoot.find('out_en') is not None:
            self.output_en = self.outputRoot.find('out_en').text.strip(' \t\n\r')
        else:
            self.output_en = 'disable'
        if self.outputRoot.find('out_type') is not None:
            self.output_type = self.outputRoot.find('out_type').text.strip(' \t\n\r')
        else:
            self.output_type = 'file' # By default use file type for the output
        if self.outputRoot.find('out_loc') is not None:
            self.output_loc = self.outputRoot.find('out_loc').text.strip(' \t\n\r')
        else:
            self.output_loc = './tech.out' # Use same directory
           

class TechSupportParser(object):
    '''
        This class helps to parse the tech support logs and stores in 
        structred format for further usage
    '''
    def __init__(self, techFile, confFile):
        self.techFile = techFile
        self.confFile = confFile

        self.readlines = []
        self.cliLineOffsets = {} # Dictionary of {cli:LineNum} for faster access

        self.config = ConfFileManager(self.confFile)
        self.readTechSupport()

    def __repr__(self):
        return '%s(%s, %s)' % (self.__class__.__name__, self.techFile, self.confFile)

    def cliParser(self, cli):
        '''
            This function parses the data for the cli passed
        '''
        lineNum = 0
        cliData = []
        if self.cliLineOffsets.has_key(cli):
            lineNum = self.cliLineOffsets.get(cli)
        else:
            self.config.logger.error("Cli: [%s] cannot be found in the tech support file <%s>" 
                            %(cli, self.techFile))
            return None

        for line in self.readlines[lineNum+1:]:
            if not any(c in line for c in self.config.getCliIdentifiers()):
                line = line.strip('\n')
                self.config.logger.debug(line)
                cliData.append(line)
            else:
                break

        return cliData

    def getDataSummary(self, string, stringType=None):
        '''
            Given a string, it searches for all the instances of occurances of that string
            and gives a meaningful data related to the string passed.

            If the stringType is passed, the search will be more methodical.

            Example: <IP address>
                    Gets all the v4/v6 LPM/Host data and logs related to the IP string passed

           Note: To get a better output, the config file should contain enough metdata for all
                 clis.
        '''
        cliLineSortedList = sorted(self.cliLineOffsets.values())
        self.config.logger.debug(cliLineSortedList)
        if stringType is None:
            for lineNum, line in enumerate(self.readlines):
                if string in line:
                    self.config.logger.debug('%s : %d' %(line, lineNum))
                    sIdx = self._findSmallerNumber(cliLineSortedList, lineNum)
                    _cli = self.cliLineOffsets.keys()[self.cliLineOffsets.values().index(sIdx)]
                    eIdx = sIdx + int(self.config.getCliConfig(_cli).hdr_len)
                    self.config.logger.debug('sIdx: %d, eIdx: %d' %(sIdx, eIdx))

                    # print the cli, header and message
                    self.config.output.info(_cli)
                    for hdr in self.readlines[sIdx+1:eIdx+1]:
                        self.config.output.info(hdr.strip("\n"))                
                    self.config.output.info(line + "\n") 

    def readTechSupport(self, readType=READ_TECH_FULL, readAttr=None):
        print("Reading the tech support file <%s> ....." %(self.techFile))
        if readType is READ_TECH_FULL:                            
            with open(self.techFile, 'r') as techFp:
                self.readlines = techFp.readlines(0)
           
            # List compression with character '`' to match exactly
            tempCliList = ['`' + x.name + '`' for x in self.config.getCliConfig()]            
            for l, line in enumerate(self.readlines):
                if any(c in line for c in tempCliList):
                    key = next((s.name for s in self.config.getCliConfig() if s.name in line), None)
                    self.config.logger.debug('%s : %d' %(key, l))
                    self.cliLineOffsets[key] = l

        self.config.logger.info("Read the tech support file <%s> successfully" %(self.techFile))

    ########################################
    #      Bunch of helper functions
    ########################################
    def _findSmallerNumber(self, numList, num):
        '''
            Returns n from numList such that n is just smaller than num
        '''
        numList = sorted(numList)
        prevN = 0
        for n in numList:
            if num > n:
                prevN = n
            else:
                break        
        return prevN


