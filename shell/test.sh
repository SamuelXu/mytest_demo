#!/bin/sh

#if test x$USER = x"root";then
#    echo "not root"
#else
#    echo $USER
#fi

#[ -n "$BASH_VERSION" ] || {
#    echo "not bash"
#    exit 1
#}
#
#echo "bash"
#
#mongod=${MONGOD-/usr/local/mongo/bin/mongod}
#
#echo $mongod

ldisk=`df -l -P | grep "/" | sort -n -k4,4 -r | grep -vE "none|udev|tmpfs|none|boot" `
DumpDir="/usr/local/DBCache/"
echo $ldisk | while read p;do
dir=`echo $p | awk '{print $NF}'`;
[ -w $dir ] || continue;
if [ "X/" = "X$dir" ];then
    break;
else 
    DumpDir=$dir"/DBCache/"
    break;
fi
done
echo $DumpDir
