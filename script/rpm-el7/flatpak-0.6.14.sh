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

cp flatpak-0.6.14.spec  $HOME/rpmbuild
cd $HOME/rpmbuild


if [ -d flatpak-0.6.14 ]; then
	rm -rfdv flatpak-0.6.14
fi

if [ -f flatpak-0.6.14.tar.gz ]; then
	rm -v flatpak-0.6.14.tar.gz
fi

mkdir flatpak-0.6.14 && cd flatpak-0.6.14

git clone https://github.com/flatpak/flatpak.git .
git checkout -b tag_0.6.14 0.6.14
git log -1 --format=%ai 0.6.14  # 2016-11-29 , latest release

cd bubblewrap
git clone https://github.com/projectatomic/bubblewrap.git .
git checkout -b tag_0.1.4 v0.1.4
git log -1 --format=%ai v0.1.4  # 2016-11-29 , latest release


cd ../libglnx
git clone https://github.com/GNOME/libglnx.git .
git checkout abd37a4790f86f53bfb442e6d80e1710f50bff92 .
cd ../..

tar -czvf flatpak-0.6.14.tar.gz flatpak-0.6.14

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp flatpak-0.6.14.tar.gz  SOURCES/
cp flatpak-0.6.14.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/flatpak-0.6.14.spec

find . -iname '*.rpm'
