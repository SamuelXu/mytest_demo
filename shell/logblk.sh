#!/bin/sh

for f in ./blk_*;do
    [[ -f $f ]] || continue
	name=`basename $f`
	name=${name%.log}
	addr=`echo $name | cut -d_ -f2`
	num=`echo $name | cut -d_ -f3`
	a=0;b=0;c=0;d=0;
	cat $f | while read line
	do
		if [[ $line =~ a: ]];then
			a=`echo $line|cut -d: -f2`
		fi
		if [[ $line =~ b: ]];then
			b=`echo $line|cut -d: -f2`
		fi
		if [[ $line =~ d: ]];then
			d=`echo $line|cut -d, -f1|cut -d: -f2`
			echo "$addr,$num,$a,$b,$d" >> aa
		fi
	done
done

