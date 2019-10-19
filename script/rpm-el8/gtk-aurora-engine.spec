#
# Spec file for gtk-aurora-engine-1.5.1
#
# ftp://vasilian.net/Gtk-Engines/gtk-aurora-engine-1.5.1.tar.bz2
#


%define    _topdir       /home/mihai/rpmbuild
%define    name          gtk-aurora-engine
%define    version       1.5.1
%define    release       1.el8
%define    buildroot     %{_topdir}/gtk-aurora-engine-%{version}-root
%define    debug_package %{nil}


BuildRoot:    %{buildroot}
Summary:      Gtk+ engine for Aurora
License:      LGPLv2
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       %{name}-%{version}.tar.gz
Prefix:       /usr
Group:        User Interface/X
Requires:     gtk2-devel





%description
Gtk+ engine for Aurora.


%prep
rm -rfvd  $RPM_BUILD_DIR/gtk-aurora-engine-1.5.1
tar -zxvf $RPM_SOURCE_DIR/gtk-aurora-engine-1.5.1.tar.gz


%build
cd $RPM_BUILD_DIR/gtk-aurora-engine-1.5.1
# by default installs into /usr/lib instead of /usr/lib64
./configure --prefix=%{_prefix} --libdir=%{_libdir}
make -j8

%install
cd $RPM_BUILD_DIR/gtk-aurora-engine-1.5.1
make DESTDIR=$RPM_BUILD_ROOT install


%postun
if [ "$1" == "0" ]; then
    rm -rfv %{_libdir}/gtk-2.0/2.10.0/engines/libaurora.la
    rm -rfv %{_libdir}/gtk-2.0/2.10.0/engines/libaurora.so
fi


%files
%defattr(-,root,root)
%{_libdir}/gtk-2.0/2.10.0/engines/libaurora.la
%{_libdir}/gtk-2.0/2.10.0/engines/libaurora.so


%changelog
* Sat Oct 19 2019 Mihai Vasilian <grayasm@gmail.com> 1.5.1-1.el8
- Initial package.
