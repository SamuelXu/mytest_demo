#!env python

import threading
import time

class timer(threading.Thread):
    def __init__(self, threadname):
        super(timer, self).__init__(name = threadname)
        self.is_cancel = False

    def run(self):
        while True:
            if self.is_cancel:
                break;
            else:
                time.sleep(2)
                print "do work"

    def stop(self):
        self.is_cancel = True

t = timer("thread-timer")
t.start()
time.sleep(10)
t.stop()
print "stopped"
