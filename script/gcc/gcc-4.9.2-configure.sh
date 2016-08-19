#!/bin/bash



# wget ftp://gcc.gnu.org/pub/gcc/releases/gcc-4.9.2/gcc-4.9.2.tar.gz


# --disable-bootstrap
# --enable-bootstrap
# --disable-multilib
# --enable-stage1-languages=c,c++ \
# --enable-stage1-checking=c,c++ \
#  MAKEINFO=missing

../gcc-4.9.2/configure --prefix=/opt/gcc-4.9.2 \
					   --enable-libstdcxx \
					   --enable-bootstrap \
					   --enable-lto \
					   --enable-shared \
					   --enable-clocale=gnu \
					   --enable-threads=posix \
					   --enable-__cxa_atexit  \
					   --enable-languages=c,c++ \
					   --enable-multilib \
					   --enable-libgomp \
					   --with-system-zlib
					   
# make DESTDIR=/opt/gcc-4.9.2  install
