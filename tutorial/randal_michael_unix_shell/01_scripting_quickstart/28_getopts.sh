#!/bin/bash

# getopts OptionString VARIABLE [ Arguments ... ]

# getopt is parse command options (enhanced) and the installation
# should provide an example for bash here:
# /usr/share/doc/util-linux/getopt-example.bash


# Run this as:
#
# ./28_getopts.sh -d200 -h 23 -m30 -s20 -p 28_getops.sh
#



SECS=0          # initialize all to zero
MINUTES=0
HOURS=0
DAYS=0
PROCESS=        # initialize to null


while getopts :s:m:h:d:p: TIMED 2> /dev/null
do
    case $TIMED in
        s) SECS=$OPTARG
           ;;
        m) (( MINUTES = $OPTARG * 60 ))
           ;;
        h) (( HOURS = $OPTARG * 3600 ))
           ;;
        d) (( DAYS = $OPTARG * 86400 ))
           ;;
        p) PROCESS=$OPTARG
           ;;
        \?) echo "usage: -d1 -h23 -m59 -s59 -p /scripts/script.sh"
            exit 1
            ;;
    esac
done

echo "Days   : $(( $DAYS / 86400 ))"
echo "Hours  : $(( $HOURS / 3600 ))"
echo "Minutes: $(( $MINUTES / 60 ))"
echo "Seconds: ${SECS}"
echo "Process: ${PROCESS}"
