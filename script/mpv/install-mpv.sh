#!/bin/bash

yum install ffmpeg-devel libass-devel lua-devel libv4l-devel mesa-libEGL-devel
yum install alsa-lib-devel libguess-devel
# I already have X11 devel

wget http://github.com/mpv-player/mpv/archive/v0.22.0.tar.gz
tar -zxvf v0.22.0.tar.gz
cd mpv-0.22.0
./waf configure --prefix=/opt/mpv-0.22
./waf build
su # to root
./waf install
