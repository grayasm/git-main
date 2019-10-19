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

cp clang-3.9.1.spec  $HOME/rpmbuild
cd $HOME/rpmbuild

# ----- llvm-3.9.1 -----
gpg --recv-key 02119294
if [ ! -f llvm-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/llvm-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/llvm-3.9.1.src.tar.xz.sig
fi

gpg --verify llvm-3.9.1.src.tar.xz.sig llvm-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "llvm-3.9.1.src.tar.xz.sig :OK"
else
	echo "llvm-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- clang-3.9.1 -----
if [ ! -f cfe-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/cfe-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/cfe-3.9.1.src.tar.xz.sig
fi

gpg --verify cfe-3.9.1.src.tar.xz.sig cfe-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "cfe-3.9.1.src.tar.xz.sig :OK"
else
	echo "cfe-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ---- compiler-rt-3.9.1 -----
if [ ! -f compiler-rt-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/compiler-rt-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/compiler-rt-3.9.1.src.tar.xz.sig
fi

gpg --verify compiler-rt-3.9.1.src.tar.xz.sig compiler-rt-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "compiler-rt-3.9.1.src.tar.xz.sig :OK"
else
	echo "compiler-rt-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- libcxx-3.9.1 -----
if [ ! -f libcxx-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/libcxx-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/libcxx-3.9.1.src.tar.xz.sig
fi

gpg --verify libcxx-3.9.1.src.tar.xz.sig libcxx-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "libcxx-3.9.1.src.tar.xz.sig :OK"
else
	echo "libcxx-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- libcxxabi-3.9.1 -----
if [ ! -f libcxxabi-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/libcxxabi-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/libcxxabi-3.9.1.src.tar.xz.sig
fi

gpg --verify libcxxabi-3.9.1.src.tar.xz.sig libcxxabi-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "libcxxabi-3.9.1.src.tar.xz.sig :OK"
else
	echo "libcxxabi-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- libunwind-3.9.1 -----
if [ ! -f libunwind-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/libunwind-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/libunwind-3.9.1.src.tar.xz.sig
fi

gpg --verify libunwind-3.9.1.src.tar.xz.sig libunwind-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "libcxxabi-3.9.1.src.tar.xz.sig :OK"
else
	echo "libcxxabi-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- lld-3.9.1 -----
if [ ! -f lld-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/lld-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/lld-3.9.1.src.tar.xz.sig
fi

gpg --verify lld-3.9.1.src.tar.xz.sig lld-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "lld-3.9.1.src.tar.xz.sig :OK"
else
	echo "lld-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- lldb-3.9.1 -----
if [ ! -f lldb-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/lldb-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/lldb-3.9.1.src.tar.xz.sig
fi

gpg --verify lldb-3.9.1.src.tar.xz.sig lldb-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "lldb-3.9.1.src.tar.xz.sig :OK"
else
	echo "lldb-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- openmp-3.9.1 -----
if [ ! -f openmp-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/openmp-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/openmp-3.9.1.src.tar.xz.sig
fi

gpg --verify openmp-3.9.1.src.tar.xz.sig openmp-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "openmp-3.9.1.src.tar.xz.sig :OK"
else
	echo "openmp-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- polly-3.9.1 -----
if [ ! -f polly-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/polly-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/polly-3.9.1.src.tar.xz.sig
fi

gpg --verify polly-3.9.1.src.tar.xz.sig polly-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "polly-3.9.1.src.tar.xz.sig :OK"
else
	echo "polly-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- clang-tools-extra-3.9.1 -----
if [ ! -f clang-tools-extra-3.9.1.src.tar.xz ]; then
	wget http://releases.llvm.org/3.9.1/clang-tools-extra-3.9.1.src.tar.xz
	wget http://releases.llvm.org/3.9.1/clang-tools-extra-3.9.1.src.tar.xz.sig
fi

gpg --verify clang-tools-extra-3.9.1.src.tar.xz.sig clang-tools-extra-3.9.1.src.tar.xz
if [ $? -eq 0 ]; then
	echo "clang-tools-extra-3.9.1.src.tar.xz.sig :OK"
else
	echo "clang-tools-extra-3.9.1.src.tar.xz.sig :NOT OK"
	exit
fi

# ----- end -----


rm -rfvd   BUILD RPMS SOURCES SPECS SRPMS
mkdir -pv  BUILD RPMS SOURCES SPECS SRPMS


cp llvm-3.9.1.src.tar.xz                SOURCES/
cp cfe-3.9.1.src.tar.xz                 SOURCES/
cp compiler-rt-3.9.1.src.tar.xz         SOURCES/
cp libcxx-3.9.1.src.tar.xz              SOURCES/
cp libcxxabi-3.9.1.src.tar.xz           SOURCES/
cp libunwind-3.9.1.src.tar.xz           SOURCES/
cp lld-3.9.1.src.tar.xz                 SOURCES/
cp lldb-3.9.1.src.tar.xz                SOURCES/
cp openmp-3.9.1.src.tar.xz              SOURCES/
cp polly-3.9.1.src.tar.xz               SOURCES/
cp clang-tools-extra-3.9.1.src.tar.xz   SOURCES/


cp clang-3.9.1.spec    SPECS/

rpmbuild -v --sign -bb --clean SPECS/clang-3.9.1.spec

find . -iname '*.rpm'
