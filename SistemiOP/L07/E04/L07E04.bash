#!/bin/bash

i=0
n=0

for word in $(cat $1); do
    
    flag=0
    i=0
    while [ $i -lt $n ]; do
    if  [ "$word" = "${wordArrey[$i]}" ]; then
        wordNum[$i]=$[${wordNum[$i]}+1]
        flag=1
    fi
    i=$[$i+1]
    done
    if [ $flag -eq 0 ]; then
        wordArrey[$(($n))]="$word"
        wordNum[$n]=1
        n=$[$n+1]
    fi

done

for (( j=0; j<${#wordArrey[*]}; j++ )); do
    echo "${wordArrey[$j]} ${wordNum[$j]}"
done

