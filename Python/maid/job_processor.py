###############################################################################
#   File : job_processor.py
#   Author : Pruthwin Kadmaje Giridhara 
#   Description : The main module of maid. Processes the jobs sent by the 
#               the job_requestor module 
###############################################################################
from house_keeper import *
import os
import subprocess

class MaidJobPriority(object):
    JOB_PRIO_HIGH = 0xFF
    JOB_PRIO_IMMEDIATE = 0xAA
    JOB_PRIO_LOW  = 0x00

class MaidJobMsg(MaidJobPriority):
    '''
        Defines the maid job message
    ''' 
    def __init__(self, job=None, job_id=0, job_priority=MaidJobPriority.JOB_PRIO_IMMEDIATE, shellJob=True):
        self.job_id = job_id
        self.job_priority = job_priority
        self.job = job
        self.shell = shellJob

    def set_job_priority(self):
        self.job_priority = job_priority

    def set_job_id(self):
        self.job_id = job_id

    def get_job_priority(self):
        return self.job_priority

    def get_job_id(self):
        return self.job_id

    def print_job_info(self, loggerObj):
        loggerObj.info("Job ID : %d" %self.job_id)
        loggerObj.info("Job Priority : %d" %self.job_priority)
        loggerObj.info("Job : %s" %self.job)

class MaidJobProcessor(object):
    '''
        Main class which is responsible for accepting jobs and processing it
    '''
    def __init__(self, config):
        self.maid_housekeeper_obj = HouseKeeper(config)
        self.maidLogger = self.maid_housekeeper_obj.logger
        self.maidLogger.info("Starting Maid....")
        self.maid_housekeeper_obj.getMaidUserInfo()

    def executeMaidJob(self, maidJobObj):
        maidJobObj.print_job_info(self.maidLogger)
        if maidJobObj.job_priority == MaidJobPriority.JOB_PRIO_IMMEDIATE:
           subprocess.call(maidJobObj.job, shell=maidJobObj.shell)

    def getNextMaidJob(self):
        pass
        
