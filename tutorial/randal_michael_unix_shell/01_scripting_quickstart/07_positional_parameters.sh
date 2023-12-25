#!/bin/bash

# $0                            is the actual command
# $1 $2 .. $9 ${10} ${11}..     are positional parameters
# $1 $2 .. $9 ${10} ${11}..     in a function are function arguments


# Call this script with 10 parameters as:
# script 1 2 3 40 50 60 700 800 9000 10000

for i in $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10}   # for > $9 {brakets} are necessary
do
    if [ -n "$i" ]
    then
        echo -n "$i "
    fi
done


function f
{
    echo -e "\nf arguments"
    for i in $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10}
    do
        if [ -n "$i" ]
        then
            echo -n "$i "
        fi
    done

}

f 0.1 0.2 0.3 4 5 6 70 80 90 100

echo -e ""
