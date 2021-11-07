#!/bin/bash

if [ `id -u` != 0 ]; then
    echo "you must be root"
    exit
fi


cd /tmp
# exit when testing new commands
# exit



# Aurora R2Carbon
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460764485/s/a2ff8aaa925b78fa6183e87ded56a6e7/t/1532764485/u/108920-R2Carbon.tar.gz
wget ftp://vasilian.net/Gtk-Themes/108920-R2Carbon.tar.gz
tar zxvf 108920-R2Carbon.tar.gz
rm -rfv /usr/share/themes/R2Carbon
mv R2Carbon /usr/share/themes/
chown -Rv root:root /usr/share/themes/R2Carbon
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/R2Carbon
rm 108920-R2Carbon.tar.gz


# Aurora Australis
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460761926/s/ccbd1b4c383a23a367540a2b9622a372/t/1532765382/u/107222-Aurora-Australis.tar.bz2
wget ftp://vasilian.net/Gtk-Themes/107222-Aurora-Australis.tar.bz2
tar jxvf 107222-Aurora-Australis.tar.bz2
rm -rfv /usr/share/themes/Aurora-Australis
mv Aurora-Australis /usr/share/themes/
chown -Rv root:root /usr/share/themes/Aurora-Australis
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Aurora-Australis
rm 107222-Aurora-Australis.tar.bz2


# AuroraMintClear
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460765464/s/a83da4437a83cb815ae3cb444ced1413/t/1532765534/u/82999-AuroraMintClear.tar.gz
wget ftp://vasilian.net/Gtk-Themes/82999-AuroraMintClear.tar.gz
tar zxvf 82999-AuroraMintClear.tar.gz
rm -rfv /usr/share/themes/AuroraMintClear
mv AuroraMintClear /usr/share/themes/
chown -Rv root:root /usr/share/themes/AuroraMintClear
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/AuroraMintClear
rm 82999-AuroraMintClear.tar.gz


# Aurora Graisboro
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460967055/s/633d4ca9050659acae5f0c2b9c758539/t/1532765612/u/114657-Aurora-Grainsboro-0.1.tar.bz2
wget ftp://vasilian.net/Gtk-Themes/114657-Aurora-Grainsboro-0.1.tar.bz2
tar jxvf 114657-Aurora-Grainsboro-0.1.tar.bz2
rm -rfv "/usr/share/themes/Aurora Grainsboro"
mv "Aurora Grainsboro" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora Grainsboro"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora Grainsboro"
rm 114657-Aurora-Grainsboro-0.1.tar.bz2


# Aurora delta
# wget "https://dl.opendesktop.org/api/files/downloadfile/id/1460763519/s/81b9bfada530fc22dab056fed3f8d21b/t/1532765836/u/138760-Aurora delta.tar.gz"
wget "ftp://vasilian.net/Gtk-Themes/138760-Aurora delta.tar.gz"
tar zxvf "138760-Aurora delta.tar.gz"
rm -rfv "/usr/share/themes/Aurora delta"
mv "Aurora delta" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora delta"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora delta"
chmod -Rv 755 "/usr/share/themes/Aurora delta"
rm "138760-Aurora delta.tar.gz"


# Blubuntu blue - does not use Aurora engine!
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460969897/s/8d6db1b56b8a301fb7bfa1ca4012af7d/t/1532766036/u/62176-Blubuntu-Aurora.tar.gz
wget ftp://vasilian.net/Gtk-Themes/62176-Blubuntu-Aurora.tar.gz
tar zxvf 62176-Blubuntu-Aurora.tar.gz
rm -rfv /usr/share/themes/Blubuntu-Aurora
mv Blubuntu-Aurora /usr/share/themes/
chown -Rv root:root /usr/share/themes/Blubuntu-Aurora
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Blubuntu-Aurora
rm 62176-Blubuntu-Aurora.tar.gz


# Aurora BB - dark theme
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460968015/s/8a17c951ea58f49c152d2b1681668235/t/1532766102/u/81470-BB.tar.gz
wget ftp://vasilian.net/Gtk-Themes/81470-BB.tar.gz
tar zxvf 81470-BB.tar.gz
rm -rfv /usr/share/themes/BB
mv BB /usr/share/themes/
chown -Rv root:root /usr/share/themes/BB
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/BB
rm 81470-BB.tar.gz


# Aurora-wave - dark theme!
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460764049/s/d5817cdcaebd2d54bf23feb81ec0acdb/t/1532766159/u/67305-Aurora-wave.tar.gz
wget ftp://vasilian.net/Gtk-Themes/67305-Aurora-wave.tar.gz
tar zxvf 67305-Aurora-wave.tar.gz
rm -rfv /usr/share/themes/Aurora-wave
mv Aurora-wave /usr/share/themes/
chown -Rv root:root /usr/share/themes/Aurora-wave
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Aurora-wave
rm 67305-Aurora-wave.tar.gz


# Aurora Borealis
# wget "https://dl.opendesktop.org/api/files/downloadfile/id/1460969864/s/5dc9a65f629e8a7160ffad7246fc6b1d/t/1532766251/u/69273-Aurora Borealis.tar.bz2"
wget "ftp://vasilian.net/Gtk-Themes/69273-Aurora Borealis.tar.bz2"
tar jxvf "69273-Aurora Borealis.tar.bz2"
rm -rfv "/usr/share/themes/Aurora Borealis"
mv "Aurora Borealis" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora Borealis"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora Borealis"
rm "69273-Aurora Borealis.tar.bz2"
rm aurora_borealis.png


# Arbeit Aurora - best with MAC style decorations.
# wget "https://dl.opendesktop.org/api/files/downloadfile/id/1460764559/s/97436bad69f03250c603f1247882fa32/t/1532766327/u/126718-Arbeit Aurora.tar.gz"
wget "ftp://vasilian.net/Gtk-Themes/126718-Arbeit Aurora.tar.gz"
tar zxvf "126718-Arbeit Aurora.tar.gz"
rm -rfv "/usr/share/themes/Arbeit Aurora"
mv "Arbeit Aurora" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Arbeit Aurora"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Arbeit Aurora"
rm "126718-Arbeit Aurora.tar.gz"


# Aurora Mini - has nice small scrollbar
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460763365/s/62091f882c55e56f9fb436c6a54a03a6/t/1532766473/u/88489-AuroraMini.gtp
wget ftp://vasilian.net/Gtk-Themes/88489-AuroraMini.gtp
tar zxvf 88489-AuroraMini.gtp
rm -rfv "/usr/share/themes/Aurora Mini"
mv "Aurora Mini" /usr/share/themes/
chown -Rv root:root "/usr/share/themes/Aurora Mini"
chcon -Rv -u system_u -r object_r -t usr_t "/usr/share/themes/Aurora Mini"
rm 88489-AuroraMini.gtp


# Caramel_Aurora - has something special
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460969992/s/d2aee979fbb135e298e86aa8da8b3bc8/t/1532766583/u/76581-Caramel_Aurora.tar.bz2
wget ftp://vasilian.net/Gtk-Themes/76581-Caramel_Aurora.tar.bz2
tar jxvf 76581-Caramel_Aurora.tar.bz2
rm -rfv /usr/share/themes/Caramel_Aurora
mv Caramel_Aurora /usr/share/themes/
chown -Rv root:root /usr/share/themes/Caramel_Aurora
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Caramel_Aurora
rm 76581-Caramel_Aurora.tar.bz2


# AuroraElementary
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460765468/s/0510a40d4d2417244aa84c9b475b7e1e/t/1532766633/u/85879-AuroraElementary-0.2.tar.gz
wget ftp://vasilian.net/Gtk-Themes/85879-AuroraElementary-0.2.tar.gz
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
wget ftp://vasilian.net/Gtk-Themes/23870-ClearLooks-Ice.tar.gz
tar zxvf 23870-ClearLooks-Ice.tar.gz
rm -rfv /usr/share/themes/ClearLooks-Ice
mv ClearLooks-Ice /usr/share/themes/
chown -Rv root:root /usr/share/themes/ClearLooks-Ice
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/ClearLooks-Ice
rm 23870-ClearLooks-Ice.tar.gz


# Clearlooks XPSilver - real nice theme
# wget https://dl.opendesktop.org/api/files/downloadfile/id/1460764027/s/effee4048da8e6eb93e95ab602bfc1cd4f8ae863c2269b5669665db44128bb64697c89d21f0d9143ef2e1afdc06f4648d735321bd1c48d75e2528642a715cf25/t/1543154161/u/56800/48568-Clearlooks-XPSilver.tar.bz2
wget ftp://vasilian.net/Gtk-Themes/48568-Clearlooks-XPSilver.tar.bz2
tar -jxvf 48568-Clearlooks-XPSilver.tar.bz2
rm -rfv /usr/share/themes/Clearlooks-XPSilver
mv Clearlooks-XPSilver /usr/share/themes/
chown -Rv root:root /usr/share/themes/Clearlooks-XPSilver
chcon -Rv -u system_u -r object_r -t usr_t /usr/share/themes/Clearlooks-XPSilver
rm 48568-Clearlooks-XPSilver.tar.bz2



# Do not add windows decorations here.
# Continue from top of page :
# https://www.xfce-look.org/browse/cat/138/page/22/ord/latest/
