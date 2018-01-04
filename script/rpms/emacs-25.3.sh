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

cp emacs-25.3.spec  $HOME/rpmbuild
cd $HOME/rpmbuild

gpg --recv-key 7C207910
if [ ! -f emacs-25.3.tar.xz ]; then
	wget http://ftp.gnu.org/gnu/emacs/emacs-25.3.tar.xz
	wget http://ftp.gnu.org/gnu/emacs/emacs-25.3.tar.xz.sig
fi

gpg --verify emacs-25.3.tar.xz.sig emacs-25.3.tar.xz
if [ $? -eq 0 ]; then
	echo "emacs-25.3.tar.xz.sig :OK"
else
	echo "emacs-25.3.tar.xz.sig :NOT OK"
	exit
	# Not until I have 7C207910 key installed.
fi


rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS


cp emacs-25.3.tar.xz  SOURCES/
cp emacs-25.3.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/emacs-25.3.spec

find . -iname '*.rpm'
