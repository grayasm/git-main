#!/bin/bash

# The shift command is used to move positional parameters > $0 to the left;
# $2 becomes $1 and previous $1 is discarded
# shift 3 moves $4 to $1 and previous $1 $2 $3 are discarded

# Test this script with few parameters

while [ -n "$1" ]           # -n true if the length of "string" is non-zero
do
    echo "\$1=$1"           # display 1st positional parameter $1
    shift                   # move all positional parameters one to the left
done
