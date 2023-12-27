#!/bin/bash

# The ps shows information about current system processes.

# ps            The user's currently running processes
# ps -f         Full listing of the user's currently running processes
# ps -ef        Full listing of all processes, except kernel processes
# ps -A         All processes including kernel processes
# ps -Kf        Full listing of kernel processes
# ps auxw       Wide listing sorted by percentage of CPU usage, %CPU

pid=$$

ps ax | grep $pid

#   7799 pts/0    S+     0:00 /bin/bash ./20_ps.sh
#   7801 pts/0    S+     0:00 grep 7799
