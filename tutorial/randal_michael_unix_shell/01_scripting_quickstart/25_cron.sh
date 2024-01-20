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
# |  |  |  +-------> month of year (1-12)
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


# * * * * * echo `date` > /tmp/log.txt          # execute every minute

# 0 2 * * * echo `date` > /tmp/log.txt          # at 2am daily

# * 5,17 * * * echo `date` > /tmp/log.txt       # twice a day, at 5am and 5pm


























