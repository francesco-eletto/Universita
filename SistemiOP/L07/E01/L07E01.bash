#!/usr/bin/bash

list=$(find "$1" -name "*.c" -readable)
for i in $list; do
    tmp=$(cat "$i" | grep -e "\<$2(" | wc -l)

    if [ $tmp -gt 0 ] ; then
        echo "$i"
        echo "$(grep "$i" -e "\<$2(" -n)"
        echo ""

    fi
done

