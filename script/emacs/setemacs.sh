#!/bin/bash

# cp $PWD/setemacs.sh $HOME/Code/git-main/script/emacs/setemacs.sh
# svn status $HOME/Code/git-main
# svn diff   $HOME/Code/git-main
# svn commit $HOME/Code/git-main


# lusty explorer
mkdir -pv $HOME/.emacs.d/lisp/
cd $HOME/.emacs.d/lisp/
wget http://www.emacswiki.org/emacs/download/lusty-explorer.el

# auto-complete, fuzzy matching
# https://github.com/auto-complete/auto-complete.git
cd /tmp
wget https://github.com/auto-complete/auto-complete/archive/v1.3.1.tar.gz
tar zxvf v1.3.1.tar.gz   # it will unzip into auto-complete-1.3.1
rm v1.3.1.tar.gz
# eval not working
# emacs --batch --eval '(load-file /tmp/auto-complete-1.3.1/etc/install.el)'


# FillColumnIndicator
cd ~/.emacs.d/lisp/
wget http://www.emacswiki.org/emacs/download/fill-column-indicator.el


# Emacs ColorTheme
cd /tmp
wget http://download.savannah.gnu.org/releases/color-theme/color-theme-6.6.0.tar.gz
tar zxvf color-theme-6.6.0.tar.gz
mv color-theme-6.6.0  $HOME/.emacs.d/
rm /tmp/color-theme-6.6.0.tar.gz


# copy .emacs
cp $HOME/Code/git-main/script/emacs/emacs  $HOME/.emacs
