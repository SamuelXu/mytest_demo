#!/bin/sh

C=300000000

while read f
do
    if [ $f = "end" ];then break;fi
    y=`echo "scale=6;1000.0*$C/$f" | bc`
    echo $f,$y
done
