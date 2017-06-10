#!/bin/bash


cd /tmp



exit
# Aurora R2Carbon
wget https://dl.opendesktop.org/api/files/download/id/1460764485/108920-R2Carbon.tar.gz
tar zxvf 108920-R2Carbon.tar.gz
mv R2Carbon ~/.themes/
rm 108920-R2Carbon.tar.gz


# Aurora Australis
wget https://dl.opendesktop.org/api/files/download/id/1460761926/107222-Aurora-Australis.tar.bz2
tar jxvf 107222-Aurora-Australis.tar.bz2
mv Aurora-Australis ~/.themes/
rm 107222-Aurora-Australis.tar.bz2


# Aurora based AuroraMintClear
wget https://dl.opendesktop.org/api/files/download/id/1460765464/82999-AuroraMintClear.tar.gz
tar zxvf 82999-AuroraMintClear.tar.gz
mv AuroraMintClear ~/.themes/
rm 82999-AuroraMintClear.tar.gz


# Aurora Graisboro
wget https://dl.opendesktop.org/api/files/download/id/1460967055/114657-Aurora-Grainsboro-0.1.tar.bz2
tar jxvf 114657-Aurora-Grainsboro-0.1.tar.bz2
mv "Aurora Grainsboro" ~/.themes/
rm 114657-Aurora-Grainsboro-0.1.tar.bz2


# need /usr/bin/7z  from p7zip-plugins
7z i 2>&1 >/dev/null
_7Z_IS_AVAILABLE=$?
if [ $_7Z_IS_AVAILABLE -ne 0 ]; then
	echo "install 7zip"
	yum install p7zip p7zip-plugins
fi

# Aurora_Garbonner - broken window decorations
wget https://dl.opendesktop.org/api/files/download/id/1460765737/94749-Aurora_Garbonner.lzh
7z x 94749-Aurora_Garbonner.lzh
rm 94749-Aurora_Garbonner.lzh
rm -rfv Aurora_Garbonner


# Aurora delta
wget  https://dl.opendesktop.org/api/files/download/id/1460763519/138760-Aurora%20delta.tar.gz
tar zxvf "138760-Aurora delta.tar.gz"
mv "Aurora delta" ~/.themes/
rm "138760-Aurora delta.tar.gz"


# Blubuntu blue - does not use Aurora engine!
wget https://dl.opendesktop.org/api/files/download/id/1460969897/62176-Blubuntu-Aurora.tar.gz
tar zxvf 62176-Blubuntu-Aurora.tar.gz
mv Blubuntu-Aurora ~/.themes/
rm 62176-Blubuntu-Aurora.tar.gz


# Aurora BB - dark theme
wget https://dl.opendesktop.org/api/files/download/id/1460968015/81470-BB.tar.gz
tar zxvf 81470-BB.tar.gz
mv BB ~/.themes/
rm 81470-BB.tar.gz

# Aurora-wave - dark theme!
wget https://dl.opendesktop.org/api/files/download/id/1460764049/67305-Aurora-wave.tar.gz
tar zxvf 67305-Aurora-wave.tar.gz
mv Aurora-wave ~/.themes/
rm 67305-Aurora-wave.tar.gz


# Aurora Borealis
wget https://dl.opendesktop.org/api/files/download/id/1460969864/69273-Aurora%20Borealis.tar.bz2
tar jxvf "69273-Aurora Borealis.tar.bz2"
mv "Aurora Borealis" ~/.themes/
rm "69273-Aurora Borealis.tar.bz2"
rm aurora_borealis.png


# Arbeit Aurora - best with MAC style decorations.
wget https://dl.opendesktop.org/api/files/download/id/1460764559/126718-Arbeit%20Aurora.tar.gz
tar zxvf "126718-Arbeit Aurora.tar.gz"
mv "Arbeit Aurora" ~/.themes/
rm "126718-Arbeit Aurora.tar.gz"


# Aurora Mini - has nice small scrollbar
wget https://dl.opendesktop.org/api/files/download/id/1460763365/88489-AuroraMini.gtp
tar zxvf 88489-AuroraMini.gtp
mv "Aurora Mini" ~/.themes/
rm 88489-AuroraMini.gtp


# Caramel_Aurora - has something special
wget https://dl.opendesktop.org/api/files/download/id/1460969992/76581-Caramel_Aurora.tar.bz2
tar jxvf 76581-Caramel_Aurora.tar.bz2
mv Caramel_Aurora ~/.themes/
rm 76581-Caramel_Aurora.tar.bz2


# AuroraElementary
wget https://dl.opendesktop.org/api/files/download/id/1460765468/85879-AuroraElementary-0.2.tar.gz
tar zxvf 85879-AuroraElementary-0.2.tar.gz
mv AuroraElementary ~/.themes/
rm 85879-AuroraElementary-0.2.tar.gz


# Window Decorations
# Ambiance (Ubuntu), +hidpi (Extra Large Buttons)
# Plastik, +hidpi + RedmondXP-hidpi (Too Large)
wget https://dl.opendesktop.org/api/files/download/id/1469878208/hidpi-xfwm4-theme-pack-1.1.tar.gz
tar zxvf hidpi-xfwm4-theme-pack-1.1.tar.gz
mv hidpi-xfwm4-theme-pack/* ~/.themes/
rm hidpi-xfwm4-theme-pack-1.1.tar.gz


# Window Decoration pcc_bb_square_var for Xfce4 - Retro, sharp edges
wget https://dl.opendesktop.org/api/files/download/id/1464562838/176106-pcc_bb_square_var.tar.bz2
tar jxvf 176106-pcc_bb_square_var.tar.bz2
mv pcc_bb_square_var ~/.themes/
rm 176106-pcc_bb_square_var.tar.bz2


# Window decorations for Xfce4, GKT2, GTK3
wget https://dl.opendesktop.org/api/files/download/id/1464548430/174774-Elementary-v3.zip
unzip 174774-Elementary-v3.zip
mv Elementary ~/.themes/Elementary-v3
rm 174774-Elementary-v3.zip

# continue with new window decorations from here
# https://www.xfce-look.org/browse/cat/138/page/6/ord/latest/
