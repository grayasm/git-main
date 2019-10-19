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

cp gtk-aurora-engine.spec $HOME/rpmbuild
cd $HOME/rpmbuild

if [ ! -f gtk-aurora-engine-1.5.1.tar.gz ]; then
	wget ftp://vasilian.net/Gtk-Engines/gtk-aurora-engine-1.5.1.tar.gz
	wget ftp://vasilian.net/Gtk-Engines/gtk-aurora-engine-1.5.1.md5
fi

CHECKSUM=`md5sum -c gtk-aurora-engine-1.5.1.md5 2>/dev/null | grep gtk-aurora-engine-1.5.1.tar.gz | cut -d : -f 2`

if [ "${CHECKSUM}" == " OK" ]; then
	echo "md5sum is OK"
else
	echo "md5sum NOT OK"
	exit
fi

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp gtk-aurora-engine-1.5.1.tar.gz  SOURCES/
cp gtk-aurora-engine-1.5.1.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/gtk-aurora-engine-1.5.1.spec

find . -iname '*.rpm'
