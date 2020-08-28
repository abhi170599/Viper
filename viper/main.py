# !/usr/bin/env python
# -*- coding: utf-8 -*-

"""
main.py
@author:Abhishek Jha
Starting a daemon to periodically scan and kill ports
"""

from datetime import datetime
import time

from PortScanner import PortScanner
from CommandHandler import CommandHandler
from Daemon import Daemon


# daemon class
class Viper():
    # TODO : Add Hidden and Secure Logging for remote monitoring
    """
    constructor
    @params:
    service_filter -> services to be poisoned

    """

    def __init__(self, period=5, logging=False, log_file=None, service_filter=None):

        # initialize resources
        self.period = period
        self.logfile = log_file
        self.log = None
        self.logging = logging
        self.command = CommandHandler(log_file=self.logfile, logging=logging)
        self.port_scanner = PortScanner(lower=1200, upper=9000, service_filter=service_filter)

    def run(self):

        if self.logging:
            self.log = open(self.logfile, 'a+')

        if self.logging:
            log = "-------------------------------------------------" \
                  + "\nStarting Port scan at {}\n".format(datetime.now()) \
                  + "------------------------------------------------"
            self.log.write(log + "\n")

        # scan for ports
        print("starting port scan")
        ports = self.port_scanner.scan()
        print(ports)

        # kill the ports
        for port in ports:
            self.command.kill(port)
            if self.logging:
                log = "Poisoned port : {},{},{}".format(port[0], port[1], port[2])
                self.log.write(log + "\n")

        if self.logging:
            self.log.close()


if __name__ == "__main__":
    # register self into startup services

    app = Viper(service_filter=["server", "python"], log_file="viper.log", logging=False)
    app.run()
