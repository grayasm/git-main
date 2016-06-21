#!/bin/bash

# warnings
echo "If you run kernel-lt with NVIDIA-Linux-x86_64-340.96.run
this script will disable the nvidia driver (dump login to console).
I had to:
systemctl disable lightdm.service && reboot
/usr/bin/nvidia-uninstall && rm /etc/X11/xorg.conf
yum install kernel kmod-nvidia-340xx && reboot # to kernel
graphic login || startx
run this script
reboot # to kernel-lt
yum remove kernel kmod-nvidia-340xx
reboot # kernel-lt/graphic; nouveau in initramfs: hard to blacklist other way
install NVIDIA-Linux-x86_64-340.96.run
reboot # to kernel-lt with nvidia-340xx, all should be fine again.

When you are ready remove this exit to proceed with the script."
exit


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
