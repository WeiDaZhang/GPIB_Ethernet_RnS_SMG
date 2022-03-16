"""
Try to connect to GPIB-ETHERNET (the adapter)
Performed on 2022 Mar 15
"""

import socket as skt
import time
import math
import os
# import numpy as np
# import numpy.lib.recfunctions as rfn
# import matplotlib
# import matplotlib.pyplot as plt

HOST = '192.168.1.32'
PORT = 1234

def connect():

    s = skt.socket()
    s.settimeout(5)
    try:
        s.connect((HOST,PORT))
        s.send(b'++savecfg 0\n')
        s.send(b'++addr 28\n')
        s.send(b'++auto 0\n')
        s.send(b'++ver\n')
        try:
            print(s.recv(1024))
            s.send(b'*IDN?\n')
            s.send(b'++read EOI\n')
            try:
                print(s.recv(1024))
                s.send(b'RF?\n')
                s.send(b'++read EOI\n')
                try:
                    print(s.recv(1024))
                    s.send(b'LEVEL?\n')
                    s.send(b'++read EOI\n')
                    try:
                        print(s.recv(1024))
                        s.send(b'LEVEL:OFF\n')
                        s.send(b'RF:START 10KHZ\n')
                        s.send(b'RF:STOP 62MHZ\n')
                        s.send(b'RF:STEP 200KHZ\n')
                        s.send(b'TIME:RF_SWP 50MS\n')
                        s.send(b'SWP:AUTO\n')
                        s.send(b'LEVEL:ON\n')
                    except skt.timeout:
                        print('Reading RF Output LEVEL Failed!')
                except skt.timeout:
                    print('Inquiring RF parameter Failed!')
            except skt.timeout:
                print('Reading GPIB Instrument Version Failed!')
        except skt.timeout:
            print('Reading GPIB-ETHERNET Module Version Failed!')
    except skt.timeout:
        print('GPIB-ETHERNET Module Network Error!')

    # rm = pyvisa.ResourceManager()
    # print('List GPIB Instruments:')
    # instru_tuple = rm.list_resources()
    # print('\t' + str(instru_tuple))
    # for idx in range(len(instru_tuple)):
        # try:
            # instru = rm.open_resource(str(instru_tuple[idx]))
            # instru_str = instru.query('*IDN?')
            # print('Instrument IDN of ' + str(instru_tuple[idx]) + ' is ' + instru_str)
        # except:
            # print('Error found when inquiring ' + str(instru_tuple[idx]))

def main():
    connect()
        

if __name__ == '__main__':
    main()
