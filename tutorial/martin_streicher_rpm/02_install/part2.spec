# This is spec file for simple part2 (installed in /tmp/part2)
#
# The simplest case of deployment is when system lacks:
#    - you package's daemons
#    - binaries
#    - configuration files
#    - data files
#
# The installation need not stop work in progress or back up, restore and
# possibly merge files.

%define _topdir     /home/mihai/Code/git-main/tutorial/martin_streicher_rpm
%define name        part2
%define release     1
%define version     0.1
%define buildroot   %{_topdir}/%{name}-%{version}-root


BuildRoot:     %{buildroot}
Summary:       GNU part2
License:       GPL
Name:          %{name}
Version:       %{version}
Release:       %{release}
Source:        %{name}-%{version}.tar.gz
Prefix:        /tmp/part2
Group:         Development/Tools



%description
The GNU part2 dummy program.

%prep
%setup -q

%build
make -f part2.mk

%install
make -f part2.mk DESTDIR=$RPM_BUILD_ROOT/tmp/part2 install

%files
%defattr(-,root,root)
/tmp/part2/bin/part2
/tmp/part2/share/icons/part2.png
