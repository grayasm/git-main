#!/bin/bash

if [ ! -f /etc/centos-release ]; then
	echo "centos supported only!"
	exit
fi

if [ `id -u` -ne 0 ]; then
	echo "run as root"
	exit
fi

X11_DEVEL='libXp-devel  libXpm-devel  libXt-devel  libXtst-devel
          libXv-devel libXvMC-devel  libX11-devel  libXNVCtrl-devel
          libXScrnSaver-devel  libXau-devel  libXaw-devel libXcomposite-devel
          libXcursor-devel  libXdamage-devel  libXdmcp-devel  libXevie-devel
          libXext-devel  libXfixes-devel  libXfont-devel libXft-devel
          libXi-devel libXinerama-devel  libXmu-devel  libXrandr-devel
          libXrender-devel  libXres-devel  libXxf86dga-devel libXxf86misc-devel
          libXxf86vm-devel  libx86-devel  libx86emu-devel  libxc-devel
          libxcb-devel  libxdo-devel  libxkbfile-devel  libxklavier-devel
          libxkbcommon-devel'

echo $X11_DEVEL
