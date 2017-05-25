#!env python

import threading

t = 0
n = 0
def hello():
    print "hello world!"
    global t
    global n
    n+=1
    t = threading.Timer(2, hello)
    t.start()
    if n==10:
        goodbye()

def goodbye():
    print "goodbye world!"
    global t
    t.cancel()

hello()
