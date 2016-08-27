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

cp gcc-6.1.0.spec  $HOME/rpmbuild
cd $HOME/rpmbuild

if [ ! -f gcc-6.1.0.tar.gz ]; then
	wget ftp://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-6.1.0/gcc-6.1.0.tar.gz
fi

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp gcc-6.1.0.tar.gz  SOURCES/
cp gcc-6.1.0.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/gcc-6.1.0.spec

find . -iname '*.rpm'
