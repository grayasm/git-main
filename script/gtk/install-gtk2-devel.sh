#!/bin/bash

if [ ! -f /etc/centos-release ]; then
	echo "only for centos"
	exit
fi

if [ `id -u` -ne 0 ]; then
	echo "required: root"
	exit
fi


yum provides "/usr/include/gtk-2.0/gtk/gtk.h"
yum install gtk2-devel
# gcc ... `pkg-config --cflags --libs gtk+-2.0`


yum provides "/usr/include/libglade-2.0/glade/glade.h"
yum install libglade2-devel
# gcc ... `pkg-config --cflags --libs gtk+-2.0 libglade-2.0`


#User Interface Designer for GTK+ 2
yum install glade3
