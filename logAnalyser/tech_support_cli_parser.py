#*******************************************************************************
# Author: Pruthwin Kadmaje Giridhara
#         pkadmaje@cisco.com
# Date: 07/17/2017
#*******************************************************************************

class TechCliParser(object):
    '''
        This class is used to parse the clis in a very specific way.
        User needs to implement the methods for all the clis which needs special
        attention while parsing and display the output

        This class does not have it own logging/file reading mechanism.
        The TechSupportParser class object needs to be passes to this for
        logging/reading/output to work properly.        
    '''
    def __init__(self, techObj):        
        if not isinstance(techObj, TechSupportParser):                
            raise Exception( "Not a valid class object")
            
        self.inputdata = techObj.inputdata
        self.logger = techObj.config.logger
        self.output = techObj.config.output

