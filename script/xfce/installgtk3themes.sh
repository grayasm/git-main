#!/bin/bash

# 1) Nevermind, just copy to ftp://vasilian.net/Misc

if [ `id -u` != 0 ]; then
	echo "you must be root"
	exit
fi


cd /tmp
# exit when testing new commands
# exit

# Xfce-ClassicLooks Gtk3 Theme
# https://www.gnome-look.org/p/1326363/
wget ftp://vasilian.net/Gtk3-Themes/classiclooks-1.5.0.zip
unzip classiclooks-1.5.0.zip -d classiclooks
rm -rfv "/usr/share/themes/ClassicLooks"
rm -rfv "/usr/share/themes/ClassicLooks Ambiance"
rm -rfv "/usr/share/themes/ClassicLooks Bronze"
rm -rfv "/usr/share/themes/ClassicLooks Crux"
rm -rfv "/usr/share/themes/ClassicLooks Devilsclaw"
rm -rfv "/usr/share/themes/ClassicLooks Graphite"
rm -rfv "/usr/share/themes/ClassicLooks Greybird"
rm -rfv "/usr/share/themes/ClassicLooks (HDPI)"
rm -rfv "/usr/share/themes/ClassicLooks Icelake"
rm -rfv "/usr/share/themes/ClassicLooks Irix"
rm -rfv "/usr/share/themes/ClassicLooks Rainyday"
rm -rfv "/usr/share/themes/ClassicLooks Raleigh"
rm -rfv "/usr/share/themes/ClassicLooks Redmond"
rm -rfv "/usr/share/themes/ClassicLooks Solaris"
rm -rfv "/usr/share/themes/ClassicLooks Straw"
rm -rfv "/usr/share/themes/ClassicLooks Summerfield"
rm -rfv "/usr/share/themes/ClassicLooks Summerstorm"
rm -rfv "/usr/share/themes/ClassicLooks XFWM4"
rm -rfv "/usr/share/themes/ClassicLooks XFWM4 (HDPI)"
rm -fv classiclooks/HISTORY
rm -fv classiclooks/LICENSE
rm -fv classiclooks/README
mv classiclooks/* /usr/share/themes/
chown -Rv root:root /usr/share/themes/ClassicLooks*
chmod -Rv 755 /usr/share/themes/ClassicLooks*
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/ClassicLooks*
rm classiclooks-1.5.0.zip
rm -rfv classiclooks
