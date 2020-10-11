#!/bin/bash

if [ ! -f /etc/centos-release ]; then
	echo "packages are for CentOS only"
	exit
fi

if [ `id -u` != 0 ]; then
	echo "you must be root"
	exit
fi

if [ ! -f /etc/yum.repos.d/nux-dextop.repo ]; then
	echo "must install nux-dextop repository first"
	exit
fi

if [ ! -f /etc/yum.repos.d/epel.repo ]; then
	echo "must install epel repository first"
	exit
fi

if [ ! -f /etc/yum.repos.d/icons-moka.repo ]; then
	echo "must install icons-moka repository first"
	exit
fi

if [ ! -f /etc/yum.repos.d/fedora19.repo ]; then
    echo "must install fedora19 repository first"
    exit
fi


ENGINE="gtk-murrine-engine gtk-nimbus-engine \
        gtk-nodoka-engine gtk-nodoka-engine-extras \
        gtk-unico-engine gtk-aurora-engine gtk-equinox-engine \
        xfwm4-theme-nodoka libia_ora-gnome"
echo "Installing Theme Engines"
yum --enablerepo=fedora19 install $ENGINE



THEMES="clearlooks-phenix-common clearlooks-phenix-gtk2-theme \
        clearlooks-phenix-xfwm4-theme xfwm4-themes bluecurve-gtk-themes  \
        zukitwo-gtk2-theme zukitwo-xfwm4-theme \
        iaora-gnome-theme light-theme-gnome \
        nodoka-theme-gnome"
echo "Installing Xfce themes for CentOS"
yum --enablerepo=fedora19 install $THEMES



ICONS="mate-icon-theme-faenza dmz-cursor-themes hicolor-icon-theme \
       moka-icon-theme gnome-icon-theme gnome-colors-icon-theme \
       gnome-icon-theme-extras gnome-icon-theme-legacy \
       gnome-icon-theme-symbolic"
echo "Installing Icons for CentOS"
yum --enablerepo=fedora19 install $ICONS


REDHAT_THEMES="bluecurve-cursor-theme bluecurve-icon-theme \
               clearlooks-compact-gnome-theme clearlooks-phenix-common \
               clearlooks-phenix-gtk2-theme clearlooks-phenix-gtk3-theme \
               clearlooks-phenix-xfwm4-theme fedora-icon-theme \
               gnome-theme-curvylooks gnome-themes gnome-themes-legacy \
               gnome-themes-standard humanity-icon-theme \
               tango-icon-theme xfce4-icon-theme"
echo "Installing RedHat Artwork for Xfce"
yum --enablerepo=fedora19 install $REDHAT_THEMES

