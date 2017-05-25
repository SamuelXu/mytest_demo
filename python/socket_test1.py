import socket

HOST = 'ip'    # The remote host
PORT = 18080              # The same port as used by the server
i = 0
while True:
    if i < 1000:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((HOST, PORT))
        s.sendall('Hello, world')
        data = s.recv(1024)
        print data
        i = i + 1
        usleep 
s.close()
