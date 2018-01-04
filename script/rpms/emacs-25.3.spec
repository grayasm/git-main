#
# Spec file for emacs-25.3
#
# http://ftp.gnu.org/gnu/emacs/emacs-25.3.tar.xz


%define    _topdir       /home/mihai/rpmbuild
%define    name          emacs253
%define    version       25.3
%define    release       1.el7
%define    buildroot     %{_topdir}/emacs-%{version}-root
%define    debug_package %{nil}


BuildRoot:    %{buildroot}
Summary:      GNU Emacs text editor
License:      GPLv3+ and CC0-1.0
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       emacs-%{version}.tar.xz
Prefix:       /opt/emacs-25.3
Group:        Applications/Editors



%description
Emacs is a powerful, customizable, self-documenting, modeless text
editor. Emacs contains special code editing features, a scripting
language (elisp), and the capability to read mail, news, and more
without leaving the editor.


%prep
rm -rfvd  $RPM_BUILD_DIR/emacs-25.3
unxz -v   $RPM_SOURCE_DIR/emacs-25.3.tar.xz
tar -xvf  $RPM_SOURCE_DIR/emacs-25.3.tar


%build
cd $RPM_BUILD_DIR/emacs-25.3
mkdir emacs-build && cd emacs-build
../configure --prefix=/ \
			 --with-x-toolkit=gtk2
make -j8

%install
cd $RPM_BUILD_DIR/emacs-25.3/emacs-build
make DESTDIR=$RPM_BUILD_ROOT/opt/emacs-25.3 install


%postun
if [ "$1" == "0" ]; then
	rm -rfvd /opt/emacs-25.3
fi


%files
%defattr(-,root,root)



%changelog
* Wed Jan 03 2018 Mihai Vasilian <grayasm@gmail.com> 25.3-1.el7
- Initial package.
