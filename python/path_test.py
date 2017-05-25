#!env python

import os
import sys

path = sys.argv[1]

if os.path.isdir(path):
    print path, "is exist"
elif path[-1] == "/" or path[-1] == "\\":
    os.makedirs(path)
    print path, "created"
else:
    print "file", path
