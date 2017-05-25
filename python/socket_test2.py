#!env python

import socket
import sys

#create an INET, STREAMing socket
serversocket = socket.socket(
            socket.AF_INET, socket.SOCK_STREAM)
#bind the socket to a public host,
# and a well-known port
serversocket.bind((192.168.8.1, 8000))
#become a server socket
serversocket.listen(5)

