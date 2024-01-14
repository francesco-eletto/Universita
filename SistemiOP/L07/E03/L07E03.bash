#!/bin/bash

for file in $(ls $1); do
    tmp=$(echo "$file" | tr '[:upper:]' '[:lower:]')
    mv "$file" "$tmp"
done

