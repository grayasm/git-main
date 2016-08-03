#!/bin/bash

set -x
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ `basename $DIR` != "martin_streicher_rpm" ]; then
	echo "run this script from dir: martin_streicher_rpm"
	exit
fi

mkdir -pv BUILD RPMS SOURCES SPECS SRPMS
cd SOURCES
wget http://ftp.gnu.org/gnu/wget/wget-1.18.tar.gz
