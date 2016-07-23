#!/bin/bash

# make verbose
set -x

/usr/bin/distccd --daemon --allow 192.168.0.0/24 --no-detach --log-file=/tmp/distccd.log --log-level=error
