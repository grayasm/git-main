#!/bin/bash

# Install xfwm themes.
if [ `id -u` != 0 ]; then
    echo "you must be root"
    exit
fi


# Window Decorations
# Ambiance (Ubuntu), +hidpi (Extra Large Buttons)
# Plastik, +hidpi + RedmondXP-hidpi (Too Large)
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1469878208/s/2233dac976b360ffeba258b681c1a820/t/1532766678/u/hidpi-xfwm4-theme-pack-1.1.tar.gz
wget ftp://vasilian.net/Gtk-Themes/hidpi-xfwm4-theme-pack-1.1.tar.gz
tar zxvf hidpi-xfwm4-theme-pack-1.1.tar.gz
rm -rfv /usr/share/themes/Ambiance
rm -rfv /usr/share/themes/Ambiance-hidpi
rm -rfv /usr/share/themes/Bluebird-hidpi
rm -rfv /usr/share/themes/Plastik
rm -rfv /usr/share/themes/Plastik-hidpi
rm -rfv /usr/share/themes/RedmondXP-hidpi
mv hidpi-xfwm4-theme-pack/* /usr/share/themes/
chown -Rv root:root /usr/share/themes/Ambiance
chown -Rv root:root /usr/share/themes/Ambiance-hidpi
chown -Rv root:root /usr/share/themes/Bluebird-hidpi
chown -Rv root:root /usr/share/themes/Plastik
chown -Rv root:root /usr/share/themes/Plastik-hidpi
chown -Rv root:root /usr/share/themes/RedmondXP-hidpi
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Ambiance
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Ambiance-hidpi
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Bluebird-hidpi
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Plastik
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Plastik-hidpi
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/RedmondXP-hidpi
rm hidpi-xfwm4-theme-pack-1.1.tar.gz
rm -rfv hidpi-xfwm4-theme-pack


# Window Decoration pcc_bb_square_var for Xfce4 - Retro, sharp edges
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1464562838/s/42e210d6a6605f850bebaf71945d5257/t/1532766735/u/176106-pcc_bb_square_var.tar.bz2
wget ftp://vasilian.net/Gtk-Themes/176106-pcc_bb_square_var.tar.bz2
tar jxvf 176106-pcc_bb_square_var.tar.bz2
rm -rfv /usr/share/themes/pcc_bb_square_var
mv pcc_bb_square_var /usr/share/themes/
chown -Rv root:root /usr/share/themes/pcc_bb_square_var
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/pcc_bb_square_var
rm 176106-pcc_bb_square_var.tar.bz2


# Window decorations for Xfce4, GKT2, GTK3
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1464548430/s/ab7187fef0435ab384283c253b4f1b8c/t/1532766820/u/174774-Elementary-v3.zip
wget ftp://vasilian.net/Gtk-Themes/174774-Elementary-v3.zip
unzip 174774-Elementary-v3.zip
rm -rfv /usr/share/themes/Elementary-v3
mv Elementary /usr/share/themes/Elementary-v3
chown -Rv root:root /usr/share/themes/Elementary-v3
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Elementary-v3
chmod -Rv 755 /usr/share/themes/Elementary-v3
rm 174774-Elementary-v3.zip


# blarge-color Window decorations for XFCE/XFWM4 (hdpmi - large)
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1461767559/s/984a6d4ed177f65f6a20975f65cffa5b/t/1532766867/u/175878-blarge-color.tar.gz
wget ftp://vasilian.net/Gtk-Themes/175878-blarge-color.tar.gz
tar zxvf 175878-blarge-color.tar.gz
rm -rfv /usr/share/themes/blarge-color
mv  blarge-color  /usr/share/themes/
chown -Rv root:root /usr/share/themes/blarge-color
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/blarge-color
rm 175878-blarge-color.tar.gz



# dust-shiki-numix Window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1461053452/s/fbba3451376750b24d0c90751014eb09/t/1532766914/u/175816-dust-shiki-numix.tar.gz
wget ftp://vasilian.net/Gtk-Themes/175816-dust-shiki-numix.tar.gz
tar zxvf 175816-dust-shiki-numix.tar.gz
rm -rfv /usr/share/themes/dust-shiki-numix
mv dust-shiki-numix  /usr/share/themes/
chown -Rv root:root /usr/share/themes/dust-shiki-numix
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/dust-shiki-numix
rm 175816-dust-shiki-numix.tar.gz


# Bluecurve window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460766007/s/2fd852a8f99daa262f319c64803d384b/t/1532766971/u/174775-Bluecurve-XWM4.tar.gz
wget ftp://vasilian.net/Gtk-Themes/174775-Bluecurve-XWM4.tar.gz
tar zxvf 174775-Bluecurve-XWM4.tar.gz
mv Bluecurve  Bluecurve-hamish
rm -rfv /usr/share/themes/Bluecurve-hamish
mv Bluecurve-hamish /usr/share/themes/
chown -Rv root:root /usr/share/themes/Bluecurve-hamish
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Bluecurve-hamish
rm 174775-Bluecurve-XWM4.tar.gz


# Clearlooks-Phenix-Faded window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460766438/s/7952dd95c119434e91ccaca8b8951310/t/1532767017/u/174540-Clearlooks-Phenix-Faded.tar.gz
wget ftp://vasilian.net/Gtk-Themes/174540-Clearlooks-Phenix-Faded.tar.gz
tar zxvf 174540-Clearlooks-Phenix-Faded.tar.gz
rm -rfv /usr/share/themes/Clearlooks-Phenix-Faded
mv Clearlooks-Phenix-Faded  /usr/share/themes/
chown -Rv root:root /usr/share/themes/Clearlooks-Phenix-Faded
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Phenix-Faded
rm 174540-Clearlooks-Phenix-Faded.tar.gz


# Greybird alternative (full buttom) window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460765969/s/3c2982262b763ac66cd0bdf31edbc663/t/1532767059/u/171328-Greybird-alt-fb-2015-09-09.zip
wget ftp://vasilian.net/Gtk-Themes/171328-Greybird-alt-fb-2015-09-09.zip
unzip 171328-Greybird-alt-fb-2015-09-09.zip
rm -rfv Greybird-alt-fb/.git
rm -rfv /usr/share/themes/Greybird-alt-fb
mv Greybird-alt-fb  /usr/share/themes/
chown -Rv root:root /usr/share/themes/Greybird-alt-fb
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Greybird-alt-fb
rm 171328-Greybird-alt-fb-2015-09-09.zip


# Greybird alternative window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460766263/s/22cae08f8cd4e8e46ea0955b7dbb9cf2/t/1532767102/u/168845-Greybird-alt-2015-09-09.zip
wget ftp://vasilian.net/Gtk-Themes/168845-Greybird-alt-2015-09-09.zip
unzip 168845-Greybird-alt-2015-09-09.zip
rm -rfv /usr/share/themes/Greybird-alt
mv Greybird-alt /usr/share/themes/
chown -Rv root:root /usr/share/themes/Greybird-alt
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Greybird-alt
rm 168845-Greybird-alt-2015-09-09.zip


# Sabia window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460765964/s/3a598f58709c95bf2be7f190a0cbc134/t/1532767141/u/170898-Sabia.zip
wget ftp://vasilian.net/Gtk-Themes/170898-Sabia.zip
unzip 170898-Sabia.zip
rm -rfv /usr/share/Sabia\ *
mv Sabia\ *  /usr/share/themes/
chown -Rv root:root /usr/share/themes/Sabia\ *
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Sabia\ *
rm 170898-Sabia.zip


# Window decorations: Another Xfwm themE (AXE) is a minimalistic theme which
# picks up your gtk colors
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460767141/s/fc8caf91b49ecbb0bdfa783d0bca654b/t/1532767184/u/73291-axe.tar.gz
wget ftp://vasilian.net/Gtk-Themes/73291-axe.tar.gz
tar zxvf 73291-axe.tar.gz
rm -rfv /usr/share/themes/axe
rm -rfv "/usr/share/themes/axe rounded"
mv axe /usr/share/themes/
mv "axe rounded"  /usr/share/themes/
chown -Rv root:root /usr/share/themes/axe
chown -Rv root:root "/usr/share/themes/axe rounded"
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/axe
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/axe rounded"
rm 73291-axe.tar.gz


# Window decorations: 4deb theme for xfwm4 with Debian color scheme
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460766415/s/8b55178542e6fc703693ac693f0f61b6/t/1532767230/u/166997-4deb.zip
wget ftp://vasilian.net/Gtk-Themes/166997-4deb.zip
unzip 166997-4deb.zip
rm -rfv /usr/share/themes/4deb
mv 4deb  /usr/share/themes/
chown -Rv root:root /usr/share/themes/4deb
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/4deb
rm 166997-4deb.zip

# Window decorations: Clearlooks-Xfce-Colors themes for xfwm4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460767136/s/2303ab25cdee0bb5f67be2e1ea4746bf/t/1532767271/u/90384-Clearlooks-Xfce-Colors.zip
wget ftp://vasilian.net/Gtk-Themes/90384-Clearlooks-Xfce-Colors.zip
unzip 90384-Clearlooks-Xfce-Colors.zip
rm -rfv /usr/share/themes/Clearlooks-Xfce-Wise
rm -rfv /usr/share/themes/Clearlooks-Xfce-Wine
rm -rfv /usr/share/themes/Clearlooks-Xfce-Human
rm -rfv /usr/share/themes/Clearlooks-Xfce-Classic
mv Clearlooks-Xfce-Wise /usr/share/themes/
mv Clearlooks-Xfce-Wine /usr/share/themes/
mv Clearlooks-Xfce-Human /usr/share/themes/
mv Clearlooks-Xfce-Classic /usr/share/themes/
chown -Rv root:root /usr/share/themes/Clearlooks-Xfce-Wise
chown -Rv root:root /usr/share/themes/Clearlooks-Xfce-Wine
chown -Rv root:root /usr/share/themes/Clearlooks-Xfce-Human
chown -Rv root:root /usr/share/themes/Clearlooks-Xfce-Classic
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Xfce-Wise
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Xfce-Wine
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Xfce-Human
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Xfce-Classic
rm 90384-Clearlooks-Xfce-Colors.zip

# Window decorations: Clearlooks-Xfce-Black themes for xfwm4
# https://www.opendesktop.org/p/1277683/
wget ftp://vasilian.net/Gtk-Themes/Clearlooks-Xfce-Black.tar.gz
tar zxvf Clearlooks-Xfce-Black.tar.gz
rm -rfv /usr/share/themes/Clearlooks-Xfce-Black
mv Clearlooks-Xfce-Black /usr/share/themes/
chown -Rv root:root /usr/share/themes/Clearlooks-Xfce-Black
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Xfce-Black
rm Clearlooks-Xfce-Black.tar.gz


# Window decorations: Clearlooks-Xfce-Black-Big themes for xfwm4
# modified Clearlooks-Xfce-Black titlebar height from 24 to 31 pixels (proportional)
wget ftp://vasilian.net/Gtk-Themes/Clearlooks-Xfce-Black-Big.tar.gz
tar zxvf Clearlooks-Xfce-Black-Big.tar.gz
rm -rfv /usr/share/themes/Clearlooks-Xfce-Black-Big
mv Clearlooks-Xfce-Black-Big /usr/share/themes/
chown -Rv root:root /usr/share/themes/Clearlooks-Xfce-Black-Big
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Xfce-Black-Big
rm Clearlooks-Xfce-Black-Big.tar.gz

# Continue from top of page :
# https://www.xfce-look.org/browse/cat/138/page/22/ord/latest/
