#!/bin/bash

# https://linuxize.com/post/at-command-in-linux/

# dnf install at
# systemctl enable atd
# systemctl start atd
# systemctl status atd


# [[ Quick example: ]]

# echo `date` > /tmp/log.txt | at 16:45     <-- run the command at 16:45 and
#                                               then delete it.
# at -l                                     <-- list all current pending jobs
# at -r 15                                  <-- remove task number 15


# [[ Multiple ways to schedule a one-time job: ]]

# Using 'at' command prompt:
# at 16:45                        <--and press enter
# echo `date` > /tmp/log.txt
#                                 <-- Ctrl+D to exit
# The job will run at 16:45 and then be deleted.


# Using echo and | :
# echo `date` > /tmp/log.txt | at 16:45


# Using HERE document:
# at 16:45 <<EOF
# echo `date` > /tmp/log.txt
# EOF


# Using the -f:
# at 16:45 -f /scripts/script.sh


# [[ Options: ]]

# Use -M to avoid sending and email with the output to the user:
# at 16:45 -M


# Use -m to send an email even if there is no output:
# at 16:45 -m


# Use at -b or batch to run a command when system load average is below 1.5
# echo `date` > /tmp/log.txt | batch


# Use -q to specify to which queue to add the job.
# The queues are a to z and A to Z. Lower letters run with lower niceness.
# By default at adds the jobs to a queue, and batch to b queue.

# at monday +2 hours -q L


# [[ Time specifications: ]]

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


# Examples:

# at sunday +10 minutes    <-- if time now is 18:00:00
#                              the job will run next sunday at 18:10:00

# at 1pm +2 days           <-- at 1pm two days from now

# at 12:30 022624          <-- at 12:30 on 26 Feb 2024

# at now +1 hours          <-- one hour from now

# at -t 202402261810.30    <-- use -t to specify [[CC]YY]MMDDhhmm[.ss]



# [[ Miscellaneous: ]]

# at -l                    <-- list pending jobs, similar with 'atq'

# at -r 9                  <-- remove pending job 9, similar with atrm 9


# /etc/at.deny             <-- if exists and empty all users can use 'at'
#                              if not empty, listed users cannot use 'at'

# /etc/at.allow            <-- if exists, only listed users can use 'at'

# If neither of the files exists, only the users with administrative privileges
# can use the 'at' command.
