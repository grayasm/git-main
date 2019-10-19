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

cp win10-fonts.spec  $HOME/rpmbuild
cp ~/Downloads/win10-fonts.tar.gz  $HOME/rpmbuild
cd $HOME/rpmbuild


rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp win10-fonts.tar.gz  SOURCES/
cp win10-fonts.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/win10-fonts.spec

find . -iname '*.rpm'
