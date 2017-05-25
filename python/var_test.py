#!/usr/local/bin/python3
import sys

if 1==int(sys.argv[1]):
    a=5
    b="qwe"
    c=[1,2,3]
elif 2==int(sys.argv[1]):
    a=6
    b="asd"
    c=[2,3,4]
else:
    a=7
    b="zxc"
    c=[3,4,5]

print((a,b,c))

print(1==int("1"))
