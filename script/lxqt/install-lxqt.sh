#!/bin/bash

if [ ! -f /etc/rocky-release ]; then
    echo "packages are for RockyLinux only"
    exit
fi

if [ `id -u` != 0 ]; then
    echo "you must be root"
    exit
fi

# asking if there are plugins for:
# systemload (cpu,mem,swap,uptime,net traffic), appfinder, datetime, dict,
# mount, netload, notes, panel, powermgr, screenshooter, sensors, settings,
# smartbookmark, terminal, timeout, wheater, xkb, editor, calendar,
# img viewer, video player, file manager, volume manager

LXQT="liblxqt liblxqt-mount lxqt-about lxqt-common lxqt-config \
      lxqt-globalkeys lxqt-notificationd lxqt-openssh-askpass \
      lxqt-panel lxqt-policykit lxqt-powermanagement \
      lxqt-qtplugin lxqt-runner lxqt-session lximage-qt \
      lxqt-sudo pcmanfm-qt"

echo "Installing LXQT for RockyLinux"
dnf install $LXQT
