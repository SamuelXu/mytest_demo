#!env python

import socket
import sys

HOST = 'ip'    # The remote host
PORT = 50007              # The same port as used by the server
s = None
for res in socket.getaddrinfo(HOST, PORT, socket.AF_UNSPEC, socket.SOCK_STREAM):
    af, socktype, proto, canonname, sa = res
    try:
        s = socket.socket(af, socktype, proto)
    except socket.error as msg:
        s = None
        continue
    try:
        s.connect(sa)
    except socket.error as msg:
        s.close()
        s = None
        continue
    break
if s is None:
    print 'could not open socket'
    sys.exit(1)
s.sendall('Hello, world')

s.settimeout(5)
data = ""
while len(data)<10 :
    try:
        data = s.recv(1024)
        data += data
        print data
    except socket.error, e:
        print "error occur:"+e
s.close()
print 'Received', repr(data)
