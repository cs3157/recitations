#!/bin/bash

# seq command gives a range of numbers
for number in $(seq 1 10); do
    echo "number $number"
done

# a fake version of ls
for file in $(ls -a); do
    echo "file: $file"
done
