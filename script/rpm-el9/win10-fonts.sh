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
%_gpg_name    Mihai Vasilian (RPM Signing Key) <grayasm@gmail.com>
" > $HOME/.rpmmacros

cp win10-fonts.spec  $HOME/rpmbuild
cp win10-fonts.mk    $HOME/rpmbuild
cd $HOME/rpmbuild

if [ ! -f win10-fonts.tar.gz ]; then
    wget ftp://vasilian.net/Fonts/win10-fonts.tar.gz
fi

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp win10-fonts.tar.gz  SOURCES/
cp win10-fonts.mk      SOURCES/
cp win10-fonts.spec    SPECS/

rpmbuild -v -bb --clean SPECS/win10-fonts.spec
rpmsign --addsign RPMS/x86_64/win10-fonts-1.2-1.el9.x86_64.rpm

find . -iname '*.rpm'
