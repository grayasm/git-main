#!/bin/bash

# https://linuxize.com/post/at-command-in-linux/

# dnf install at
# systemctl enable atd
# systemctl start atd
# systemctl status atd


# 1) Schedule a job using 'at' command prompt:
# at 16:45                        <--and press enter
# echo `date` > /tmp/log.txt
#                                 <-- Ctrl+D to exit
# The job will run at 16:45 and then be deleted.


# 2) Schedule a job using echo and pipe | to at:
# echo `date` > /tmp/log.txt | at 16:45


# 3) Schedule a job using HERE document:
# at 16:45 <<EOF
# echo `date` > /tmp/log.txt
# EOF


# 4) Schedule a job by passing the -f script directly:
# at 16:45 -f /scripts/script.sh


# 5) Use -M to avoid sending and email with the output to the user:
# at 16:45 -M


# 6) Use -m to send an email even if there is no output:
# at 16:45 -m


# 7) Use at -b or batch to run a command when system load average is below 1.5
# echo `date` > /tmp/log.txt | batch


# at [OPTIONS] time_specifications

# 'at' allows pretty complex time specifications with TIME, DATE and INCREMENT
# in combinations.

# TIME supports:
# HH:MM or HHMM
# when using 12-hour clock format, can add 'am' or 'pm'
# can add strings like now, midnight, noon or teatime


# DATE supports:
# MMDD[CC]YY
# MM/DD/[CC]YY
# DD.MM.[CC]YY
# [CC]YY-MM-DD
# alternatively you can use strings like: today or tomorrow or weekday.


# INCREMENT supports:
# now + count time-unit
# time-unit can be: minutes, hours, days, weeks


# Examples, using 'at' command prompt.

# at sunday +10 minutes
# if time now is 18:00:00 it will schedule a job for next sunday at 18:10:00

# at 1pm +2 days           <-- at 1pm two days from now

# at 12:30 022624          <-- at 12:30 on 26 Feb 2024

# at now +1 hours          <-- one hour from now

# at -t 202402261810.30    <-- use -t to specify [[CC]YY]MMDDhhmm[.ss]
