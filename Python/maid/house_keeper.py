###############################################################################
#   File : house_keeper.py    
#   Author : Pruthwin Kadmaje Giridhara
#   Description : Does some of the house keeping jobs, maintain debugging 
#                 information, various utilities etc. 
###############################################################################
import yaml
import logging

class HouseKeeper(object):
    def __init__(self, confFile):	
        self.confFile = confFile
        with open(confFile, 'r') as ymlfile:
            self.maid_config = yaml.load(ymlfile)


        self.appName = self.maid_config['logger']['app_name']
        self.logger_loc = self.maid_config['logger']['log_loc']
        self.logger_lvl = self.maid_config['logger']['log_lvl']
        self.logger_en = self.maid_config['logger']['log_en']
        self.logLevels = {'dbg_all': logging.DEBUG,
                          'dbg_info': logging.INFO,
                          'dbg_warn' : logging.WARNING, 
                          'dbg_error': logging.ERROR, 
                          'dbg_critical': logging.CRITICAL}
        self.initLogger()

    def initLogger(self):
        # Logger support    
        self.logger = logging.getLogger(self.appName + 'logger')
        if self.maid_config['logger']['log_type'] == 'console':
            hdlr = logging.StreamHandler()
        else:
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


    def getMaidUserInfo(self):
        self.logger.info(self.maid_config['profile'])
