# This is spec file for part2-0 (installed in /tmp/part2)
#
# - %pre hook run before your package is installed.
# - %post hook run after your packages has been installed.
# - %preun hook runs before your package is removed from the system.
# - %postun hook run after your package is removed from the system.


%define _topdir      /home/mihai/Code/git-main/tutorial/martin_streicher_rpm
%define name         part2
%define release      1
%define version      0.1
%define buildroot    %{_topdir}/%{name}-%{version}-root



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
make -f part2-0.mk

%install
make -f part2-0.mk DESTDIR=$RPM_BUILD_ROOT/tmp/part2 install

%files
%defattr(-,root,root)
