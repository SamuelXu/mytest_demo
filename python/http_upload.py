#!env python

import urllib2
import mmap

f = open(argv[1], 'rb')
mmaped_file = mmap.mmap(f.fileno(), 0, access = mmap.ACCESS_READ)

request = urllib2.Request(url, mmaped_file)
request.add_header("Content-Type", "text/plain")
response = urllib2.urlopen(request)

mmaped_file.close()
f.close()

