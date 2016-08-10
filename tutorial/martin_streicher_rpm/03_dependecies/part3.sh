#!/bin/bash

set -x
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ `basename $DIR` != "03_dependencies" ]; then
	echo "run this script from: 03_dependencies"
	exit
fi

rmdir  -v BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv BUILD RPMS SOURCES SPECS SRPMS

mkdir part3-0.1
cp part3.{cpp,mk} part3-0.1
tar -cvzf part3-0.1.tar.gz part3-0.1
mv part3-0.1.tar.gz  SOURCES/

cp part3.spec  SPECS/
rpmbuild -v -bb --clean SPECS/part3.spec

find . -iname '*.rpm'
