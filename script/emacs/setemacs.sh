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



# FillColumnIndicator updated for emacs-25
cd /tmp
# git clone https://github.com/alpaker/Fill-Column-Indicator.git  Fill-Column-Indicator
# if [ ! -d /tmp/Fill-Column-Indicator ]; then
# 	echo "cannot clone Fill-Column-Indicator"
# 	exit
# fi

mkdir -pv $HOME/.emacs.d/lisp
wget http://www.emacswiki.org/emacs/download/fill-column-indicator.el
# cp -v /tmp/Fill-Column-Indicator/fill-column-indicator.el $HOME/.emacs.d/lisp
# rm -rfvd /tmp/Fill-Column-Indicator
cp -v /tmp/fill-column-indicator.el $HOME/.emacs.d/lisp
rm /tmp/fill-column-indicator.el


# Emacs ColorTheme
cd /tmp
wget http://download.savannah.gnu.org/releases/color-theme/color-theme-6.6.0.tar.gz
tar zxvf color-theme-6.6.0.tar.gz
mv color-theme-6.6.0  $HOME/.emacs.d/
rm /tmp/color-theme-6.6.0.tar.gz


# copy .emacs
cp -v $HOME/Code/git-main/script/emacs/emacs  $HOME/.emacs
