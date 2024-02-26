#!/bin/bash

# Cron is a service (crond) that executes commands from a file.
# Crontab (crontab) is the program used to edit,view,etc the commands.

# ==================== crond service commands: =================================
# systemctl status crond
# systemctl [start|stop|restart] crond


# ======================= crontab commands: ====================================
# https://tecadmin.net/crontab-in-linux-with-20-examples-of-cron-schedule/

# crontab file format is:
# *  *  *  *  *  /path/to/script.sh
# |  |  |  |  |  |
# |  |  |  |  |  +-> script file or directly a command to execute
# |  |  |  |  +----> day of week (0-6) 0:Sunday, 6:Saturday
# |  |  |  +-------> month of year (1-12) or Jan,Feb,Mar,Apr,May,Jun,..
# |  |  +----------> day of month (1-31)
# |  +-------------> hour (0-23)
# +----------------> minute (0-59)


# *                             - matches anything
# 1,2,3                         - matches multiple values
# mon,tue,wed,thu,fri,sat,sun   - matches multiple values
# jan,feb,mar,apr,may,jun,jul
# aug,sep,oct,nov,dec           - matches multiple values
# 1-10                          - defines a range
# feb-apr                       - defines a range
# jan-mar,jul-sep               - defines multiple ranges


# crontab -e                # edit the crontab file for the current user
# crontab -l                # list crontab entries for the current user
# crontab -u username -l    # list crontab entries for the specified user


# 0 2 * * * echo `date` > /tmp/log.txt          # at 2am daily

# 0 5,17 * * * echo `date` > /tmp/log.txt       # twice a day, at 5am and 5pm

# * * * * * echo `date` > /tmp/log.txt          # execute every minute

# 0 17 * * sun echo `date` > /tmp/log.txt       # every Sunday at 5pm

# */10 * * * * echo `date` > /tmp/log.txt       # every 10 minutes

# * * * jan,may,sep * echo `date` > /tmp/log.txt # on selected months

# 0 17 * * sun,fri echo `date` > /tmp/log.txt   # each Sunday and Friday at 5pm

# 0 */4 * * * /scripts/script.sh                # every 4 hours

# 0 4,17 * * sun,mon /scripts/script.sh         # twice on Sunday and Monday

# * * * * *           /scripts/script.sh        # cron does not have a parameter
# * * * * * sleep 30; /scripts/script.sh        # for seconds, so to run every
                                                # 30 seconds use this syntax;

# * * * * * /scripts/script1.sh; /scripts/script2.sh  # multiple jobs separated
                                                      # by ;

# @yearly /scripts/script.sh         # @yearly is similar with 0 0 1 1 *
# @monthly                           # @mongtly is similar with 0 0 1 * *
# @weekly                            # @weekly is similar with 0 0 * * sun
# @daily                             # @daily is similar with 0 0 * * *
# @hourly                            # @hourly is similar with 0 * * * *
# @reboot                            # @reboot will run on system startup

# crontab -l > cron-backup.txt       # backup cron to a text file

# crontab -r                         # clears the crontab

# crontab cron-backup.txt            # restores the crontab from file


# TROUBLESHOOTING:

# * * 33 feb * echo `date` > /tmp/log.txt       # error bad-day-of-month

# * * 31 feb * echo `date` > /tmp/log.txt       # accepted, but impossible

# 0 2 * * sun [ $(date +%d) -le 07 ] && echo `date` > /tmp/log.txt # doesn't run

# The above entry it's suppose to schedule the job only in the first Sunday
# of the month, but while testing the cron does not execute anything.
# This link:
# https://serverfault.com/questions/449651/why-is-my-crontab-not-working-and-how-can-i-troubleshoot-it
# suggests to put everything in a script or a wrapper script.

# 0 2 * * sun /path/to/first-sunday-of-the-month-housekeeping-job.sh
