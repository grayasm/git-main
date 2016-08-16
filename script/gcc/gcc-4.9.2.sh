#!/bin/bash

set -x

rmdir -v  BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv BUILD RPMS SOURCES SPECS SRPMS

cp gcc-4.9.2.tar.gz  SOURCES/
cp gcc-4.9.2.spec    SPECS/

rpmbuild -v -bb --clean  SPECS/gcc-4.9.2.spec
