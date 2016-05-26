#!/bin/bash

# print every command
set -x 

# need git
git --version 2>&1 >/dev/null
GIT_IS_AVAILABLE=$?
if [ $GIT_IS_AVAILABLE -ne 0 ]; then
	echo "install git"
	exit
fi

# need wget
wget --version 2>&1 >/dev/null
WGET_IS_AVAILABLE=$?
if [ $WGET_IS_AVAILABLE -ne 0 ]; then
	echo "install wget"
	exit
fi


# lusty explorer
cd /tmp
git clone https://github.com/sjbach/lusty-emacs.git lusty-emacs
if [ ! -d /tmp/lusty-emacs ]; then
	echo "cannot clone lusty-emacs"
	exit
fi

mkdir -pv $HOME/.emacs.d/lisp/
cp -v /tmp/lusty-emacs/lusty-explorer.el  $HOME/.emacs.d/lisp/
rm -rfvd /tmp/lusty-emacs



# FillColumnIndicator
cd /tmp
git clone https://github.com/alpaker/Fill-Column-Indicator.git  Fill-Column-Indicator
if [ ! -d /tmp/Fill-Column-Indicator ]; then
	echo "cannot clone Fill-Column-Indicator"
	exit
fi

mkdir -pv $HOME/.emacs.d/lisp
cp -v /tmp/Fill-Column-Indicator/fill-column-indicator.el $HOME/.emacs.d/lisp
rm -rfvd /tmp/Fill-Column-Indicator


# Emacs ColorTheme
cd /tmp
wget http://download.savannah.gnu.org/releases/color-theme/color-theme-6.6.0.tar.gz
tar zxvf color-theme-6.6.0.tar.gz
mv color-theme-6.6.0  $HOME/.emacs.d/
rm /tmp/color-theme-6.6.0.tar.gz



# auto-complete, fuzzy matching
# https://github.com/auto-complete/auto-complete.git
cd /tmp
wget https://github.com/auto-complete/auto-complete/archive/v1.3.1.tar.gz
tar zxvf v1.3.1.tar.gz   # it will unzip into auto-complete-1.3.1
rm v1.3.1.tar.gz
# eval not working
# emacs --batch --eval '(load-file /tmp/auto-complete-1.3.1/etc/install.el)'
echo "TODO: in emacs, load-file /tmp/auto-complete-1.3.1/etc/install.el"

# copy .emacs
cp -v $HOME/Code/git-main/script/emacs/emacs  $HOME/.emacs
