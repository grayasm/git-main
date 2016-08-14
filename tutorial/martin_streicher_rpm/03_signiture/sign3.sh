#!/bin/bash

set -x
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ `basename $DIR` != "03_signiture" ]; then
	echo "run this script from: 03_signiture"
	exit
fi

rmdir  -v BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv BUILD RPMS SOURCES SPECS SRPMS

mkdir sign3-0.1
cp sign3.{cpp,mk} sign3-0.1
tar -cvzf sign3-0.1.tar.gz sign3-0.1
mv sign3-0.1.tar.gz  SOURCES/

cp sign3.spec  SPECS/
rpmbuild -v --sign -bb --clean SPECS/sign3.spec

find . -iname '*.rpm'
