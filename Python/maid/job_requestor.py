###############################################################################
#   File : job_processor.py
#   Author : Pruthwin Kadmaje Giridhara 
#   Description : The main module of maid. Processes the jobs sent by the 
#               the job_requestor module 
###############################################################################
from house_keeper import  *
from job_processor import *


class MaidJobRequestor(object):
    def __init__(self, config):
        self.maidObj = MaidJobProcessor(config) 


    def sendEmailNotification(self, message, profile_id=1):
         pass

    def startMaidShell(self):
        pass

    def sendImmediateMaidJob(self, job):
        maidMsgObj = MaidJobMsg(job)
        self.maidObj.executeMaidJob(maidMsgObj)


if __name__ == '__main__':
   #prompt = logPrompt()
   #prompt.Prompt = '>'
   #prompt.cmdloop('Starting logAnalyser....')
    maidUI = MaidJobRequestor('maid.yaml')
    maidUI.sendImmediateMaidJob('ls -al')
    maidUI.sendImmediateMaidJob('echo "Hello World"')
    maidUI.sendImmediateMaidJob('date')
