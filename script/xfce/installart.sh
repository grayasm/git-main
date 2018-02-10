#!/bin/bash

if [ `id -u` != 0 ]; then
	echo "you must be root"
	exit
fi

# test new commands
cd /tmp

exit


# Aurora R2Carbon
wget https://dl.opendesktop.org/api/files/download/id/1460764485/108920-R2Carbon.tar.gz
tar zxvf 108920-R2Carbon.tar.gz
rm -rfv /usr/share/themes/R2Carbon
mv R2Carbon /usr/share/themes/
chown -Rv root:root /usr/share/themes/R2Carbon
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/R2Carbon
rm 108920-R2Carbon.tar.gz


# Aurora Australis
wget https://dl.opendesktop.org/api/files/download/id/1460761926/107222-Aurora-Australis.tar.bz2
tar jxvf 107222-Aurora-Australis.tar.bz2
rm -rfv /usr/share/themes/Aurora-Australis
mv Aurora-Australis /usr/share/themes/
chown -Rv root:root /usr/share/themes/Aurora-Australis
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Aurora-Australis
rm 107222-Aurora-Australis.tar.bz2


# AuroraMintClear
wget https://dl.opendesktop.org/api/files/download/id/1460765464/82999-AuroraMintClear.tar.gz
tar zxvf 82999-AuroraMintClear.tar.gz
rm -rfv /usr/share/themes/AuroraMintClear
mv AuroraMintClear /usr/share/themes/
chown -Rv root:root /usr/share/themes/AuroraMintClear
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/AuroraMintClear
rm 82999-AuroraMintClear.tar.gz


# Aurora Graisboro
wget https://dl.opendesktop.org/api/files/download/id/1460967055/114657-Aurora-Grainsboro-0.1.tar.bz2
tar jxvf 114657-Aurora-Grainsboro-0.1.tar.bz2
rm -rfv "/usr/share/themes/Aurora Grainsboro"
mv "Aurora Grainsboro" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora Grainsboro"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora Grainsboro"
rm 114657-Aurora-Grainsboro-0.1.tar.bz2


# Aurora delta
wget  https://dl.opendesktop.org/api/files/download/id/1460763519/138760-Aurora%20delta.tar.gz
tar zxvf "138760-Aurora delta.tar.gz"
rm -rfv "/usr/share/themes/Aurora delta"
mv "Aurora delta" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora delta"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora delta"
chmod -Rv 755 "/usr/share/themes/Aurora delta"
rm "138760-Aurora delta.tar.gz"


# Blubuntu blue - does not use Aurora engine!
wget https://dl.opendesktop.org/api/files/download/id/1460969897/62176-Blubuntu-Aurora.tar.gz
tar zxvf 62176-Blubuntu-Aurora.tar.gz
rm -rfv /usr/share/themes/Blubuntu-Aurora
mv Blubuntu-Aurora /usr/share/themes/
chown -Rv root:root /usr/share/themes/Blubuntu-Aurora
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Blubuntu-Aurora
rm 62176-Blubuntu-Aurora.tar.gz


# Aurora BB - dark theme
wget https://dl.opendesktop.org/api/files/download/id/1460968015/81470-BB.tar.gz
tar zxvf 81470-BB.tar.gz
rm -rfv /usr/share/themes/BB
mv BB /usr/share/themes/
chown -Rv root:root /usr/share/themes/BB
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/BB
rm 81470-BB.tar.gz


# Aurora-wave - dark theme!
wget https://dl.opendesktop.org/api/files/download/id/1460764049/67305-Aurora-wave.tar.gz
tar zxvf 67305-Aurora-wave.tar.gz
rm -rfv /usr/share/themes/Aurora-wave
mv Aurora-wave /usr/share/themes/
chown -Rv root:root /usr/share/themes/Aurora-wave
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Aurora-wave
rm 67305-Aurora-wave.tar.gz


# Aurora Borealis
wget https://dl.opendesktop.org/api/files/download/id/1460969864/69273-Aurora%20Borealis.tar.bz2
tar jxvf "69273-Aurora Borealis.tar.bz2"
rm -rfv "/usr/share/themes/Aurora Borealis"
mv "Aurora Borealis" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora Borealis"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora Borealis"
rm "69273-Aurora Borealis.tar.bz2"
rm aurora_borealis.png


# Arbeit Aurora - best with MAC style decorations.
wget https://dl.opendesktop.org/api/files/download/id/1460764559/126718-Arbeit%20Aurora.tar.gz
tar zxvf "126718-Arbeit Aurora.tar.gz"
rm -rfv "/usr/share/themes/Arbeit Aurora"
mv "Arbeit Aurora" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Arbeit Aurora"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Arbeit Aurora"
rm "126718-Arbeit Aurora.tar.gz"


# Aurora Mini - has nice small scrollbar
wget https://dl.opendesktop.org/api/files/download/id/1460763365/88489-AuroraMini.gtp
tar zxvf 88489-AuroraMini.gtp
rm -rfv "/usr/share/themes/Aurora Mini"
mv "Aurora Mini" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora Mini"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora Mini"
rm 88489-AuroraMini.gtp


# Caramel_Aurora - has something special
wget https://dl.opendesktop.org/api/files/download/id/1460969992/76581-Caramel_Aurora.tar.bz2
tar jxvf 76581-Caramel_Aurora.tar.bz2
rm -rfv /usr/share/themes/Caramel_Aurora
mv Caramel_Aurora /usr/share/themes/
chown -Rv root:root /usr/share/themes/Caramel_Aurora
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Caramel_Aurora
rm 76581-Caramel_Aurora.tar.bz2


# AuroraElementary
wget https://dl.opendesktop.org/api/files/download/id/1460765468/85879-AuroraElementary-0.2.tar.gz
tar zxvf 85879-AuroraElementary-0.2.tar.gz
rm -rfv /usr/share/themes/AuroraElementary
mv AuroraElementary /usr/share/themes/
chown -Rv root:root /usr/share/themes/AuroraElementary
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/AuroraElementary
chmod -v 755 /usr/share/themes/AuroraElementary
chmod -v 755 /usr/share/themes/AuroraElementary/gtk-2.0/
chmod -Rv 644 /usr/share/themes/AuroraElementary/gtk-2.0/
rm 85879-AuroraElementary-0.2.tar.gz


# Window Decorations
# Ambiance (Ubuntu), +hidpi (Extra Large Buttons)
# Plastik, +hidpi + RedmondXP-hidpi (Too Large)
wget https://dl.opendesktop.org/api/files/download/id/1469878208/hidpi-xfwm4-theme-pack-1.1.tar.gz
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
wget https://dl.opendesktop.org/api/files/download/id/1464562838/176106-pcc_bb_square_var.tar.bz2
tar jxvf 176106-pcc_bb_square_var.tar.bz2
rm -rfv /usr/share/themes/pcc_bb_square_var
mv pcc_bb_square_var /usr/share/themes/
chown -Rv root:root /usr/share/themes/pcc_bb_square_var
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/pcc_bb_square_var
rm 176106-pcc_bb_square_var.tar.bz2


# Window decorations for Xfce4, GKT2, GTK3
wget https://dl.opendesktop.org/api/files/download/id/1464548430/174774-Elementary-v3.zip
unzip 174774-Elementary-v3.zip
rm -rfv /usr/share/themes/Elementary-v3
mv Elementary /usr/share/themes/Elementary-v3
chown -Rv root:root /usr/share/themes/Elementary-v3
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Elementary-v3
chmod -Rv 755 /usr/share/themes/Elementary-v3
rm 174774-Elementary-v3.zip


# blarge-color Window decorations for XFCE/XFWM4 (hdpmi - large)
wget https://dl.opendesktop.org/api/files/download/id/1461767559/175878-blarge-color.tar.gz
tar zxvf 175878-blarge-color.tar.gz
rm -rfv /usr/share/themes/blarge-color
mv  blarge-color  /usr/share/themes/
chown -Rv root:root /usr/share/themes/blarge-color
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/blarge-color
rm 175878-blarge-color.tar.gz



# dust-shiki-numix Window decorations for XFCE/XFWM4
wget https://dl.opendesktop.org/api/files/download/id/1461053452/175816-dust-shiki-numix.tar.gz
tar zxvf 175816-dust-shiki-numix.tar.gz
rm -rfv /usr/share/themes/dust-shiki-numix
mv dust-shiki-numix  /usr/share/themes/
chown -Rv root:root /usr/share/themes/dust-shiki-numix
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/dust-shiki-numix
rm 175816-dust-shiki-numix.tar.gz


# Bluecurve window decorations for XFCE/XFWM4
https://dl.opendesktop.org/api/files/download/id/1460766007/174775-Bluecurve-XWM4.tar.gz
tar zxvf 174775-Bluecurve-XWM4.tar.gz
mv Bluecurve  Bluecurve-hamish
rm -rfv /usr/share/themes/Bluecurve-hamish
mv Bluecurve-hamish /usr/share/themes/
chown -Rv root:root /usr/share/themes/Bluecurve-hamish
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Bluecurve-hamish
rm 174775-Bluecurve-XWM4.tar.gz


# Clearlooks-Phenix-Faded window decorations for XFCE/XFWM4
wget https://dl.opendesktop.org/api/files/download/id/1460766438/174540-Clearlooks-Phenix-Faded.tar.gz
tar zxvf 174540-Clearlooks-Phenix-Faded.tar.gz
rm -rfv /usr/share/themes/Clearlooks-Phenix-Faded
mv Clearlooks-Phenix-Faded  /usr/share/themes/
chown -Rv root:root /usr/share/themes/Clearlooks-Phenix-Faded
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Phenix-Faded
rm 174540-Clearlooks-Phenix-Faded.tar.gz


# Greybird alternative (full buttom) window decorations for XFCE/XFWM4
wget https://dl.opendesktop.org/api/files/download/id/1460765969/171328-Greybird-alt-fb-2015-09-09.zip
unzip 171328-Greybird-alt-fb-2015-09-09.zip
rm -rfv Greybird-alt-fb/.git
rm -rfv /usr/share/themes/Greybird-alt-fb
mv Greybird-alt-fb  /usr/share/themes/
chown -Rv root:root /usr/share/themes/Greybird-alt-fb
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Greybird-alt-fb
rm 171328-Greybird-alt-fb-2015-09-09.zip


# Greybird alternative window decorations for XFCE/XFWM4
wget https://dl.opendesktop.org/api/files/download/id/1460766263/168845-Greybird-alt-2015-09-09.zip
unzip 168845-Greybird-alt-2015-09-09.zip
rm -rfv /usr/share/themes/Greybird-alt
mv Greybird-alt /usr/share/themes/
chown -Rv root:root /usr/share/themes/Greybird-alt
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Greybird-alt
rm 168845-Greybird-alt-2015-09-09.zip


# Sabia window decorations for XFCE/XFWM4
wget https://dl.opendesktop.org/api/files/download/id/1460765964/170898-Sabia.zip
unzip 170898-Sabia.zip
rm -rfv /usr/share/Sabia\ *
mv Sabia\ *  /usr/share/themes/
chown -Rv root:root /usr/share/themes/Sabia\ *
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Sabia\ *
rm 170898-Sabia.zip


# Window decorations: Another Xfwm themE (AXE) is a minimalistic theme which
# picks up your gtk colors
wget https://dl.opendesktop.org/api/files/download/id/1460767141/73291-axe.tar.gz
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
wget https://dl.opendesktop.org/api/files/download/id/1460766415/166997-4deb.zip
unzip 166997-4deb.zip
rm -rfv /usr/share/themes/4deb
mv 4deb  /usr/share/themes/
chown -Rv root:root /usr/share/themes/4deb
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/4deb
rm 166997-4deb.zip

# Window decorations: Clearlooks-Xfce-Colors themes for xfwm4
wget https://dl.opendesktop.org/api/files/downloadfile/id/1460767136/s/e7c0466e23f4da98a13efaf43d7f4b5d/t/1518282916/u/90384-Clearlooks-Xfce-Colors.zip
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

# continue from top of page :
# https://www.xfce-look.org/browse/cat/138/page/22/ord/latest/
