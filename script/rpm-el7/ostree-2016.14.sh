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

cp ostree-2016.14.spec  $HOME/rpmbuild
cd $HOME/rpmbuild

if [ -d ostree-2016.14 ]; then
	rm -rfdv ostree-2016.14
fi

if [ -f ostree-2016.14.tar.gz ]; then
	rm -v ostree-2016.14.tar.gz
fi

mkdir ostree-2016.14 && cd ostree-2016.14
git clone https://github.com/ostreedev/ostree.git .
git checkout -b tag_v2016.14 v2016.14
git log -1 --format=%ai v2016.14  # tag creation date: 2016-11-23 10:42:39 -0500
cd libglnx
git clone https://github.com/GNOME/libglnx.git .
git checkout abd37a4790f86f53bfb442e6d80e1710f50bff92 .
cd ../..
tar -czvf ostree-2016.14.tar.gz ostree-2016.14

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp ostree-2016.14.tar.gz  SOURCES/
cp ostree-2016.14.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/ostree-2016.14.spec

find . -iname '*.rpm'
