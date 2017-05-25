#!env python

import os
import time

time.sleep(1)
os.rename(__file__, __file__+".1")
time.sleep(1)
