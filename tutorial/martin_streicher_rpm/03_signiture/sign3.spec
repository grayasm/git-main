# This is spec file for sign3 sample (Signing your RPM)
#
# See README.txt for instructions about how to setup gpg.
# This file is no different than a normal spec file.
# The only difference is in $HOME/.rpmmacros and the rpmbuild command.
#
# Note: I tried to add the macros from $HOME/.rpmmacros here but:
# error: line 9: Unknown tag: %_signature   gpg
#

%define _topdir      /home/mihai/Code/git-main/tutorial/martin_streicher_rpm/03_signiture
%define name         sign3
%define release      1.el7
%define version      0.1
%define buildroot    %{_topdir}/%{name}-%{version}-root

BuildRoot:     %{buildroot}
Summary:       GNU sign3
License:       GPL
Name:          %{name}
Version:       %{version}
Release:       %{release}
Source:        %{name}-%{version}.tar.gz
Prefix:        /tmp/sign3
Group:         Development/Tools



%description
The GNU sign3 dummy program.

# error: Empty %files file debugsourcefiles.list
%global debug_package %{nil}

%prep
%setup -q

%build
make -f sign3.mk

%install
make -f sign3.mk DESTDIR=$RPM_BUILD_ROOT/tmp/sign3 install

%clean
rm -rf $RPM_BUILD_ROOT



%files
%defattr(-,root,root)
/tmp/sign3/bin/sign3


%changelog
* Sat Oct 1 2022 Mihai Vasilian <grayasm@gmail.com>
- Add debug_package
* Sun Aug 14 2016 Mihai Vasilian <grayasm@gmail.com> 0.1-1.el7
- Initial package with signiture.
