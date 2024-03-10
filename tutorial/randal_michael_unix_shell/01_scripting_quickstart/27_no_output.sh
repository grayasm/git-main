#!/bin/bash

# 0 - stdin    /dev/stdin -> /proc/self/fd/0
# 1 - stdout   /dev/stdout-> /proc/self/fd/1
# 2 - stderr   /dev/stderr-> /proc/self/fd/2


# Redirect stdout to bit bucket
ls -1 / 1> /dev/null

# Redirect stderr to bit bucket
ls -l /etc/audit 2> /dev/null


# Redirect both stdout and stderr to /dev/null
find /etc -type f > /dev/null 2>&1


# The syntax in general is
# command       >/dev/null 2>&1
# ./script.sh   >/dev/null 2>&1
# ./example.pl  >/dev/null 2>&1


# It redirects first implicitly the output to /dev/null
# and then the error output into standard output with 2>&1
