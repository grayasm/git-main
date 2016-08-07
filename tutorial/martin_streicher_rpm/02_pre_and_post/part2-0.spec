# This is spec file for part2-0 (installed in /tmp/part2)
#
# - %pre hook run before your package is installed.
# - %post hook run after your packages has been installed.
# - %preun hook runs before your package is removed from the system.
# - %postun hook run after your package is removed from the system.


%define _topdir      /home/mihai/Code/git-main/tutorial/martin_streicher_rpm/02_pre_and_post
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

%clean
rm -rf $RPM_BUILD_ROOT


# http://pkgs.fedoraproject.org/cgit/rpms/autossh.git/tree/autossh.spec#n53
%pre
if [ "$1" == "1" ]; then
	echo "spec: %{name}-%{version} run %pre $1 hook before install"
elif [ "$1" == "2" ]; then
	echo "spec: %{name}-%{version} run %pre $1 hook before upgrade"
fi

%post
if [ "$1" == "1" ]; then
	echo "spec: %{name}-%{version} run %post $1 hook after install"
elif [ "$1" == "2" ]; then
	echo "spec: %{name}-%{version} run %post $1 hook after upgrade"
fi

%preun
if [ "$1" == "0" ]; then
	echo "spec: %{name}-%{version} run %preun $1 hook before uninstall"
elif [ "$1" == "1" ]; then
	echo "spec: %{name}-%{version} run %preun $1 hook before upgrade"
fi

%postun
if [ "$1" == "0" ]; then
	echo "spec: %{name}-%{version} run %preun $1 hook after uninstall"
elif [ "$1" == "1" ]; then
	echo "spec: %{name}-%{version} run %preun $1 hook after upgrade"
fi



%files
%defattr(-,root,root)
/tmp/part2/bin/part2
/tmp/part2/etc/config2.0


%changelog
* Sun Aug 6 2016 Mihai Vasilian <grayasm@gmail.com> 0.1-1
- Initial package
