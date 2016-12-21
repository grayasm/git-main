#
# Spec file for Flatpak release 0.6.14 @2016-11-29
# + bubblewrap release 0.1.4  @2016-11-29
# + libglnx revision abd37a4790f86f53bfb442e6d80e1710f50bff92
#
# https://github.com/flatpak/flatpak.git
# https://github.com/projectatomic/bubblewrap.git
# https://github.com/GNOME/libglnx.git
#

%define    _topdir       /home/mihai/rpmbuild
%define    name          flatpak
%define    version       0.6.14
%define    release       1.el7
%define    buildroot     %{_topdir}/%{name}-%{vesion}-root
%define    debug_package %{nil}


BuildRoot:    %{buildroot}
Summary:      Flatpak framework for desktop applications on Linux
License:      GPL
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       flatpak-%{version}.tar.gz
#Prefix:      /usr
Group:        Development/Libraries


BuildRequires:    json-glib-devel, gpgme-devel, xz-devel, zlib-devel
BuildRequires:    libarchive-devel, systemd-devel, libmount-devel
BuildRequires:    libselinux-devel, libsoup-devel, glib2-devel, libXau-devel
BuildRequires:    libseccomp-devel, glibc-devel, glibc-headers, glibc-common
BuildRequires:    libgpg-error-devel, libxml2-devel, libcap-devel
BuildRequires:    libblkid-devel, libuuid-devel, pcre-devel, libffi-devel
BuildRequires:    elfutils-libelf-devel


Requires:     json-glib, ostree, gpgme, xz-libs, zlib, libarchive, systemd-libs
Requires:     libmount, libselinux, libsoup, glib2, libXau, libseccomp, glibc
Requires:     libassuan, libgpg-error, openssl-libs, libacl, libattr, lzo
Requires:     bzip2-libs, libxml2, libcap, libgcrypt, elfutils-libs
Requires:     libgcc, libblkid, libuuid, pcre, sqlite, libffi, elfutils-libelf



%description
Flatpak is the new framework for desktop applications on Linux. It allows
the same app to be installed on different Linux distributions, including
different version.

%prep
rm -rfvd   $RPM_BUILD_DIR/flatpak-0.6.14
tar -zxvf  $RPM_SOURCE_DIR/flatpak-0.6.14.tar.gz


%build
cd $RPM_BUILD_DIR/flatpak-0.6.14
./autogen.sh --with-dwarf-header=/usr/include/libdwarf

./configure --prefix=/usr \
            --libdir=/usr/lib64 \
            --with-dwarf-header=/usr/include/libdwarf \
            --disable-silent-rules
make %{?_smp_mflags}


%install
cd $RPM_BUILD_DIR/flatpak-0.6.14
make install DESTDIR=$RPM_BUILD_ROOT INSTALL="install -p -c"


%files
%defattr(-,root,root)
/usr/bin/flatpak
/usr/bin/flatpak-builder
/usr/etc/dbus-1/system.d/org.freedesktop.Flatpak.SystemHelper.conf
/usr/etc/profile.d/flatpak.sh
/usr/include/flatpak/flatpak-bundle-ref.h
/usr/include/flatpak/flatpak-enum-types.h
/usr/include/flatpak/flatpak-error.h
/usr/include/flatpak/flatpak-installation.h
/usr/include/flatpak/flatpak-installed-ref.h
/usr/include/flatpak/flatpak-ref.h
/usr/include/flatpak/flatpak-related-ref.h
/usr/include/flatpak/flatpak-remote-ref.h
/usr/include/flatpak/flatpak-remote.h
/usr/include/flatpak/flatpak-version-macros.h
/usr/include/flatpak/flatpak.h
/usr/lib/systemd/system/flatpak-system-helper.service
/usr/lib/systemd/user/dbus.service.d/flatpak.conf
/usr/lib/systemd/user/flatpak-session-helper.service
/usr/lib/systemd/user/xdg-document-portal.service
/usr/lib/systemd/user/xdg-permission-store.service
/usr/lib64/girepository-1.0/Flatpak-1.0.typelib
/usr/lib64/libflatpak.la
/usr/lib64/libflatpak.so
/usr/lib64/libflatpak.so.0
/usr/lib64/libflatpak.so.0.600.14
/usr/lib64/pkgconfig/flatpak.pc
/usr/libexec/flatpak-bwrap
/usr/libexec/flatpak-dbus-proxy
/usr/libexec/flatpak-session-helper
/usr/libexec/flatpak-system-helper
/usr/libexec/xdg-document-portal
/usr/libexec/xdg-permission-store
/usr/share/bash-completion/completions/flatpak
/usr/share/dbus-1/interfaces/org.freedesktop.Flatpak.xml
/usr/share/dbus-1/interfaces/org.freedesktop.impl.portal.PermissionStore.xml
/usr/share/dbus-1/interfaces/org.freedesktop.portal.Documents.xml
/usr/share/dbus-1/services/org.freedesktop.Flatpak.service
/usr/share/dbus-1/services/org.freedesktop.impl.portal.PermissionStore.service
/usr/share/dbus-1/services/org.freedesktop.portal.Documents.service
/usr/share/dbus-1/system-services/org.freedesktop.Flatpak.SystemHelper.service
/usr/share/flatpak/triggers/desktop-database.trigger
/usr/share/flatpak/triggers/gtk-icon-cache.trigger
/usr/share/flatpak/triggers/mime-database.trigger
/usr/share/gdm/env.d/flatpak.env
/usr/share/gir-1.0/Flatpak-1.0.gir
/usr/share/locale/de/LC_MESSAGES/flatpak.mo
/usr/share/locale/hu/LC_MESSAGES/flatpak.mo
/usr/share/locale/pl/LC_MESSAGES/flatpak.mo
/usr/share/locale/sk/LC_MESSAGES/flatpak.mo
/usr/share/locale/sv/LC_MESSAGES/flatpak.mo
/usr/share/locale/uk/LC_MESSAGES/flatpak.mo
/usr/share/man/man1/flatpak-build-bundle.1.gz
/usr/share/man/man1/flatpak-build-commit-from.1.gz
/usr/share/man/man1/flatpak-build-export.1.gz
/usr/share/man/man1/flatpak-build-finish.1.gz
/usr/share/man/man1/flatpak-build-import-bundle.1.gz
/usr/share/man/man1/flatpak-build-init.1.gz
/usr/share/man/man1/flatpak-build-sign.1.gz
/usr/share/man/man1/flatpak-build-update-repo.1.gz
/usr/share/man/man1/flatpak-build.1.gz
/usr/share/man/man1/flatpak-builder.1.gz
/usr/share/man/man1/flatpak-document-export.1.gz
/usr/share/man/man1/flatpak-document-info.1.gz
/usr/share/man/man1/flatpak-document-list.1.gz
/usr/share/man/man1/flatpak-document-unexport.1.gz
/usr/share/man/man1/flatpak-enter.1.gz
/usr/share/man/man1/flatpak-info.1.gz
/usr/share/man/man1/flatpak-install.1.gz
/usr/share/man/man1/flatpak-list.1.gz
/usr/share/man/man1/flatpak-make-current.1.gz
/usr/share/man/man1/flatpak-override.1.gz
/usr/share/man/man1/flatpak-remote-add.1.gz
/usr/share/man/man1/flatpak-remote-delete.1.gz
/usr/share/man/man1/flatpak-remote-list.1.gz
/usr/share/man/man1/flatpak-remote-ls.1.gz
/usr/share/man/man1/flatpak-remote-modify.1.gz
/usr/share/man/man1/flatpak-run.1.gz
/usr/share/man/man1/flatpak-uninstall.1.gz
/usr/share/man/man1/flatpak-update.1.gz
/usr/share/man/man1/flatpak.1.gz
/usr/share/man/man5/flatpak-flatpakref.5.gz
/usr/share/man/man5/flatpak-flatpakrepo.5.gz
/usr/share/man/man5/flatpak-metadata.5.gz
/usr/share/polkit-1/actions/org.freedesktop.Flatpak.policy
/usr/share/polkit-1/rules.d/org.freedesktop.Flatpak.rules


%changelog
* Wed Dec 21 2016 Mihai Vasilian <grayasm@gmail.com> 0.6.14-1.el7
- Initial package.
