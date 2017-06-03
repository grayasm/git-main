#
# Spec file for libyahoo-plusplus
#
# https://github.com/EionRobb/funyahoo-plusplus/archive/master.zip
#

%define    _topdir       /home/mihai/rpmbuild
%define    name          libyahoo-plusplus
%define    version       0.1
%define    release       1.el7
%define    buildroot     %{_topdir}/%{name}-%{version}-root
%define    debug_package %{nil}


BuildRoot:    %{buildroot}
Summary:      A replacement Yahoo prpl (protocol plugin) for Pidgin/libpurple
License:      GPLv3
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       https://github.com/EionRobb/funyahoo-plusplus/archive/master.zip
#Prefix:      /
Group:        Applications/Internet

BuildRequires:  libpurple-devel, json-glib-devel, glib2-devel
Requires:       git, make, libxml2, libidn, libffi, zlib, xz-libs, pcre

%description
A replacement Yahoo prpl (protocol plugin) for Pidgin/libpurple compatible with
the new protocol enforced by Yahoo since Sept 2016

%prep
rm -rfvd  $RPM_BUILD_ROOT/funyahoo-plusplus-master
unzip     $RPM_SOURCE_DIR/master.zip


%build
cd $RPM_BUILD_DIR/funyahoo-plusplus-master
make %{?_smp_mflags}


%install
cd $RPM_BUILD_DIR/funyahoo-plusplus-master
make install DESTDIR=$RPM_BUILD_ROOT


%files
%defattr(-,root,root)
/usr/lib64/purple-2/libyahoo-plusplus.so


%changelog
* Sun May 28 2017 Mihai Vasilian <grayasm@gmail.com>  0.1-1.el7
- Initial package
