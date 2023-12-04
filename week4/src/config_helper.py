import os
import json
import subprocess

def run_config(exec_name, config_name):

    subprocess.run([exec_name, get_config_path(config_name)]) # TODO: popen 

def get_config_path(config_name):

    CONFIG_DIR = './configs'

    if not os.path.exists(CONFIG_DIR):

        os.mkdir(CONFIG_DIR)
    
    return os.path.join(CONFIG_DIR, config_name + '.json')

def create_config(config_dict, config_name):

    path_to_config = get_config_path(config_name)
    
    with open(path_to_config, 'w') as file:

        file.write(json.dumps(config_dict))

class Config:

    def __init__(self, name, dict):

        self.name = name
        self.dict = dict

    def __getitem__(self, key):

        return self.dict[key]

    def __setitem__(self, key, value):

        self.dict[key] = value
    
    def write(self):

        create_config(self.dict, self.name)
