#!/bin/bash

# cp $PWD/setemacs.sh $HOME/Code/git-main/script/emacs/setemacs.sh
# svn status $HOME/Code/git-main
# svn diff   $HOME/Code/git-main
# svn commit $HOME/Code/git-main


# lusty explorer
cd $HOME/.emacs.d
wget http://www.emacswiki.org/emacs/download/lusty-explorer.el

# auto-complete, fuzzy matching
cd /tmp
wget http://cx4a.org/pub/auto-complete/auto-complete-1.3.1.tar.bz2
tar jxvf auto-complete-1.3.1.tar.bz2
emacs --batch --eval '(load-file /tmp/auto-complete-1.3.1/etc/install.el)'
rm /tmp/auto-complete-1.3.1.tar.bz2
rmdir /tmp/auto-complete-1.3.1


# FillColumnIndicator
cd ~/.emacs.d/
wget http://www.emacswiki.org/emacs/download/fill-column-indicator.el


# Emacs ColorTheme
cd /tmp
wget http://download.savannah.gnu.org/releases/color-theme/color-theme-6.6.0.tar.gz
tar zxvf color-theme-6.6.0.tar.gz
mv color-theme-6.6.0  $HOME/.emacs.d/
rm /tmp/color-theme-6.6.0.tar.gz


# copy .emacs
cp $HOME/Code/git-main/script/emacs/emacs  $HOME/.emacs
