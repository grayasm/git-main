#!/bin/bash

if [ `id -u` != 0 ]; then
    echo "you must be root"
    exit
fi


# ubo-icons
wget http://pen-art.ru/downloads/icons/ubo-icons-0.1alpha.tar.gz
tar zxvf ubo-icons-0.1alpha.tar.gz
rm -rfv /usr/share/icons/ubo-icons-0.1alpha
mv ubo-icons-0.1alpha /usr/share/icons/
chown -Rv root:root /usr/share/icons/ubo-icons-0.1alpha
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/icons/ubo-icons-0.1alpha
gtk-update-icon-cache /usr/share/icons/ubo-icons-0.1alpha
rm ubo-icons-0.1alpha.tar.gz


# FlatWoken and FlatWokenMin
wget https://github.com/alecive/FlatWoken/archive/master.zip
unzip master.zip
rm -rfv /usr/share/icons/FlatWoken
rm -rfv /usr/share/icons/FlatWokenMin
mv FlatWoken-master/FlatWoken  /usr/share/icons/
mv FlatWoken-master/FlatWokenMin  /usr/share/icons/
chown -Rv root:root /usr/share/icons/FlatWoken
chown -Rv root:root /usr/share/icons/FlatWokenMin
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/icons/FlatWoken
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/icons/FlatWokenMin
gtk-update-icon-cache /usr/share/icons/FlatWoken
gtk-update-icon-cache /usr/share/icons/FlatWokenMin
rm master.zip
rm -rfv FlatWoken-master
