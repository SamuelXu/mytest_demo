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


TIMES=10
TIMES=${TIMES:-1000}
WHEN=${@:-2358 2359 0000 0001 0002}

echo $TIMES

for i in $WHEN;do
        echo $i
done

min=50
for i in {10..100..10};do
        echo $i;
done

i=0
while true;do
    echo $i
    ((i = (i + 10) / 2 + 2))
    echo $((i / 500 * 500))
    if [ $i -gt 10 -o $i -eq 10 ];then
        break
    fi
done

#compare float
a=15
#if [ "$(expr $a '>' 5.2)" -eq 1 ];then
#when compare float use expr is wrong,should like below
if [ "$(echo $a '>' 5|bc -l)" -eq 1 ];then
    echo $a
fi

i=50
j=0
k=100
step=5
while true;do
    echo $i,$j,$k
    if [ $i -eq $k -o $i -eq $j ];then
        break
    fi
    if [ $i -gt 61 ];then
        k=$i
        ((i = (i + j) / 2 / step * step))
    else
        j=$i
        ((i = (i + k) / 2 / step * step))
    fi
done

