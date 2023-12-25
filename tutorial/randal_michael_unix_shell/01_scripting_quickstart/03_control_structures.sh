#!/bin/bash

# I've found this tldp.org website where Bash is explained for beginners
# for if [ TEST-COMMAND ] see:
# https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_07_01.html
# for loops see:
# https://tldp.org/LDP/abs/html/loops1.html
# for case see:
# https://tldp.org/LDP/abs/html/testbranch.html


# if...then statement
if [ -d /tmp ]
then
    echo "echo from if"
fi


# if...then...else statement
if [ ! -d /tmp ]
then
    echo "echo from if"
else
    echo "echo from else"
fi


# if...then...elif...(else) statement
if [ ! -d /tmp ]
then
    echo "echo from if"
elif [ -d /home ]
then
    echo "echo from elif"
elif [ -d /var/log ]
then
    echo "echo from elif"
else
    echo "echo in else"
fi

# for...in statement
for num in 1 2 3 4 5
do
    echo "num is $num"
done


# while statement
num=0
while [ "$num" -lt 5 ]
do
    echo -n "$num "           # -n suppress new line
    num=$((num + 1))          # increment
done


# until statement
until (( num > 10 ))
do
    echo -n "$num "
    (( num++ ))
done


# case statement
case "$SHELL" in
    "/bin/bash" )
    echo -e "\n\$SHELL is a bash shell"       # -e enable new lines
    ;;

    "/bin/sh" )
    echo -e "\n\$SHELL is a bourne shell"
    ;;

    * )
    echo -e "\ncase default"
    ;;
esac
