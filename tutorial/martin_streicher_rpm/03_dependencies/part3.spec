# This is spec file for part3 (dependencies)
#
# When you create a RPM package, you can declare four types of dependencies:
# Requires, Provides, Conflicts, Obsoletes
#
# Requires:  to define a requirement,
# Provides:  declare the capability your package provides,
# Conflicts: for when it cannot coexist simultaneously with another package,
# Obsoletes: when it deprecates another package or an older version of itself.
#
# There are six comparisons for version number (<, >, >=, <=, =, package)

%define _topdir      /home/mihai/Code/git-main/tutorial/martin_streicher_rpm/03_dependencies
%define name         part3
%define release      1.el7
%define version      0.1
%define buildroot    %{_topdir}/%{name}-%{version}-root



BuildRoot:     %{buildroot}
Summary:       GNU part3
License:       GPL
Name:          %{name}
Version:       %{version}
Release:       %{release}
Source:        %{name}-%{version}.tar.gz
Prefix:        /tmp/part3
Group:         Development/Tools

Requires:      zlib >= 5.5, man < 2.0
Provides:      part3
Conflicts:     gcc > 3.0, gdb = 5
Obsoletes:     zcat


%description
The GNU part3 dummy program.

%prep
%setup -q

%build
make -f part3.mk

%install
make -f part3.mk DESTDIR=$RPM_BUILD_ROOT/tmp/part3 install

%clean
rm -rf $RPM_BUILD_ROOT



%files
%defattr(-,root,root)
/tmp/part3/bin/part3


%changelog
* Sun Aug 10 2016 Mihai Vasilian <grayasm@gmail.com> 0.1-1.el7
- Initial package
