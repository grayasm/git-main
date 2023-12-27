#!/bin/bash

# The last command shows the history of who has logged in to the system
# since the wtmp file was created.

echo "`last`"

# mihai    tty1         :0               Wed Dec 27 09:21   still logged in
# mihai    :0                            Wed Dec 27 09:21   still logged in
# reboot   system boot  5.14.0-362.8.1.e Wed Dec 27 09:17   still running
#
# wtmp begins Wed Dec 27 01:19:09 2023


locate wtmp
# /etc/logrotate.d/wtmp
# /var/log/wtmp
# /var/log/wtmp-20231227
