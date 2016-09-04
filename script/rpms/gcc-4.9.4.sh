#!/bin/bash


set -x

if [ ! -d $HOME/rpmbuild ]; then
	mkdir -v $HOME/rpmbuild
fi

if [ ! -f $HOME/.rpmmacros ]; then
	touch $HOME/.rpmmacros
fi

echo "
%_signature   gpg
%_gpg_path    /home/mihai/.gnupg
%_gpg_name    Mihai Vasilian (Key for RPM) <grayasm@gmail.com>
" > $HOME/.rpmmacros

cp gcc-4.9.4.spec  $HOME/rpmbuild
cd $HOME/rpmbuild

if [ ! -f gcc-4.9.4.tar.gz ]; then
	wget ftp://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-4.9.4/gcc-4.9.4.tar.gz
	wget ftp://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-4.9.4/md5.sum
fi

CHECKSUM=`md5sum -c md5.sum 2>/dev/null | grep gcc-4.9.4.tar.gz | cut -d : -f 2`
if [ "${CHECKSUM}" == " OK" ]; then
	echo "md5sum is OK"
else
	echo "md5sum NOT OK"
	exit
fi

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp gcc-4.9.4.tar.gz  SOURCES/
cp gcc-4.9.4.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/gcc-4.9.4.spec

find . -iname '*.rpm'
