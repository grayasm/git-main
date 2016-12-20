#
# Spec file for OSTree release 2016.14 @2016-11-23 10:42:39 -0500
# built with libglnx revision abd37a4790f86f53bfb442e6d80e1710f50bff92
#
# https://github.com/ostreedev/ostree.git
# https://github.com/GNOME/libglnx.git
#

%define    _topdir       /home/mihai/rpmbuild
%define    name          ostree
%define    version       2016.14
%define    release       1.el7
%define    buildroot     %{_topdir}/%{name}-%{vesion}-root
%define    debug_package %{nil}


BuildRoot:    %{buildroot}
Summary:      OSTree bootable filesystem trees, v2016.14 released 2016-11-23.
License:      GPL
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       ostree-%{version}.tar.gz
# Prefix:     /
Group:        Development/Libraries


%description
OSTree is a tool that combines a "git-like" model for commiting and
downloading bootable filesystem trees, along with a layer for
deploying them and managing the bootloader configuration.

%prep
rm -rfvd   $RPM_BUILD_DIR/ostree-2016.14
tar -zxvf  $RPM_SOURCE_DIR/ostree-2016.14.tar.gz


%build
cd $RPM_BUILD_DIR/ostree-2016.14
env NOCONFIGURE=1 ./autogen.sh
./configure --prefix=/usr \
            --libdir=/usr/lib64 \
            --disable-silent-rules
make %{?_smp_mflags}


%install
cd $RPM_BUILD_DIR/ostree-2016.14
make install DESTDIR=$RPM_BUILD_ROOT INSTALL="install -p -c"


%files
%defattr(-,root,root)
/usr/bin/ostree
/usr/bin/rofiles-fuse
/usr/etc/grub.d/15_ostree
/usr/include/ostree-1/ostree-async-progress.h
/usr/include/ostree-1/ostree-autocleanups.h
/usr/include/ostree-1/ostree-bootconfig-parser.h
/usr/include/ostree-1/ostree-core.h
/usr/include/ostree-1/ostree-deployment.h
/usr/include/ostree-1/ostree-diff.h
/usr/include/ostree-1/ostree-dummy-enumtypes.h
/usr/include/ostree-1/ostree-gpg-verify-result.h
/usr/include/ostree-1/ostree-mutable-tree.h
/usr/include/ostree-1/ostree-repo-deprecated.h
/usr/include/ostree-1/ostree-repo-file.h
/usr/include/ostree-1/ostree-repo.h
/usr/include/ostree-1/ostree-sepolicy.h
/usr/include/ostree-1/ostree-sysroot-upgrader.h
/usr/include/ostree-1/ostree-sysroot.h
/usr/include/ostree-1/ostree-types.h
/usr/include/ostree-1/ostree.h
/usr/lib/ostree/ostree-prepare-root
/usr/lib/ostree/ostree-remount
/usr/lib/systemd/system/ostree-prepare-root.service
/usr/lib/systemd/system/ostree-remount.service
/usr/lib64/girepository-1.0/OSTree-1.0.typelib
/usr/lib64/libostree-1.la
/usr/lib64/libostree-1.so
/usr/lib64/libostree-1.so.1
/usr/lib64/libostree-1.so.1.0.0
/usr/lib64/pkgconfig/ostree-1.pc
/usr/libexec/ostree/grub2-15_ostree
/usr/share/gir-1.0/OSTree-1.0.gir
/usr/share/man/man1/ostree-admin-cleanup.1.gz
/usr/share/man/man1/ostree-admin-config-diff.1.gz
/usr/share/man/man1/ostree-admin-deploy.1.gz
/usr/share/man/man1/ostree-admin-init-fs.1.gz
/usr/share/man/man1/ostree-admin-instutil.1.gz
/usr/share/man/man1/ostree-admin-os-init.1.gz
/usr/share/man/man1/ostree-admin-set-origin.1.gz
/usr/share/man/man1/ostree-admin-status.1.gz
/usr/share/man/man1/ostree-admin-switch.1.gz
/usr/share/man/man1/ostree-admin-undeploy.1.gz
/usr/share/man/man1/ostree-admin-unlock.1.gz
/usr/share/man/man1/ostree-admin-upgrade.1.gz
/usr/share/man/man1/ostree-admin.1.gz
/usr/share/man/man1/ostree-cat.1.gz
/usr/share/man/man1/ostree-checkout.1.gz
/usr/share/man/man1/ostree-checksum.1.gz
/usr/share/man/man1/ostree-commit.1.gz
/usr/share/man/man1/ostree-config.1.gz
/usr/share/man/man1/ostree-diff.1.gz
/usr/share/man/man1/ostree-export.1.gz
/usr/share/man/man1/ostree-fsck.1.gz
/usr/share/man/man1/ostree-gpg-sign.1.gz
/usr/share/man/man1/ostree-init.1.gz
/usr/share/man/man1/ostree-log.1.gz
/usr/share/man/man1/ostree-ls.1.gz
/usr/share/man/man1/ostree-prune.1.gz
/usr/share/man/man1/ostree-pull-local.1.gz
/usr/share/man/man1/ostree-pull.1.gz
/usr/share/man/man1/ostree-refs.1.gz
/usr/share/man/man1/ostree-remote.1.gz
/usr/share/man/man1/ostree-reset.1.gz
/usr/share/man/man1/ostree-rev-parse.1.gz
/usr/share/man/man1/ostree-show.1.gz
/usr/share/man/man1/ostree-static-delta.1.gz
/usr/share/man/man1/ostree-summary.1.gz
/usr/share/man/man1/ostree-trivial-httpd.1.gz
/usr/share/man/man1/ostree.1.gz
/usr/share/man/man1/rofiles-fuse.1.gz
/usr/share/man/man5/ostree.repo-config.5.gz
/usr/share/man/man5/ostree.repo.5.gz
/usr/share/ostree/trusted.gpg.d/README-gpg


%changelog
* Tue Dec 20 2016 Mihai Vasilian <grayasm@gmail.com> 2016.14-1.el7
- Initial package.
