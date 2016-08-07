# This is a spec file for wget

%define _topdir   /home/mihai/Code/git-main/tutorial/martin_streicher_rpm
%define name      wget
%define release   1
%define version   1.18
%define buildroot %{_topdir}/%{name}-%{version}-root

BuildRoot:    %{buildroot}
Summary:      GNU wget
License:      GPL
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       %{name}-%{version}.tar.gz
Prefix:       /opt/wget
Group:        Development/Tools


%description
The GNU wget program downloads files from the Internet using the command-line.

%prep
%setup -q

%build
./configure
make

%install
make install prefix=$RPM_BUILD_ROOT/opt/wget

%files
%defattr(-,root,root)
/opt/wget/bin/wget

%doc %attr(0444,root,root)   /opt/wget/share/man/man1/wget.1
%doc %attr(0444,root,root)   /opt/wget/etc/wgetrc
%doc %attr(0444,root,root)   /opt/wget/share/info/dir
%doc %attr(0444,root,root)   /opt/wget/share/info/wget.info
%doc %attr(0444,root,root)   /opt/wget/share/locale/be/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/bg/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/ca/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/cs/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/da/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/de/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/el/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/en_GB/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/eo/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/es/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/et/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/eu/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/fi/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/fr/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/ga/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/gl/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/he/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/hr/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/hu/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/id/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/it/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/ja/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/lt/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/nb/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/nl/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/pl/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/pt/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/pt_BR/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/ro/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/ru/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/sk/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/sl/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/sr/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/sv/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/tr/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/uk/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/vi/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/zh_CN/LC_MESSAGES/wget.mo
%doc %attr(0444,root,root)   /opt/wget/share/locale/zh_TW/LC_MESSAGES/wget.mo
