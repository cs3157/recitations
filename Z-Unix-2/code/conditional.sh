#!/bin/bash

n=$(cat dogs.sh | wc -l)
if [ $n -eq 9 ]; then
    echo "Same number of lines"
else
    echo "Somebody changed the file"
fi

read -p "Enter a string: " str
if [ -z $str ]; then
    echo "You didn't enter anything"
    exit 1
fi
if [ $str == "hi" ]; then
    echo "Greetings"
fi
