#*******************************************************************************
# Author: Pruthwin Kadmaje Giridhara
#         pkadmaje@cisco.com
# Date: 06/20/2017 
#*******************************************************************************
from tech_support_parser import *
from tech_support_cli_parser import *

'''
    This file is the front end of the logAnalyzer application.
    It supports:
        - tech support file parsing and analysis
        - elam data parsing and analysis (TODO)
'''


techParser = TechSupportParser('pruthwin_log', 'tech_support.xml')
techParser.cliParser('show hardware internal tah l3 counter')
techParser.getDataSummary("20.0.137.27")
techParser.getDataSummary("130.0.29.64/28")
