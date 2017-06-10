#!/bin/bash

if [ `id -u` != 0 ]; then
	echo "you must be root"
	exit
fi

# test new commands
# cd /tmp
# exit

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

# continue with new window decorations from here
# https://www.xfce-look.org/browse/cat/138/page/6/ord/latest/
