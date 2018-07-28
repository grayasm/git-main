#!/bin/bash

if [ ! -f /etc/centos-release ]; then
	echo "packages are for CentOS only"
	exit
fi

if [ `id -u` != 0 ]; then
	echo "you must be root"
	exit
fi

XFCE="f22-backgrounds-xfce gtk-xfce-engine \
      libxfce4ui libxfce4util libxfcegui4 \
      xfce4-about xfce4-appfinder xfce4-cpufreq-plugin \
      xfce4-cpugraph-plugin xfce4-datetime-plugin \
      xfce4-dict xfce4-mount-plugin xfce4-netload-plugin \
      xfce4-notes-plugin xfce4-notifyd xfce4-panel \
      xfce4-power-manager xfce4-screenshooter \
      xfce4-sensors-plugin xfce4-session \
      xfce4-session-engines xfce4-settings \
      xfce4-smartbookmark-plugin xfce4-systemload-plugin \
      xfce4-terminal xfce4-time-out-plugin \
      xfce4-weather-plugin xfce4-xkb-plugin exo mousepad \
      orage parole ristretto xarchiver xfdesktop xfwm4 \
      Thunar thunar-archive-plugin thunar-volman \
      ntfs-3g udisks2 gvfs gvfs-fuse gvfs-gphoto2 gvfs-smb \
      gvfs-archive"

echo "Installing Xfce for CentOS"
yum group install "Xfce"
yum install $XFCE



