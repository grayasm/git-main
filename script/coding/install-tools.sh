#!/bin/bash

if [ `id -u` != 0 ]; then
    echo "you must be root"
    exit
fi

cd /tmp
# test new commands here
# exit here when testing new commands
#exit

dnf install -y filezilla

dnf group install -y "Development Tools"

wget ftp://vasilian.net/Devel/eclipse-cpp-2022-09-R-linux-gtk-x86_64.tar.gz
tar -xvf eclipse-cpp-2022-09-R-linux-gtk-x86_64.tar.gz
mv eclipse /opt/eclipse-2022-09
chown -Rv root:root /opt/eclipse-2022-09
chcon -u system_u -t usr_t -Rv /opt/eclipse-2022-09
cat << EOF > /usr/share/applications/eclipse-2022-09.desktop
[Desktop Entry]
Version=1.0
Name=Eclipse IDE 2022-09
Comment=C/C++ Programming IDE
Keywords=programming;code;editor;development;c;c++;
Exec=/opt/eclipse-2022-09/eclipse
Icon=/opt/eclipse-2022-09/icon.xpm
Terminal=false
Type=Application
StartupNotify=true
Categories=GTK;GNOME;Development;
MimeType=text/x-c++src;text/x-c++hdr;text/x-csrc;text/x-chdr;
EOF
chcon -u system_u -v /usr/share/applications/eclipse-2022-09.desktop
