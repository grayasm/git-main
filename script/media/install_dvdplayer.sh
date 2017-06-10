#!/bin/bash

if [ ! -f /etc/centos-release ]; then
	echo "only for centos"
	exit
fi

if [ `id -u` -ne 0 ]; then
	echo "required: root"
	exit
fi

if [ ! -f /etc/yum.repos.d/nux-dextop.repo ] ||
   [ ! -f /etc/yum.repos.d/epel.repo ]
then
	echo "required: nux-dextop.repo  epel.repo"
	exit
fi

DVDPLAYER="vlc smplayer ffmpeg HandBrake-{gui,cli} \
           libdvdcss libdvdread libdvdnav lsdvd libquicktime \
           mplayer mplayer-gui gstreamer-ffmpeg \
           gstreamer{,1}-plugins-ugly gstreamer-plugins-bad-nonfree \
           gstreamer1-plugins-bad-freeworld gstreamer-plugins-bad"

yum install $DVDPLAYER
