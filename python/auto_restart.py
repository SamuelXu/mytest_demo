#!/usr/bin/python

import os, sys, time

def main():
    print "auto restart service..."
    executable = sys.executable
    print executable
    args = sys.argv[:]
    print args
    args.insert(0, sys.executable)
    print args

    time.sleep(2)
    print os.path.dirname(os.path.realpath(__file__))
    print "respawning"
    os.execvp(executable, args)


if __name__ == "__main__":
    main()
