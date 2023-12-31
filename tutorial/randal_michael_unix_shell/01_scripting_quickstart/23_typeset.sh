#!/bin/bash

# We case use typeset to control the attributes of a variable in the shell.
# We can set the attribute to always translate all of the characters to
# upppercase or lowercase.
#
# typeset is a bash built-in command:
# typeset [-aAfFgiIlnrtux] [-p] [name[=value] ...]

typeset -u VARIABLE
VARIABLE="TYPEset UPPERcase ATTRibute"
echo "$\VARIABLE=$VARIABLE"                 # TYPESET UPPERCASE ATTRIBUTE


typeset -l VARIABLE
VARIABLE="TYPEset LOWERcase ATTRibute"
echo "$\VARIABLE=$VARIABLE"                 # typeset lowercase attribute
