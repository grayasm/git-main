#!/bin/bash

# Make sure only root can run our script
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root"
   exit 1
fi

if [ ! -f /etc/yum.repos.d/vasilian.repo ]; then
	echo "Add vasilian.repo"
	exit 1
fi

dnf --enablerepo=vasilian install win10-fonts
