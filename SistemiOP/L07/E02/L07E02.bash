#!/bin/bash

maxLen=0
i=0
y=0

for line in $(cat "$1"); 
do
    len=${#line}
    if [ $len -gt $maxLen ]; then
        maxLen="$len"
        y="$i"
    fi
    i=$[$i+1]
done

echo "$y $maxLen $(wc $1 -l)"
