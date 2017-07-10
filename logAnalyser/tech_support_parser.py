#*******************************************************************************
# Author: Pruthwin Kadmaje Giridhara
#         pkadmaje@cisco.com
# Date: 06/20/2017 
#*******************************************************************************

import xml.etree.ElementTree

# Macros to define the different readtypes supported
READ_TECH_FULL = 0x00000001    # Try reading full file into buffer
READ_TECH_OFFSET = 0x00000002  # Read line with offset mentioned
READ_TECH_CHUNKS = 0x00000003  # Read in chunks


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

        try:
            self.conf = xml.etree.ElementTree.parse(self.confFile).getroot()
        except IOError:
            print "Error: can\'t find file <%s> or error in read data" %(self.confFile)
        else:    
            print "Read the conf file <%s> successfully" %(self.confFile)

        #self.tech = open(self.fileName, 'r')

    def __repr__(self):
        return '%s(%s, %s)' % (self.__class__.__name__, self.techFile, self.confFile)

    def getCliListFromConf(self):
        cliList = []
        for cli in self.conf.findall('cli'):
            #print cli.text
            cliList.append(cli.text)
        return cliList
            
    def getCliIdentifiersFromConf(self):
        cliIdentifiers = []
        for cliID in self.conf.findall('cli_identifiers'):
             cliIdentifiers.extend([d.strip(' \t\n\r') for d in cliID.text.split(",")])

        #print cliIdentifiers
        return ['`' + x for x in cliIdentifiers]


    def cliParser(self, cli):
        '''
            This function parses the data for the cli passed
        '''
        lineNum = 0
        cliData = []
        if self.cliLineOffsets.has_key(cli):
            lineNum = self.cliLineOffsets.get(cli)
        else:
            print "Cli cannot be found in the tech support file <%s>" %(self.techFile)
            return None

        for line in self.readlines[lineNum+1:]:
            if not any(c in line for c in self.getCliIdentifiersFromConf()):
                #print line
                cliData.append(line)
            else:
                break

        return cliData

    def readTechSupport(self, readType=READ_TECH_FULL, readAttr=None):
        print "Reading the tech support file <%s> ....." %(self.techFile)
        if readType is READ_TECH_FULL:                            
            with open(self.techFile, 'r') as techFp:
                self.readlines = techFp.readlines(0)
           
            # List compression with character '`' to match exactly
            tempCliList = ['`' + x + '`' for x in self.getCliListFromConf()]            
            for l, line in enumerate(self.readlines):
                if any(c in line for c in tempCliList):
                    key = next((s for s in self.getCliListFromConf() if s in line), None)
                    #print l, key
                    self.cliLineOffsets[key] = l


########################################
#   Test code
#######################################        
if __name__ == '__main__':        
    techParser = TechSupportParser('pruthwin_log', 'tech_support.xml')
    techParser.readTechSupport()
    print techParser.cliParser('show hardware internal tah l3 counter')


