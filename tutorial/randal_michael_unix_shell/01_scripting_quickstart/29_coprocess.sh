#!/bin/bash

# This co-process does not work.
# xwatch is suppose to read what xtrap is print-ing but it can't.
# I need to review this method sometime later.

BREAK_OUT='N'

function xtrap
{
    BREAK_OUT='Y'
}

function xwatch
{
    while [ true ]
    do
        if [[ $BREAKOUT == 'Y' ]]
        then
            echo "Terminated!"
            return 0
        fi
    done
}


trap "xtrap; exit 2" SIGHUP SIGINT SIGQUIT SIGKILL SIGTERM

xwatch &

WPID=$!

echo "PID=${WPID}"

COUNTER=15

until (( COUNTER == 0 ))
do
    (( COUNTER = COUNTER - 1 ))
    sleep 1
    echo "counter: ${COUNTER}; Kill me with Ctrl+C"
done
