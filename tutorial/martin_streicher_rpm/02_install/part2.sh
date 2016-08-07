#!/bin/bash

set -x
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ `basename $DIR` != "martin_streicher_rpm" ]; then
	echo "run this script from dir: martin_streicher_rpm"
	exit
fi

rmdir -v  BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv BUILD RPMS SOURCES SPECS SRPMS

mkdir part2-0.1 && cp part2.{cpp,mk,png} part2-0.1/
tar -cvzf part2-0.1.tar.gz part2-0.1
mv part2-0.1.tar.gz  SOURCES/

cp part2.spec  SPECS/part2.spec
rpmbuild -v -bb --clean SPECS/part2.spec

find . -iname '*.rpm'
