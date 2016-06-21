#!/bin/bash

# remmina and rdesktop in centos7 packages are built with pulse support.
# to install rdesktop with alsa support I build from source.


if [ ! -d /usr/include/gssglue ]; then
	echo "required: yum install libgssglue-devel"
	exit
fi


if [ ! -d /usr/include/alsa ]; then
	echo "required: yum install alsa-lib-devel"
	exit
fi


cd /tmp
echo "current directory: ${PWD}"

# need wget
wget --version 2>&1 >/dev/null
WGET_IS_AVAILABLE=$?
if [ $WGET_IS_AVAILABLE -ne 0 ]; then
	echo "install wget"
	exit
fi

wget -v https://github.com/rdesktop/rdesktop/archive/v1.8.3.zip

# need unzip
unzip -v 2>&1 >/dev/null
UNZIP_IS_AVAILABLE=$?
if [ $UNZIP_IS_AVAILABLE -ne 0 ]; then
	echo "install unzip"
	exit
fi

unzip v1.8.3.zip
rm v1.8.3.zip
cd rdesktop-1.8.3

# create configure.sh
autoreconf


DEST=/opt/rdesktop-src-1.8.3
./configure --prefix=$DEST --with-sound=alsa --disable-smartcard
make -j `nproc`

echo -e "\n\n"
echo "prefix=$DEST"
echo "if no error: make install"
