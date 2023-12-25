#!/bin/bash

# https://tldp.org/LDP/abs/html/internalvariables.html

# $*        All command line arguments
# $@        All command line arguments
# "$*"      Takes the entire list as one argument with spaces in between
# "$@"      Takes the entire list and separates it into separate arguments
# $#        Number of command line arguments
# $-        Flags passed to script
# $!        PID of last job run in background
# $_        Special variable set to final argument of previous command executed
# $?        Exit status of a command, function or the script itself
# $$        PID of the script itself


# example for $*
echo -n "\$*="
for i in $*
do
    echo -n "$i "
done
echo -e ""


# example for $@
echo -n "\$@="
for i in $@
do
    echo -n "$i "
done
echo -e ""


# example for "$*"
echo "\"\$*\" expands as:"
for i in "$*"
do
    echo "param=$i"                             # all params in one line
done


# example for "$@"
echo "\"\$@\" expands as:"
for i in "$@"
do
    echo "param=$i"                             # one line for each param
done


# example for $#
echo "\$#=$# number of arguments"


# example for $-
echo "\$-=$- flags passed to script using set"      # displays =hB


# example for $!    PID of last job run in background
command1="sleep 5"
${command1} &
echo "\$!=$! PID of last sleep 5 job"


# example for $_    Final argument of previous command
echo "++++++"
echo "\$_=$_ Final argument of previous command"


# example of $?     Exit status of a command, function or script itself
last_command=$(ls *.sh)
echo "\$?=$? Exit status of a last command, SUCCESS=0"


# example of $$     PID of the script itself
echo "\$$=$$ PID of the script itself"
