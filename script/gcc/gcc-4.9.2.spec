#
# Spec file for gcc-4.9.2
#



%define    _topdir       /home/mihai/Code/git-main/script/gcc
%define    name          gcc
%define    version       4.9.2
%define    release       1
%define    buildroot     %{_topdir}/%{name}-%{version}-root
%define    debug_package %{nil}


BuildRoot:    %{buildroot}
Summary:      GNU gcc compiler version 4.9.2
License:      GPL
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       %{name}-%{version}.tar.gz
Prefix:       /opt/gcc-4.9.2
Group:        Development/Tools




%description
The GNU gcc compiler version 4.9.2

%prep
%setup -q

%build
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
cd gcc-build
make DESTDIR=$RPM_BUILD_ROOT/opt/gcc-4.9.2 install

%postun
if [ "$1" == "0" ]; then
	rm -rfvd /opt/gcc-4.9.2
fi


%files
%defattr(-,root,root)


%changelog
* Sun Aug 19 2016 Mihai Vasilian <grayasm@gmail.com> 4.9.2
- My first package (gcc-4.9.2)
