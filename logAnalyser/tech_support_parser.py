#*******************************************************************************
# Author: Pruthwin Kadmaje Giridhara
#         pkadmaje@cisco.com
# Date: 06/20/2017 
#*******************************************************************************

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

    def initLogger(self):
        # Logger support    
        self.logger = logging.getLogger(self.appName)
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
        
    def getAppName(self):
        appName = self.conf.find('appName')
        if appName is None:
            return 'tech_support'
        return appName.text

    def getCliList(self):
        cliList = []
        for cli in self.conf.findall('cli'):
            self.logger.debug(cli.text)
            cliList.append(cli.text)
        return cliList
            
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
            self.config.logger.error("Cli cannot be found in the tech support file <%s>" %(self.techFile))
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
        if stringType is None:
            for lineNum, line in enumerate(self.readlines):
                if string in line:
                    self.config.logger.debug('%s : %d' %(line, lineNum))
                    key = self._findSmallerNumber(cliLineSortedList, lineNum)
                    print self.cliLineOffsets.keys()[self.cliLineOffsets.values().index(key)]
                
        

    def readTechSupport(self, readType=READ_TECH_FULL, readAttr=None):
        print("Reading the tech support file <%s> ....." %(self.techFile))
        if readType is READ_TECH_FULL:                            
            with open(self.techFile, 'r') as techFp:
                self.readlines = techFp.readlines(0)
           
            # List compression with character '`' to match exactly
            tempCliList = ['`' + x + '`' for x in self.config.getCliList()]            
            for l, line in enumerate(self.readlines):
                if any(c in line for c in tempCliList):
                    key = next((s for s in self.config.getCliList() if s in line), None)
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

########################################
#   Test code
#######################################        
if __name__ == '__main__':        
    techParser = TechSupportParser('pruthwin_log', 'tech_support.xml')
    techParser.cliParser('show hardware internal tah l3 counter')
    techParser.getDataSummary("20.0.137.27")

