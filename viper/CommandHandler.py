"""
CommandHandler.py
@author:Abhishek Jha
execute linux commands and handle output and error pipes
"""

import os
import subprocess
import shlex


class CommandHandler:

    # TODO : add logging support

    """
    constructor
    @params: log_file -> log file handler
             logging  -> Boolean to allow logging in log file
    """

    def __init__(self, log_file=None, logging=False):
        self.log = log_file
        self.logging = logging

    """
       function to execute the command
       @params: command -> command to be executed
    """

    def execute(self, command):
        # split the command into args
        args = shlex.split(command)
        try:
            out, err = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
            if err:
                return False, err
            return True, out
        except Exception as e:
            print(e)
            return False, None

    # function to extract pid of an open port
    def extract_info(self, port):
        cmd = 'lsof -i :{}'.format(port)
        done, res = self.execute(cmd)
        if done:
            # extract_pid and service information
            res = str(res)
            res = res.split('\\n')[1].split(' ')
            service, pid, user = (res[0], res[2], res[3])
            return service, pid, user
        return None

    # function to kill a process
    def kill(self,port):
        pid = port[1]
        try:
            cmd = 'kill -9 {}'.format(pid)
            done,res = self.execute(cmd)
            # if done:
                # print("port poisoned : {}".format(port[0]))
        except Exception as e:
            print(e)







