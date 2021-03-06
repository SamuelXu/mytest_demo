#!/bin/sh

# Setup variables
EXEC=/usr/bin/jsvc
JAVA_HOME=/usr/lib/jvm/java-1.8.0
CLASS_PATH="/home/samuel/test/commons-daemon-1.0.15.jar":"/home/samuel/test/example.jar"
CLASS=example.Main
USER=root
PID=/tmp/example.pid
LOG_OUT=/tmp/example.out
LOG_ERR=/tmp/example.err

do_exec()
{
	$EXEC -home "$JAVA_HOME" -cp $CLASS_PATH -user $USER -outfile $LOG_OUT -errfile $LOG_ERR -pidfile $PID $1 $CLASS
}

case "$1" in
	start)
		do_exec
		;;
	stop)
		do_exec "-stop"
		;;
	restart)
		if [ -f "$PID" ]; then
			do_exec "-stop"
			do_exec
		else
			echo "service not running, will do nothing"
			exit 1
		fi
		;;
	*)
		echo "usage: daemon {start|stop|restart}" >&2
		exit 3
		;;
esac

