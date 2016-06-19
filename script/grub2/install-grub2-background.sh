#!/bin/bash

# check location
if [ "${PWD##*/}" != "grub2" ]; then
	echo "switch to script directory!"
	exit
fi

# need wget
wget --version 2>&1 >/dev/null
WGET_IS_AVAILABLE=$?
if [ $WGET_IS_AVAILABLE -ne 0 ]; then
	echo "install wget"
	exit
fi

# need root
if [ `id -u` -ne 0 ]; then
	echo "required: root"
	exit
fi

# download the bg
cd /boot/grub
wget https://sites.google.com/site/grayasm/grub/grub-solar.tga
chcon -v -u system_u -t boot_t  grub-solar.tga

# save default grub
cd /etc/default
if [ ! -f /etc/default/grub.orig ]; then
	cp /etc/default/grub  /etc/default/grub.orig
fi

# switch grub console to graphic + 120 timeout
sed -i '/^GRUB_TERMINAL_OUTPUT=/s/^/#/g'          grub
sed -i 's/^GRUB_TIMEOUT=[0-9]*/GRUB_TIMEOUT=120/' grub

# append/replace bg
grep -q '^GRUB_BACKGROUND=' grub
if [ $? -eq 0 ]; then
	# use % as escape because of / in bg path
	sed -i 's%^GRUB_BACKGROUND=.*%GRUB_BACKGROUND="/boot/grub/grub-solar.tga"%' grub
else
	# bg not found, append
	printf '%s\n' 'GRUB_BACKGROUND="/boot/grub/grub-solar.tga"' >> grub
fi

grub2-mkconfig -o /boot/grub2/grub.cfg
