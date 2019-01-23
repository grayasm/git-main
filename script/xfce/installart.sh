#!/bin/bash

# a) Run wget url with the initial path from opendesktop.org
#    e.g. wget https://www.opendesktop.org/p/1015014/startdownload?file_id=1460764027&file_name=48568-Clearlooks-XPSilver.tar.bz2&file_type=application/x-bzip2&file_size=1513
# b) It will download /tmp/48568-Clearlooks-XPSilver.tar.bz2 (html file)
# c) Open it with gedit and search for:
#    downloadlink is now: domain/api/files/download/id/ID/s/TOKEN/t/TIMESTAMP/u/USERID/FILE_NAME
# d) Compose the url by hand, replacing ID,TOKEN,TIMESTAMP,USERID with
#    variables from the html file:
#      var hash = 'b9961e...
#      var timetamp = '1543146704';
#      var userid = '56800';
#
# x) Nevermind, just copy to ftp://vasilian.net/Misc

if [ `id -u` != 0 ]; then
	echo "you must be root"
	exit
fi


cd /tmp
# exit when testing new commands
# exit



# Aurora R2Carbon
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460764485/s/a2ff8aaa925b78fa6183e87ded56a6e7/t/1532764485/u/108920-R2Carbon.tar.gz
wget ftp://vasilian.net/Misc/108920-R2Carbon.tar.gz
tar zxvf 108920-R2Carbon.tar.gz
rm -rfv /usr/share/themes/R2Carbon
mv R2Carbon /usr/share/themes/
chown -Rv root:root /usr/share/themes/R2Carbon
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/R2Carbon
rm 108920-R2Carbon.tar.gz


# Aurora Australis
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460761926/s/ccbd1b4c383a23a367540a2b9622a372/t/1532765382/u/107222-Aurora-Australis.tar.bz2
wget ftp://vasilian.net/Misc/107222-Aurora-Australis.tar.bz2
tar jxvf 107222-Aurora-Australis.tar.bz2
rm -rfv /usr/share/themes/Aurora-Australis
mv Aurora-Australis /usr/share/themes/
chown -Rv root:root /usr/share/themes/Aurora-Australis
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Aurora-Australis
rm 107222-Aurora-Australis.tar.bz2


# AuroraMintClear
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460765464/s/a83da4437a83cb815ae3cb444ced1413/t/1532765534/u/82999-AuroraMintClear.tar.gz
wget ftp://vasilian.net/Misc/82999-AuroraMintClear.tar.gz
tar zxvf 82999-AuroraMintClear.tar.gz
rm -rfv /usr/share/themes/AuroraMintClear
mv AuroraMintClear /usr/share/themes/
chown -Rv root:root /usr/share/themes/AuroraMintClear
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/AuroraMintClear
rm 82999-AuroraMintClear.tar.gz


# Aurora Graisboro
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460967055/s/633d4ca9050659acae5f0c2b9c758539/t/1532765612/u/114657-Aurora-Grainsboro-0.1.tar.bz2
wget ftp://vasilian.net/Misc/114657-Aurora-Grainsboro-0.1.tar.bz2
tar jxvf 114657-Aurora-Grainsboro-0.1.tar.bz2
rm -rfv "/usr/share/themes/Aurora Grainsboro"
mv "Aurora Grainsboro" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora Grainsboro"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora Grainsboro"
rm 114657-Aurora-Grainsboro-0.1.tar.bz2


# Aurora delta
# wget "https://dl.opendesktop.org/api/files/downloadfile/id/1460763519/s/81b9bfada530fc22dab056fed3f8d21b/t/1532765836/u/138760-Aurora delta.tar.gz"
wget "ftp://vasilian.net/Misc/138760-Aurora delta.tar.gz"
tar zxvf "138760-Aurora delta.tar.gz"
rm -rfv "/usr/share/themes/Aurora delta"
mv "Aurora delta" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora delta"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora delta"
chmod -Rv 755 "/usr/share/themes/Aurora delta"
rm "138760-Aurora delta.tar.gz"


# Blubuntu blue - does not use Aurora engine!
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460969897/s/8d6db1b56b8a301fb7bfa1ca4012af7d/t/1532766036/u/62176-Blubuntu-Aurora.tar.gz
wget ftp://vasilian.net/Misc/62176-Blubuntu-Aurora.tar.gz
tar zxvf 62176-Blubuntu-Aurora.tar.gz
rm -rfv /usr/share/themes/Blubuntu-Aurora
mv Blubuntu-Aurora /usr/share/themes/
chown -Rv root:root /usr/share/themes/Blubuntu-Aurora
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Blubuntu-Aurora
rm 62176-Blubuntu-Aurora.tar.gz


# Aurora BB - dark theme
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460968015/s/8a17c951ea58f49c152d2b1681668235/t/1532766102/u/81470-BB.tar.gz
wget ftp://vasilian.net/Misc/81470-BB.tar.gz
tar zxvf 81470-BB.tar.gz
rm -rfv /usr/share/themes/BB
mv BB /usr/share/themes/
chown -Rv root:root /usr/share/themes/BB
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/BB
rm 81470-BB.tar.gz


# Aurora-wave - dark theme!
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460764049/s/d5817cdcaebd2d54bf23feb81ec0acdb/t/1532766159/u/67305-Aurora-wave.tar.gz
wget ftp://vasilian.net/Misc/67305-Aurora-wave.tar.gz
tar zxvf 67305-Aurora-wave.tar.gz
rm -rfv /usr/share/themes/Aurora-wave
mv Aurora-wave /usr/share/themes/
chown -Rv root:root /usr/share/themes/Aurora-wave
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Aurora-wave
rm 67305-Aurora-wave.tar.gz


# Aurora Borealis
# wget "https://dl.opendesktop.org/api/files/downloadfile/id/1460969864/s/5dc9a65f629e8a7160ffad7246fc6b1d/t/1532766251/u/69273-Aurora Borealis.tar.bz2"
wget "ftp://vasilian.net/Misc/69273-Aurora Borealis.tar.bz2"
tar jxvf "69273-Aurora Borealis.tar.bz2"
rm -rfv "/usr/share/themes/Aurora Borealis"
mv "Aurora Borealis" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora Borealis"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora Borealis"
rm "69273-Aurora Borealis.tar.bz2"
rm aurora_borealis.png


# Arbeit Aurora - best with MAC style decorations.
# wget "https://dl.opendesktop.org/api/files/downloadfile/id/1460764559/s/97436bad69f03250c603f1247882fa32/t/1532766327/u/126718-Arbeit Aurora.tar.gz"
wget "ftp://vasilian.net/Misc/126718-Arbeit Aurora.tar.gz"
tar zxvf "126718-Arbeit Aurora.tar.gz"
rm -rfv "/usr/share/themes/Arbeit Aurora"
mv "Arbeit Aurora" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Arbeit Aurora"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Arbeit Aurora"
rm "126718-Arbeit Aurora.tar.gz"


# Aurora Mini - has nice small scrollbar
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460763365/s/62091f882c55e56f9fb436c6a54a03a6/t/1532766473/u/88489-AuroraMini.gtp
wget ftp://vasilian.net/Misc/88489-AuroraMini.gtp
tar zxvf 88489-AuroraMini.gtp
rm -rfv "/usr/share/themes/Aurora Mini"
mv "Aurora Mini" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora Mini"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora Mini"
rm 88489-AuroraMini.gtp


# Caramel_Aurora - has something special
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460969992/s/d2aee979fbb135e298e86aa8da8b3bc8/t/1532766583/u/76581-Caramel_Aurora.tar.bz2
wget ftp://vasilian.net/Misc/76581-Caramel_Aurora.tar.bz2
tar jxvf 76581-Caramel_Aurora.tar.bz2
rm -rfv /usr/share/themes/Caramel_Aurora
mv Caramel_Aurora /usr/share/themes/
chown -Rv root:root /usr/share/themes/Caramel_Aurora
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Caramel_Aurora
rm 76581-Caramel_Aurora.tar.bz2


# AuroraElementary
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460765468/s/0510a40d4d2417244aa84c9b475b7e1e/t/1532766633/u/85879-AuroraElementary-0.2.tar.gz
wget ftp://vasilian.net/Misc/85879-AuroraElementary-0.2.tar.gz
tar zxvf 85879-AuroraElementary-0.2.tar.gz
rm -rfv /usr/share/themes/AuroraElementary
mv AuroraElementary /usr/share/themes/
chown -Rv root:root /usr/share/themes/AuroraElementary
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/AuroraElementary
chmod -v 755 /usr/share/themes/AuroraElementary
chmod -v 755 /usr/share/themes/AuroraElementary/gtk-2.0/
chmod -Rv 644 /usr/share/themes/AuroraElementary/gtk-2.0/
rm 85879-AuroraElementary-0.2.tar.gz


# ClearLooks-Ice - real nice theme
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460764347/s/8adc02fe7119b3fefadad50ba1591fce/t/1531766914/u/23870-ClearLooks-Ice.tar.gz
wget ftp://vasilian.net/Misc/23870-ClearLooks-Ice.tar.gz
tar zxvf 23870-ClearLooks-Ice.tar.gz
rm -rfv /usr/share/themes/ClearLooks-Ice
mv ClearLooks-Ice /usr/share/themes/
chown -Rv root:root /usr/share/themes/ClearLooks-Ice
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/ClearLooks-Ice
rm 23870-ClearLooks-Ice.tar.gz


# Clearlooks XPSilver - real nice theme
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460764027/s/effee4048da8e6eb93e95ab602bfc1cd4f8ae863c2269b5669665db44128bb64697c89d21f0d9143ef2e1afdc06f4648d735321bd1c48d75e2528642a715cf25/t/1543154161/u/56800/48568-Clearlooks-XPSilver.tar.bz2
wget ftp://vasilian.net/Misc/48568-Clearlooks-XPSilver.tar.bz2
tar -jxvf 48568-Clearlooks-XPSilver.tar.bz2
rm -rfv /usr/share/themes/Clearlooks-XPSilver
mv Clearlooks-XPSilver /usr/share/themes/
chown -Rv root:root /usr/share/themes/Clearlooks-XPSilver
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-XPSilver
rm 48568-Clearlooks-XPSilver.tar.bz2


# Window Decorations
# Ambiance (Ubuntu), +hidpi (Extra Large Buttons)
# Plastik, +hidpi + RedmondXP-hidpi (Too Large)
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1469878208/s/2233dac976b360ffeba258b681c1a820/t/1532766678/u/hidpi-xfwm4-theme-pack-1.1.tar.gz
wget ftp://vasilian.net/Misc/hidpi-xfwm4-theme-pack-1.1.tar.gz
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
wget ftp://vasilian.net/Misc/176106-pcc_bb_square_var.tar.bz2
tar jxvf 176106-pcc_bb_square_var.tar.bz2
rm -rfv /usr/share/themes/pcc_bb_square_var
mv pcc_bb_square_var /usr/share/themes/
chown -Rv root:root /usr/share/themes/pcc_bb_square_var
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/pcc_bb_square_var
rm 176106-pcc_bb_square_var.tar.bz2


# Window decorations for Xfce4, GKT2, GTK3
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1464548430/s/ab7187fef0435ab384283c253b4f1b8c/t/1532766820/u/174774-Elementary-v3.zip
wget ftp://vasilian.net/Misc/174774-Elementary-v3.zip
unzip 174774-Elementary-v3.zip
rm -rfv /usr/share/themes/Elementary-v3
mv Elementary /usr/share/themes/Elementary-v3
chown -Rv root:root /usr/share/themes/Elementary-v3
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Elementary-v3
chmod -Rv 755 /usr/share/themes/Elementary-v3
rm 174774-Elementary-v3.zip


# blarge-color Window decorations for XFCE/XFWM4 (hdpmi - large)
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1461767559/s/984a6d4ed177f65f6a20975f65cffa5b/t/1532766867/u/175878-blarge-color.tar.gz
wget ftp://vasilian.net/Misc/175878-blarge-color.tar.gz
tar zxvf 175878-blarge-color.tar.gz
rm -rfv /usr/share/themes/blarge-color
mv  blarge-color  /usr/share/themes/
chown -Rv root:root /usr/share/themes/blarge-color
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/blarge-color
rm 175878-blarge-color.tar.gz



# dust-shiki-numix Window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1461053452/s/fbba3451376750b24d0c90751014eb09/t/1532766914/u/175816-dust-shiki-numix.tar.gz
wget ftp://vasilian.net/Misc/175816-dust-shiki-numix.tar.gz
tar zxvf 175816-dust-shiki-numix.tar.gz
rm -rfv /usr/share/themes/dust-shiki-numix
mv dust-shiki-numix  /usr/share/themes/
chown -Rv root:root /usr/share/themes/dust-shiki-numix
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/dust-shiki-numix
rm 175816-dust-shiki-numix.tar.gz


# Bluecurve window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460766007/s/2fd852a8f99daa262f319c64803d384b/t/1532766971/u/174775-Bluecurve-XWM4.tar.gz
wget ftp://vasilian.net/Misc/174775-Bluecurve-XWM4.tar.gz
tar zxvf 174775-Bluecurve-XWM4.tar.gz
mv Bluecurve  Bluecurve-hamish
rm -rfv /usr/share/themes/Bluecurve-hamish
mv Bluecurve-hamish /usr/share/themes/
chown -Rv root:root /usr/share/themes/Bluecurve-hamish
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Bluecurve-hamish
rm 174775-Bluecurve-XWM4.tar.gz


# Clearlooks-Phenix-Faded window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460766438/s/7952dd95c119434e91ccaca8b8951310/t/1532767017/u/174540-Clearlooks-Phenix-Faded.tar.gz
wget ftp://vasilian.net/Misc/174540-Clearlooks-Phenix-Faded.tar.gz
tar zxvf 174540-Clearlooks-Phenix-Faded.tar.gz
rm -rfv /usr/share/themes/Clearlooks-Phenix-Faded
mv Clearlooks-Phenix-Faded  /usr/share/themes/
chown -Rv root:root /usr/share/themes/Clearlooks-Phenix-Faded
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Phenix-Faded
rm 174540-Clearlooks-Phenix-Faded.tar.gz


# Greybird alternative (full buttom) window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460765969/s/3c2982262b763ac66cd0bdf31edbc663/t/1532767059/u/171328-Greybird-alt-fb-2015-09-09.zip
wget ftp://vasilian.net/Misc/171328-Greybird-alt-fb-2015-09-09.zip
unzip 171328-Greybird-alt-fb-2015-09-09.zip
rm -rfv Greybird-alt-fb/.git
rm -rfv /usr/share/themes/Greybird-alt-fb
mv Greybird-alt-fb  /usr/share/themes/
chown -Rv root:root /usr/share/themes/Greybird-alt-fb
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Greybird-alt-fb
rm 171328-Greybird-alt-fb-2015-09-09.zip


# Greybird alternative window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460766263/s/22cae08f8cd4e8e46ea0955b7dbb9cf2/t/1532767102/u/168845-Greybird-alt-2015-09-09.zip
wget ftp://vasilian.net/Misc/168845-Greybird-alt-2015-09-09.zip
unzip 168845-Greybird-alt-2015-09-09.zip
rm -rfv /usr/share/themes/Greybird-alt
mv Greybird-alt /usr/share/themes/
chown -Rv root:root /usr/share/themes/Greybird-alt
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Greybird-alt
rm 168845-Greybird-alt-2015-09-09.zip


# Sabia window decorations for XFCE/XFWM4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460765964/s/3a598f58709c95bf2be7f190a0cbc134/t/1532767141/u/170898-Sabia.zip
wget ftp://vasilian.net/Misc/170898-Sabia.zip
unzip 170898-Sabia.zip
rm -rfv /usr/share/Sabia\ *
mv Sabia\ *  /usr/share/themes/
chown -Rv root:root /usr/share/themes/Sabia\ *
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Sabia\ *
rm 170898-Sabia.zip


# Window decorations: Another Xfwm themE (AXE) is a minimalistic theme which
# picks up your gtk colors
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460767141/s/fc8caf91b49ecbb0bdfa783d0bca654b/t/1532767184/u/73291-axe.tar.gz
wget ftp://vasilian.net/Misc/73291-axe.tar.gz
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
wget ftp://vasilian.net/Misc/166997-4deb.zip
unzip 166997-4deb.zip
rm -rfv /usr/share/themes/4deb
mv 4deb  /usr/share/themes/
chown -Rv root:root /usr/share/themes/4deb
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/4deb
rm 166997-4deb.zip

# Window decorations: Clearlooks-Xfce-Colors themes for xfwm4
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460767136/s/2303ab25cdee0bb5f67be2e1ea4746bf/t/1532767271/u/90384-Clearlooks-Xfce-Colors.zip
wget ftp://vasilian.net/Misc/90384-Clearlooks-Xfce-Colors.zip
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
wget ftp://vasilian.net/Misc/Clearlooks-Xfce-Black.tar.gz
tar zxvf Clearlooks-Xfce-Black.tar.gz
rm -rfv /usr/share/themes/Clearlooks-Xfce-Black
mv Clearlooks-Xfce-Black /usr/share/themes/
chown -Rv root:root /usr/share/themes/Clearlooks-Xfce-Black
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-Xfce-Black
rm Clearlooks-Xfce-Black.tar.gz


# continue from top of page :
# https://www.xfce-look.org/browse/cat/138/page/22/ord/latest/
