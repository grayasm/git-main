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

cp gcc-4.9.2.spec  $HOME/rpmbuild
cd $HOME/rpmbuild

if [ ! -f gcc-4.9.2.tar.gz ]; then
	wget ftp://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-4.9.2/gcc-4.9.2.tar.gz
fi

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp gcc-4.9.2.tar.gz  SOURCES/
cp gcc-4.9.2.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/gcc-4.9.2.spec

find . -iname '*.rpm'
