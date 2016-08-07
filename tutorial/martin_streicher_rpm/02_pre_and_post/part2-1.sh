#!/bin/bash

set -x
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ `basename $DIR` != "02_pre_and_post" ]; then
	echo "run this script from: 02_pre_and_post"
	exit
fi

rmdir  -v BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv BUILD RPMS SOURCES SPECS SRPMS

mkdir part2-1.1
cp part2-1.{cpp,mk,config} part2-1.1/
tar -cvzf part2-1.1.tar.gz part2-1.1
mv part2-1.1.tar.gz  SOURCES/


cp part2-1.spec SPECS/
rpmbuild -v -bb --clean  SPECS/part2-1.spec

find . -iname '*.rpm'
