'''
Common code responsible for
 - Reading the config file and generating config objects
'''

import configparser
import logging

PREDEFINED_CONFIG_KEYS={
    "device" : ['type', 'firmware', 'logging'], 
    "scale" : ['instances'],
    }

class VDConfigManager():
    def __init__(self, configFile):
        self.config = configparser.ConfigParser()
        self.configFile = configFile
        self.read_configFile(configFile)
        
        logging.debug(f"Config sections for {configFile} = {self.config.sections()}")    
        if not self.validate():
            raise Exception(f"Bad config file {configFile}") 
        
    def read_configFile(self, configFile):
        try:
            with open(configFile) as fp:                
                self.config.read_file(fp)
                self.configFp = fp
        except:
            raise FileNotFoundError(f"Cannot find the file {configFile}")       

    def get_config(self):
        self.read_configFile(self.configFile)
        config_object = {}
        for section in self.config.sections():
            config_object[section] = {}
            for key, value in self.config.items(section):
                   config_object[section][key] = value

        return config_object

    # This will modify the <device>.config file directly
    def set_config(self, new_config):
        try:
            for section, options in new_config.items():
                if not self.config.has_section(section):
                    self.config.add_section(section)
                for key, value in options.items():
                    self.config.set(section, key, value)

            with open(self.configFile, 'w') as configfile:
                self.config.write(configfile)
        except:
            raise FileNotFoundError(f"Cannot find the file {self.configFile}")

    # This generates a instance specific config by blending global + local
    def modify_config(self, global_config, local_config):
        pass

    def validate(self):
        all_sections_valid = all(key in PREDEFINED_CONFIG_KEYS for key in self.config.sections())

        for section in self.config.sections():
            for key, value in self.config.items(section):
                if key not in PREDEFINED_CONFIG_KEYS.get(section, []):
                    logging.error(f"Invalid key '{key}' in section '{section}'")
                    return False   

        return all_sections_valid
        