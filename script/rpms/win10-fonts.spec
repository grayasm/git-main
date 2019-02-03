#
# Spec file for win10-fonts
#
# The current archive contains fonts from Win7, Win8 and Win10.
# The .fon fonts could not be converted with fontforge+autotrace, so they got
# removed from the package.
#
# ftp://vasilian.net/Misc/win10-fonts.tar.gz


%define    _topdir       /home/mihai/rpmbuild
%define    name          win10-fonts
%define    version       1.1
%define    release       1.el7
%define    buildroot     %{_topdir}/%{name}-%{version}-root


BuildRoot:    %{buildroot}
Summary:      Windows 10 fonts
License:      Proprietary
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       %{name}.tar.gz
Prefix:       /
Group:        User Interface/X
Requires:     freetype, fontconfig



%description
Windows 10 fonts.


%prep
rm -rfvd  $RPM_BUILD_DIR/win10-fonts
tar -zxvf $RPM_SOURCE_DIR/win10-fonts.tar.gz


%build
cd $RPM_BUILD_DIR/win10-fonts
make all

%install
cd $RPM_BUILD_DIR/win10-fonts
make DESTDIR=$RPM_BUILD_ROOT/usr/share/fonts/win10-fonts install


%post
if [ "$1" == "1" ]; then
	fc-cache --force --system-only --verbose  /usr/share/fonts/win10-fonts
fi

%postun
if [ "$1" == "0" ]; then
	rm -rfvd /usr/share/fonts/win10-fonts
	fc-cache --force --system-only --verbose  /usr/share/fonts/
fi



%files
%defattr(-,root,root)



%changelog
* Sun Feb 3 2019 Mihai Vasilian <grayasm@gmail.com> 1.1-1.el7
- Collected the fonts from Win7, Win8 and Win10. Total 402 files.
* Sun Oct 2 2016 Mihai Vasilian <grayasm@gmail.com> 1.0-1.el7
- Initial package.
