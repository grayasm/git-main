#!/bin/bash

# cp $PWD/getmate.sh $HOME/Code/svn-trunk/script/mate/getmate.sh
# svn status $HOME/Code/svn-trunk
# svn diff   $HOME/Code/svn-trunk
# svn commit $HOME/Code/svn-trunk


MATE="mate-applet-lockkeys libmatekbd mate-applets mate-backgrounds \
	mate-calc mate-common mate-control-center mate-desktop mate-icon-theme \
	mate-media mate-menus mate-notification-daemon mate-panel mate-polkit \
	mate-power-manager mate-screensaver mate-session-manager \
	mate-settings-daemon mate-system-monitor mate-terminal mate-themes \
	mate-utils caja caja-actions compiz-mate engrampa eom libmateweather \
	libmateweather-data marco mate-control-center-filesystem mate-desktop-libs \
	mate-dialogs mate-dictionary mate-disk-usage-analyzer \
	mate-icon-theme-faenza mate-menus-libs mate-panel-libs mate-search-tool \
	mate-system-log mate-themes-extras mate-utils-common mozo xmonad-mate \
	agrep atril atril-caja atril-libs caja-beesu caja-extensions \
	caja-image-converter caja-open-terminal caja-schemas caja-sendto \
	caja-terminal mate-menus-preferences-category-menu mate-screenshot mintmenu"

if [ -f /etc/centos-release ]
then
    echo "Installing Mate for CentOS"
    yum install $MATE
fi
