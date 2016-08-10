# This is spec file for part3 (dependencies)
#
# When you create a RPM package, you can declare four types of dependencies:
# Requires, Provides, Conflicts, Obsoletes


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

Requires:      zlib >= 5.5
Provides:      part3-0.1-1.el7
Conflicts:     part3-0.1-1.el7
Obsoletes:     part3-0.1-1.el7


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
