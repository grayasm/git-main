#!/bin/bash

# fonts are usually on another drive (partition)
if [ ! -d $HOME/1TB/fonts ]; then
	echo "can not find: $HOME/1TB/fonts"
	exit
fi


# should be copied in the home directory?
read -p "Install fonts in $HOME/.fonts [Y/n]=" YN
case $YN in
	[Yy] )
		# don't run as root
		if [ `id -u` -lt 1000 ]; then
			echo "log in as regular user"
			exit
		fi

		# create destination and copy the files
		if [ ! -d $HOME/.fonts ]; then
			mkdir -pv $HOME/.fonts
		fi
		cp -v $HOME/1TB/fonts/*  $HOME/.fonts
		echo "Done."
		exit
		;;
	* ) ;; #default
esac

echo "perhaps later? :)"
