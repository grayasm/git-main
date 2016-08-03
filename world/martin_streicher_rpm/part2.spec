# This is a spec file for a dummy program 'part2'

%define _topdir     /home/mihai/Code/git-main/world/martin_streicher_rpm
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
Source:        %{name}.cpp
Prefix:        /tmp/part2
Group:         Development/Tools



%description
The GNU part2 dummy program.

%prep

%build
make -f part2.mk

%install
make -f part2.mk DESTDIR=$RPM_BUILD_ROOT/tmp/part2 install

%files
%defattr(-,root,root)
/tmp/part2/bin/part2
/tmp/part2/share/icons/part2.png