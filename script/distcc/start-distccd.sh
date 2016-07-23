#!/bin/bash

# make verbose
set -x

/usr/bin/distccd --daemon --allow 192.168.0.0/24 --no-detach --log-file=/tmp/distccd.log --log-level=error


# Few NOTES:
# 'distcc' is the client and 'distccd' is the server application
#     *** server ***
#        - there is a systemd unit file but it does not work
#        - open port 3632 in iptables; updated iptables.add
#        - run the service as normal user with command from above
#
#    *** client ***
#        - open port 3632 in iptables;
#        export DISTCC_HOSTS='localhost 192.168.0.15'
#        export CC='distcc gcc'
#        export CXX='distcc g++'
#        cmake-gui should have the correct syntax
#        make -j $(nproc)*2  ; but in reality the localhost is always 1/2 idle,
#                              and the other machine is at 100% all CPUs.
