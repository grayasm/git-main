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

if [ ! -f /usr/bin/feh ]; then
	echo "feh wallpaper setting tool not found at '/usr/bin/feh'; install feh"
	exit
	#[copr-admiralnemo-feh]
	#name=feh for i3 window manager
	#baseurl=http://copr-be.cloud.fedoraproject.org/results/admiralnemo/i3wm-el7/epel-7-$basearch/
	#failovermethod=priority
	#enabled=1
	#gpgcheck=1
	#gpgkey=https://copr-be.cloud.fedoraproject.org/results/admiralnemo/i3wm-el7/pubkey.gpg
	#priority=90
fi



mkdir -pv $HOME/.config/i3status
if [ -f $HOME/.config/i3status/config ]; then
	cp $HOME/.config/i3status/config $HOME/.config/i3status/config.old
fi

cp ./i3status-config  $HOME/.config/i3status/config

echo "please add content of i3-config at the end of ~/.config/i3/config"
