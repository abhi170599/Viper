"""
PortScanner.py
@author:Abhishek Jha
scan through open ports
"""

import threading
import socket
import CommandHandler


class PortScanner:
    # TODO: Add logging support

    """
    constructor
    @params:
    search -> To search a given range of ports
    lower  -> lower bound of range
    upper  -> upper bound of range
    filter -> type of service (python,node,go etc)
    """

    def __init__(self, host="0.0.0.0", remote=False, lower=1, upper=65432, service_filter=None,logfile=None,logging=False):
        self.host = host
        self.remote = remote
        self.lower = lower
        self.upper = upper
        self.service_filter = service_filter
        self.ch = CommandHandler.CommandHandler()

    # function to get the open ports
    def scan(self):
        ports = self.scan_range()
        return ports

    # scan a given range for open ports in a thread
    def scan_job(self, range_port, ports, i):
        print("Running thread : {}".format(i+1))
        try:
            for port in range(range_port[0], range_port[1]):
                sock = socket.socket(socket.AF_INET,
                                     socket.SOCK_STREAM)
                result = sock.connect_ex((self.host, port))
                if result == 0:
                    # retrieve port information
                    port_info = self.ch.extract_info(port)
                    if port_info is not None:
                        if self.service_filter is not None and port_info[0] not in self.service_filter:
                            continue
                        ports.append(port_info)
                sock.close()
        except Exception as e:
            print(e)

    # function to scan ports by concurrent exhaustive scan
    def scan_range(self, ports_per_thread=1000):
        num_threads = (self.upper - self.lower) // ports_per_thread
        ranges = []
        thread_ports = [[] for i in range(num_threads)]
        ports = []
        for i in range(num_threads):
            range_thread = (self.lower + (i * ports_per_thread),
                            min(self.upper, self.lower + (i + 1) * ports_per_thread))
            ranges.append(range_thread)

        threads = [threading.Thread(target=self.scan_job, args=(ranges[i], ports, i,))
                   for i in range(num_threads)]
        for thread in threads:
            thread.start()

        # wait for threads to complete scanning
        for thread in threads:
            thread.join()

        return ports


