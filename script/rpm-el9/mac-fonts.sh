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

cp mac-fonts.spec $HOME/rpmbuild
cp mac-fonts.mk   $HOME/rpmbuild
cd $HOME/rpmbuild

if [ ! -f mac-fonts.tar.gz ]; then
    wget ftp://vasilian.net/Fonts/mac-fonts.tar.gz
fi

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp mac-fonts.tar.gz  SOURCES/
cp mac-fonts.mk      SOURCES/
cp mac-fonts.spec    SPECS/

rpmbuild -v -bb --clean SPECS/mac-fonts.spec
rpmsign --addsign RPMS/x86_64/mac-fonts-1.1-1.el9.x86_64.rpm

find . -iname '*.rpm'
