#!env python

import thread, time, random

count = 0

#如果不加lock则会出现多个线程同时操作共享变量资源，导致数据不同步
lock = thread.allocate_lock()

def threadtest():
    global count, lock
    lock.acquire()
    for i in xrange(1000):
        count += 1
    lock.release()

for i in range(10):
    thread.start_new_thread(threadtest, ())

time.sleep(3)
print count

#thread.start_new_thread(lambda : (thread.interrupt_main(), ), () )
#try:
#    time.sleep(2)
#except KeyboardInterrupt, e:
#    print 'error:', e
#print 'over'
