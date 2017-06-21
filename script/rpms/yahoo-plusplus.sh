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


cp yahoo-plusplus.spec  $HOME/rpmbuild
cd $HOME/rpmbuild

if [ ! -f master.zip ]; then
	wget https://github.com/EionRobb/funyahoo-plusplus/archive/master.zip
fi

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS

cp master.zip             SOURCES/
cp yahoo-plusplus.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/yahoo-plusplus.spec

find . -iname '*.rpm'
