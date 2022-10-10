#
# Spec file for mac-fonts
#
# The current archive contains fonts relased with some versions of MacOS.
#
# ftp://vasilian.net/Gtk-Themes/mac-fonts.tar.gz


%define    _topdir       /home/mihai/rpmbuild
%define    name          mac-fonts
%define    version       1.1
%define    release       1.el9
%define    buildroot     %{_topdir}/%{name}-%{version}-root


BuildRoot:    %{buildroot}
Summary:      MacOS fonts
License:      Proprietary
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       %{name}.tar.gz
Prefix:       /
Group:        User Interface/X
Requires:     freetype, fontconfig



%description
MacOS fonts.


%prep
rm -rfvd  $RPM_BUILD_DIR/mac-fonts
tar -zxvf $RPM_SOURCE_DIR/mac-fonts.tar.gz
cp -v     $RPM_SOURCE_DIR/mac-fonts.mk  $RPM_BUILD_DIR/mac-fonts/Makefile


%build
cd $RPM_BUILD_DIR/mac-fonts
make all

%install
cd $RPM_BUILD_DIR/mac-fonts
make DESTDIR=$RPM_BUILD_ROOT/usr/share/fonts/mac-fonts install


%post
if [ "$1" == "1" ]; then
    fc-cache --force --system-only --verbose  /usr/share/fonts/mac-fonts
fi

%postun
if [ "$1" == "0" ]; then
    rm -rfvd /usr/share/fonts/mac-fonts
    fc-cache --force --system-only --verbose  /usr/share/fonts/
fi



%files
%defattr(-,root,root)
/usr/share/fonts/mac-fonts/HelveticaNeue/Helvetica-Neu-Bold.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeue-BlackCond.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeue-Light.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeue-Medium.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeue-Thin.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeue.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeueBd.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeueHv.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeueIt.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeueLt.ttf
/usr/share/fonts/mac-fonts/HelveticaNeue/HelveticaNeueMed.ttf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-Black.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-Bold.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-Heavy.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-Light.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-Medium.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-Regular.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-SemiBold.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-Semibold.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-Thin.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-UltraLight.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactDisplay-Ultralight.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-Bold.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-BoldItalic.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-Heavy.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-HeavyItalic.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-Light.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-LightItalic.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-Medium.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-MediumItalic.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-Regular.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-RegularItalic.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-SemiBold.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-SemiBoldItalic.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-Semibold.otf
/usr/share/fonts/mac-fonts/SFCompact_otf/SFCompactText-SemiboldItalic.otf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactDisplay-Black.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactDisplay-Bold.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactDisplay-Heavy.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactDisplay-Light.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactDisplay-Medium.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactDisplay-Regular.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactDisplay-SemiBold.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactDisplay-Thin.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactDisplay-UltraLight.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-Bold.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-BoldItalic.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-Heavy.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-HeavyItalic.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-Light.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-LightItalic.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-Medium.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-MediumItalic.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-Regular.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-RegularItalic.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-SemiBold.ttf
/usr/share/fonts/mac-fonts/SFCompact_ttf/SFCompactText-SemiBoldItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-Black.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-BlackItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-Bold.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-BoldItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-Heavy.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-HeavyItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-Light.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-LightItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-Medium.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-MediumItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-Regular.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-RegularItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-Semibold.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-SemiboldItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-Thin.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-ThinItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-Ultralight.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Display-UltralightItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-Bold.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-BoldItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-Heavy.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-HeavyItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-Light.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-LightItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-Medium.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-MediumItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-Regular.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-RegularItalic.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-Semibold.otf
/usr/share/fonts/mac-fonts/SFPro_otf/SF-Pro-Text-SemiboldItalic.otf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-Black.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-BlackItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-Bold.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-BoldItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-Heavy.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-HeavyItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-Light.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-LightItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-Medium.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-MediumItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-Regular.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-RegularItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-SemiBold.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-Semibold.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-SemiboldItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-Thin.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-ThinItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-UltraLight.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-Ultralight.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProDisplay-UltralightItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-Bold.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-BoldItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-Heavy.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-HeavyItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-Light.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-LightItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-Medium.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-MediumItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-Regular.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-RegularItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-SemiBold.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-SemiBoldItalic.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-Semibold.ttf
/usr/share/fonts/mac-fonts/SFPro_ttf/SFProText-SemiboldItalic.ttf
/usr/share/fonts/mac-fonts/SFMono/SFMonoBoldItalic.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoBold.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoHeavyItalic.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoHeavy.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoLightItalic.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoLight.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoMediumItalic.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoMedium.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoRegularItalic.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoRegular.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoSemiboldItalic.otf
/usr/share/fonts/mac-fonts/SFMono/SFMonoSemibold.otf


%changelog
* Mon Oct 10 2022 Mihai Vasilian <grayasm@gmail.com> 1.1-1.el9
- Create the package for el9.
* Sun Oct 20 2019 Mihai Vasilian <grayasm@gmail.com> 1.0-1.el8
- Create the package for el8.
* Tue Feb 5 2019 Mihai Vasilian <grayasm@gmail.com> 1.0-1.el7
- Initial package.
