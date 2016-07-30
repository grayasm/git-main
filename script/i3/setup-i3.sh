#!/bin/bash

# verbose
set -x

# pwd in this script location
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# last directory must match "i3" -> run from git repository
if [ "`basename $DIR`" != "i3" ]; then
	echo "run this script only from git repository"
	exit
fi


if [ ! -f /usr/bin/i3 ]; then
	echo "i3 not found at '/usr/bin/i3' ; install i3"
	exit
fi

if [ ! -f /usr/bin/i3bar ]; then
	echo "i3bar status bar program not found at '/usr/bin/i3bar'; install i3bar"
	exit
fi

if [ ! -f /usr/bin/i3status ]; then
	# i3status is an info output program
	# $> i3status | dzen2    ; to get a statusbar
	echo "i3status program not found at '/usr/bin/i3status'; install i3status"
	exit
fi

mkdir -pv $HOME/.config/i3status
if [ -f $HOME/.config/i3status/config ]; then
	cp $HOME/.config/i3status/config $HOME/.config/i3status/config.old
fi

cp ./i3status-config  $HOME/.config/i3status/config
