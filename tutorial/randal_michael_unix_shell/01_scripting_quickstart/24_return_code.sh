#!/bin/bash


# The return code of the last command is saved into the shell variable $?
# For successful the value is 0, zero.
# For not successul the value is other than 0, zero.

# Examples

test -d /usr/local/bin
if [ "$?" -eq 0 ]
then
    echo "/usr/local/bin does exist"
else
    echo "/usr/local/bin/ does not exist"
fi


if test -d /usr/local/bin
then    # the return code is zero
    echo "/usr/local/bin does exist"
else
    echo "/usr/local/bin does not exist"
fi


if [ -d /usr/local/bin ]
then    # the return code is zero
    echo "/usr/local/bin does exist"
else
    echo "/usr/local/bin does not exist"
fi
