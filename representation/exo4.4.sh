#! /bin/bash

tmpbar=`mktemp`
i=0
while read region couleur
do
    i=`expr $i + 1`
    ./statsreg images/atlas.inr.gz -c $couleur > $tmpbar
    xatlas[$i]=`cut -f1 $tmpbar`
    yatlas[$i]=`cut -f2 $tmpbar`
#   satlas[$i]=`cut -f3 $tmpbar`
    name[$i]=$region
done < atlas.txt

for j in `seq 5`
do
    ./statsreg region$j.inr > $tmpbar
    x=`cut -f1 $tmpbar`
    y=`cut -f2 $tmpbar`
    s=`cut -f3 $tmpbar`
    min=1000000000000000000
    r=-1
    for k in `seq $i`
    do
	dx=`expr ${xatlas[$k]} - $x`
	dy=`expr ${yatlas[$k]} - $y`
#	ds=`expr ${satlas[$k]} - $s`
	d2=`expr $dx \* $dx + $dy \* $dy`

	if [[ $min -gt $d2 ]]
	then
	    r=$k
	    min=$d2
	fi
    done
    if [[ $r -ne -1 ]]
    then
	cp region$j.inr ${name[$r]}.inr
	echo "region$j.inr copié dans ${name[$r]}.inr"
    fi
done

rm -f $tmpbar
