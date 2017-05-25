#!/usr/bin/python
#coding=utf-8

import sys,os,re,threading,pexpect
import time,datetime
from pexpect import *

def cptoend(child, ip, passwd, file_mid, file_end):
	child.sendline("scp  " + file_mid + " root@" + ip + ":" + file_end)
	child.expect(["(?i)password"])
	child.sendline(passwd)
	child.expect(["(?i)#", pexpect.EOF, pexpect.TIMEOUT])

	#change own & change mod
	child.sendline("./k " + ip);
	child.expect(["(?i)#", pexpect.EOF, pexpect.TIMEOUT])
	child.sendline("chown www:www " + file_end)
	child.expect(["(?i)#", pexpect.EOF, pexpect.TIMEOUT])
	child.sendline("chmod 444 " + file_end)
	child.expect(["(?i)#", pexpect.EOF, pexpect.TIMEOUT])

	#exit
	child.sendline("exit")
	child.expect(["(?i)#", pexpect.EOF, pexpect.TIMEOUT])

def cpone(localpath, path_mid, zipname, file_end, serverlist):
	cmd = "scp " + localpath + " root@" + ip_mid + ":" + path_mid + zipname
	child = pexpect.spawn(cmd)
	child.logfile = sys.stdout
	child.expect(["(?i)password"])
	child.sendline(pass_mid)
	child.expect([pexpect.EOF], timeout=3600)
	child.close(force=True)

	cmd = "ssh root@" + ip_mid
	child = pexpect.spawn(cmd)
	child.logfile = sys.stdout
	child.expect(["(?i)password"])
	child.sendline(pass_mid)
	index = child.expect(["(?i)#", pexpect.EOF, pexpect.TIMEOUT])
	if index != 0:
		print 'ssh fail 1'
		child.close(force=True)
		return 3

	for server in serverlist:
		cptoend(child, server[0], server[1], path_mid + zipname, file_end);

	child.sendline("exit")
	child.expect(["(?i)#", pexpect.EOF, pexpect.TIMEOUT])
	child.close(force=True)

serverlist=[["ip", "pass"]]
ip_mid=''
pass_mid=''
path_mid="/aa/"
path_end="/bb/"
cpone(sys.argv[1], path_mid, sys.argv[2], path_end + sys.argv[2], serverlist)

