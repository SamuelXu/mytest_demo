#!env python
import socket
import sys

def help():
    print(" server_client.py client/server ip port filepath")

def tcplink(sock, addr, fp):
    print('Accept new connection from %s:%s...' % addr)
    data = sock.recv(1*1024*1024)
    while len(data) != 0:
        fp.write(data)
        data = sock.recv(1*1024*1024)
    sock.close()
    print('Connection from %s:%s closed.' % addr)

print(sys.argc)
if sys.argc != 5:
    help()
    sys.exit(0)

HOST = sys.argv[3]    # The remote host
PORT = sys.argv[4]              # The same port as used by the server

if "client" == sys.argv[1]:
    with open(sys.argv[5], "rb") as fp:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect((HOST, PORT))
            data = fp.read(1*1024*1024)
            s.sendall(data)
    s.close()
else:
    #create an INET, STREAMing socket
    serversocket = socket.socket(
                socket.AF_INET, socket.SOCK_STREAM)
    #bind the socket to a public host,
    # and a well-known port
    serversocket.bind((HOST, PORT))
    #become a server socket
    serversocket.listen(5)
    fp = open(sys.argv[5], "wb")
    while True:
        sock, addr = serversocket.accept()
        t = threading.Thread(target=tcplink, args=(sock, addr), fp)
        t.start()

