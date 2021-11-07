#!/bin/bash

if [ ! -f /etc/rocky-release ]; then
    echo "only for rocky"
    exit
fi

if [ `id -u` -ne 0 ]; then
    echo "required: root"
    exit
fi


dnf provides "/usr/include/gtk-2.0/gtk/gtk.h"
dnf install gtk2-devel
# gcc ... `pkg-config --cflags --libs gtk+-2.0`


dnf provides "/usr/include/libglade-2.0/glade/glade.h"
dnf install libglade2-devel
# gcc ... `pkg-config --cflags --libs gtk+-2.0 libglade-2.0`


#User Interface Designer for GTK+ 2
dnf install glade3
