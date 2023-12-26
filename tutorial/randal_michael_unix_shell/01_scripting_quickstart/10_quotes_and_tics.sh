#!/bin/bash

# https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_03_03.html


# " "       Use double quotes " to allow character or command substitution.
# ' '       Use forward tics (single quotes) where we do not want character or
#           command substitution.
# ` `       Use back tics to execute a command or a script and have its output
#           substituted.


name="Randal K. Michael"
echo "$name"                # Randal K. Michael
echo '$name'                # $name
d=`date`
echo "$d"                   # Tue Dec 26 10:59:16 PM CET 2023
