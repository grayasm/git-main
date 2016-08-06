#!/bin/bash

set -x
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ `basename $DIR` != "martin_streicher_rpm" ]; then
	echo "run this script from dir: martin_streicher_rpm"
	exit
fi

rmdir -v  BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv BUILD RPMS SOURCES SPECS SRPMS

cd SOURCES
wget http://ftp.halifax.rwth-aachen.de/gnu/wget/wget-1.18.tar.gz

cd ..
cp part1.spec  SPECS/wget.spec
rpmbuild -v -bb --clean SPECS/wget.spec

find . -iname '*.rpm'
