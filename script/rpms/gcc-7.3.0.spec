#
# Spec file for gcc-7.3.0
#
# ftp://gcc.gnu.org/pub/gcc/releases/gcc-7.3.0/gcc-7.3.0.tar.gz
# ftp://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-7.3.0/gcc-7.3.0.tar.gz


%define    _topdir       /home/mihai/rpmbuild
%define    name          gcc730
%define    version       7.3.0
%define    release       1.el7
%define    buildroot     %{_topdir}/gcc-%{version}-root
%define    debug_package %{nil}


BuildRoot:    %{buildroot}
Summary:      GNU gcc compiler version 7.3.0 for C,C++ and FORTRAN.
License:      GPL
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       gcc-%{version}.tar.gz
Prefix:       /opt/gcc-7.3.0
Group:        Development/Tools




%description
The GNU gcc compiler version 7.3.0 for C,C++ and FORTRAN.


%prep
rm -rfvd  $RPM_BUILD_DIR/gcc-7.3.0
tar -zxvf $RPM_SOURCE_DIR/gcc-7.3.0.tar.gz


%build
cd $RPM_BUILD_DIR/gcc-7.3.0
mkdir gcc-build && cd gcc-build
../configure --prefix=/ \
			 --enable-libstdcxx \
			 --enable-bootstrap \
			 --enable-lto \
			 --enable-shared \
			 --enable-clocale=gnu \
			 --enable-threads=posix \
			 --enable-__cxa_atexit  \
			 --enable-languages=c,c++,fortran \
			 --enable-multilib \
			 --enable-libgomp \
			 --with-system-zlib
make -j8

%install
cd $RPM_BUILD_DIR/gcc-7.3.0/gcc-build
make DESTDIR=$RPM_BUILD_ROOT/opt/gcc-7.3.0 install


%postun
if [ "$1" == "0" ]; then
	rm -rfvd /opt/gcc-7.3.0
fi


%files
%defattr(-,root,root)


%changelog
* Fri Sep 13 2019 Mihai Vasilian <grayasm@gmail.com> 7.3.0-1.el7
- Initial package.
