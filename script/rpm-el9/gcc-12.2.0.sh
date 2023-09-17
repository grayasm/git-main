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
%_gpg_name    Mihai Vasilian (RPM Signing Key) <grayasm@gmail.com>
" > $HOME/.rpmmacros

cp gcc-12.2.0.spec  $HOME/rpmbuild
cd $HOME/rpmbuild

if [ ! -f gcc-12.2.0.tar.xz ]; then
    wget https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.xz
    wget https://ftp.gnu.org/gnu/mpfr/mpfr-4.2.0.tar.xz
    wget https://ftp.gnu.org/gnu/gmp/gmp-6.2.1.tar.xz
    wget https://ftp.gnu.org/gnu/mpc/mpc-1.3.1.tar.gz

    cat > md5sum.sum << EOF
73bafd0af874439dcdb9fc063b6fb069 gcc-12.2.0.tar.xz
a25091f337f25830c16d2054d74b5af7 mpfr-4.2.0.tar.xz
0b82665c4a92fd2ade7440c13fcaa42b gmp-6.2.1.tar.xz
5c9bc658c9fd0f940e8e3e0f09530c62 mpc-1.3.1.tar.gz
EOF
fi

GCCSUM=`md5sum -c md5sum.sum 2>/dev/null | grep 'gcc-12.2.0.tar.xz: OK'`
MPFSUM=`md5sum -c md5sum.sum 2>/dev/null | grep 'mpfr-4.2.0.tar.xz: OK'`
GMPSUM=`md5sum -c md5sum.sum 2>/dev/null | grep 'gmp-6.2.1.tar.xz: OK'`
MPCSUM=`md5sum -c md5sum.sum 2>/dev/null | grep 'mpc-1.3.1.tar.gz: OK'`


if [ "${GCCSUM}" == "gcc-12.2.0.tar.xz: OK" ] &&
   [ "${MPFSUM}" == "mpfr-4.2.0.tar.xz: OK" ] &&
   [ "${GMPSUM}" == "gmp-6.2.1.tar.xz: OK" ] &&
   [ "${MPCSUM}" == "mpc-1.3.1.tar.gz: OK" ]
then
	echo "md5sum is OK"
else
	echo "md5sum NOT OK"
	exit
fi

rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS


cp gcc-12.2.0.tar.xz    SOURCES/
cp mpfr-4.2.0.tar.xz    SOURCES/
cp gmp-6.2.1.tar.xz     SOURCES/
cp mpc-1.3.1.tar.gz     SOURCES/
cp gcc-12.2.0.spec      SPECS/


rpmbuild -v -bb --clean SPECS/gcc-12.2.0.spec
rpmsign --addsign RPMS/x86_64/gcc1220-12.2.0-1.el9.x86_64.rpm

find . -iname '*.rpm'





















