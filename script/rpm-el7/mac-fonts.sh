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

cp mac-fonts.spec $HOME/rpmbuild
cp ~/Downloads/mac-fonts.tar.gz $HOME/rpmbuild
cd $HOME/rpmbuild


rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp mac-fonts.tar.gz  SOURCES/
cp mac-fonts.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/mac-fonts.spec

find . -iname '*.rpm'
