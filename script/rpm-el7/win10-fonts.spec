#
# Spec file for win10-fonts
#
# The current archive contains fonts from Win7, Win8 and Win10.
# The .fon fonts could not be converted with fontforge+autotrace, so they got
# removed from the package.
#
# ftp://vasilian.net/Misc/win10-fonts.tar.gz


%define    _topdir       /home/mihai/rpmbuild
%define    name          win10-fonts
%define    version       1.1
%define    release       1.el7
%define    buildroot     %{_topdir}/%{name}-%{version}-root


BuildRoot:    %{buildroot}
Summary:      Windows 10 fonts
License:      Proprietary
Name:         %{name}
Version:      %{version}
Release:      %{release}
Source:       %{name}.tar.gz
Prefix:       /
Group:        User Interface/X
Requires:     freetype, fontconfig



%description
Windows 10 fonts.


%prep
rm -rfvd  $RPM_BUILD_DIR/win10-fonts
tar -zxvf $RPM_SOURCE_DIR/win10-fonts.tar.gz


%build
cd $RPM_BUILD_DIR/win10-fonts
make all

%install
cd $RPM_BUILD_DIR/win10-fonts
make DESTDIR=$RPM_BUILD_ROOT/usr/share/fonts/win10-fonts install


%post
if [ "$1" == "1" ]; then
	fc-cache --force --system-only --verbose  /usr/share/fonts/win10-fonts
fi

%postun
if [ "$1" == "0" ]; then
	rm -rfvd /usr/share/fonts/win10-fonts
	fc-cache --force --system-only --verbose  /usr/share/fonts/
fi



%files
%defattr(-,root,root)
/usr/share/fonts/win10-fonts/AdobeArabic-Bold.otf
/usr/share/fonts/win10-fonts/AdobeArabic-BoldItalic.otf
/usr/share/fonts/win10-fonts/AdobeArabic-Italic.otf
/usr/share/fonts/win10-fonts/AdobeArabic-Regular.otf
/usr/share/fonts/win10-fonts/AdobeHebrew-Bold.otf
/usr/share/fonts/win10-fonts/AdobeHebrew-BoldItalic.otf
/usr/share/fonts/win10-fonts/AdobeHebrew-Italic.otf
/usr/share/fonts/win10-fonts/AdobeHebrew-Regular.otf
/usr/share/fonts/win10-fonts/CAMBRIA_0.TTC
/usr/share/fonts/win10-fonts/Caladea-Bold.ttf
/usr/share/fonts/win10-fonts/Caladea-BoldItalic.ttf
/usr/share/fonts/win10-fonts/Caladea-Italic.ttf
/usr/share/fonts/win10-fonts/Caladea-Regular.ttf
/usr/share/fonts/win10-fonts/Candara.ttf
/usr/share/fonts/win10-fonts/Candarab.ttf
/usr/share/fonts/win10-fonts/Candarai.ttf
/usr/share/fonts/win10-fonts/Candaraz.ttf
/usr/share/fonts/win10-fonts/Carlito-Bold.ttf
/usr/share/fonts/win10-fonts/Carlito-BoldItalic.ttf
/usr/share/fonts/win10-fonts/Carlito-Italic.ttf
/usr/share/fonts/win10-fonts/Carlito-Regular.ttf
/usr/share/fonts/win10-fonts/DejaVuMathTeXGyre.ttf
/usr/share/fonts/win10-fonts/DejaVuSans-Bold.ttf
/usr/share/fonts/win10-fonts/DejaVuSans-BoldOblique.ttf
/usr/share/fonts/win10-fonts/DejaVuSans-ExtraLight.ttf
/usr/share/fonts/win10-fonts/DejaVuSans-Oblique.ttf
/usr/share/fonts/win10-fonts/DejaVuSans.ttf
/usr/share/fonts/win10-fonts/DejaVuSansCondensed-Bold.ttf
/usr/share/fonts/win10-fonts/DejaVuSansCondensed-BoldOblique.ttf
/usr/share/fonts/win10-fonts/DejaVuSansCondensed-Oblique.ttf
/usr/share/fonts/win10-fonts/DejaVuSansCondensed.ttf
/usr/share/fonts/win10-fonts/DejaVuSansMono-Bold.ttf
/usr/share/fonts/win10-fonts/DejaVuSansMono-BoldOblique.ttf
/usr/share/fonts/win10-fonts/DejaVuSansMono-Oblique.ttf
/usr/share/fonts/win10-fonts/DejaVuSansMono.ttf
/usr/share/fonts/win10-fonts/DejaVuSerif-Bold.ttf
/usr/share/fonts/win10-fonts/DejaVuSerif-BoldItalic.ttf
/usr/share/fonts/win10-fonts/DejaVuSerif-Italic.ttf
/usr/share/fonts/win10-fonts/DejaVuSerif.ttf
/usr/share/fonts/win10-fonts/DejaVuSerifCondensed-Bold.ttf
/usr/share/fonts/win10-fonts/DejaVuSerifCondensed-BoldItalic.ttf
/usr/share/fonts/win10-fonts/DejaVuSerifCondensed-Italic.ttf
/usr/share/fonts/win10-fonts/DejaVuSerifCondensed.ttf
/usr/share/fonts/win10-fonts/EmojiOneColor-SVGinOT.ttf
/usr/share/fonts/win10-fonts/Gabriola.ttf
/usr/share/fonts/win10-fonts/GenBasB.ttf
/usr/share/fonts/win10-fonts/GenBasBI.ttf
/usr/share/fonts/win10-fonts/GenBasI.ttf
/usr/share/fonts/win10-fonts/GenBasR.ttf
/usr/share/fonts/win10-fonts/GenBkBasB.ttf
/usr/share/fonts/win10-fonts/GenBkBasBI.ttf
/usr/share/fonts/win10-fonts/GenBkBasI.ttf
/usr/share/fonts/win10-fonts/GenBkBasR.ttf
/usr/share/fonts/win10-fonts/Inkfree.ttf
/usr/share/fonts/win10-fonts/KhmerUI.ttf
/usr/share/fonts/win10-fonts/KhmerUIb.ttf
/usr/share/fonts/win10-fonts/LaoUI.ttf
/usr/share/fonts/win10-fonts/LaoUIb.ttf
/usr/share/fonts/win10-fonts/LeelUIsl.ttf
/usr/share/fonts/win10-fonts/LeelaUIb.ttf
/usr/share/fonts/win10-fonts/LeelawUI.ttf
/usr/share/fonts/win10-fonts/LiberationMono-Bold.ttf
/usr/share/fonts/win10-fonts/LiberationMono-BoldItalic.ttf
/usr/share/fonts/win10-fonts/LiberationMono-Italic.ttf
/usr/share/fonts/win10-fonts/LiberationMono-Regular.ttf
/usr/share/fonts/win10-fonts/LiberationSans-Bold.ttf
/usr/share/fonts/win10-fonts/LiberationSans-BoldItalic.ttf
/usr/share/fonts/win10-fonts/LiberationSans-Italic.ttf
/usr/share/fonts/win10-fonts/LiberationSans-Regular.ttf
/usr/share/fonts/win10-fonts/LiberationSansNarrow-Bold.ttf
/usr/share/fonts/win10-fonts/LiberationSansNarrow-BoldItalic.ttf
/usr/share/fonts/win10-fonts/LiberationSansNarrow-Italic.ttf
/usr/share/fonts/win10-fonts/LiberationSansNarrow-Regular.ttf
/usr/share/fonts/win10-fonts/LiberationSerif-Bold.ttf
/usr/share/fonts/win10-fonts/LiberationSerif-BoldItalic.ttf
/usr/share/fonts/win10-fonts/LiberationSerif-Italic.ttf
/usr/share/fonts/win10-fonts/LiberationSerif-Regular.ttf
/usr/share/fonts/win10-fonts/LinBiolinum_RB_G.ttf
/usr/share/fonts/win10-fonts/LinBiolinum_RI_G.ttf
/usr/share/fonts/win10-fonts/LinBiolinum_R_G.ttf
/usr/share/fonts/win10-fonts/LinLibertine_DR_G.ttf
/usr/share/fonts/win10-fonts/LinLibertine_RBI_G.ttf
/usr/share/fonts/win10-fonts/LinLibertine_RB_G.ttf
/usr/share/fonts/win10-fonts/LinLibertine_RI_G.ttf
/usr/share/fonts/win10-fonts/LinLibertine_RZI_G.ttf
/usr/share/fonts/win10-fonts/LinLibertine_RZ_G.ttf
/usr/share/fonts/win10-fonts/LinLibertine_R_G.ttf
/usr/share/fonts/win10-fonts/Nirmala.ttf
/usr/share/fonts/win10-fonts/NirmalaB.ttf
/usr/share/fonts/win10-fonts/NirmalaS.ttf
/usr/share/fonts/win10-fonts/OpenSans-Bold.ttf
/usr/share/fonts/win10-fonts/OpenSans-BoldItalic.ttf
/usr/share/fonts/win10-fonts/OpenSans-Italic.ttf
/usr/share/fonts/win10-fonts/OpenSans-Regular.ttf
/usr/share/fonts/win10-fonts/PT_Serif-Web-Bold.ttf
/usr/share/fonts/win10-fonts/PT_Serif-Web-BoldItalic.ttf
/usr/share/fonts/win10-fonts/PT_Serif-Web-Italic.ttf
/usr/share/fonts/win10-fonts/PT_Serif-Web-Regular.ttf
/usr/share/fonts/win10-fonts/Shonar.ttf
/usr/share/fonts/win10-fonts/Shonarb.ttf
/usr/share/fonts/win10-fonts/Sitka.ttc
/usr/share/fonts/win10-fonts/SitkaB.ttc
/usr/share/fonts/win10-fonts/SitkaI.ttc
/usr/share/fonts/win10-fonts/SitkaZ.ttc
/usr/share/fonts/win10-fonts/SourceCodePro-Black.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-BlackIt.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-Bold.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-BoldIt.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-ExtraLight.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-ExtraLightIt.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-It.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-Light.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-LightIt.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-Medium.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-MediumIt.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-Regular.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-Semibold.ttf
/usr/share/fonts/win10-fonts/SourceCodePro-SemiboldIt.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-Black.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-BlackIt.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-Bold.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-BoldIt.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-ExtraLight.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-ExtraLightIt.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-It.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-Light.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-LightIt.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-Regular.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-Semibold.ttf
/usr/share/fonts/win10-fonts/SourceSansPro-SemiboldIt.ttf
/usr/share/fonts/win10-fonts/UrdType.ttf
/usr/share/fonts/win10-fonts/UrdTypeb.ttf
/usr/share/fonts/win10-fonts/Vani.ttf
/usr/share/fonts/win10-fonts/Vanib.ttf
/usr/share/fonts/win10-fonts/WinSoftPro-BItal.otf
/usr/share/fonts/win10-fonts/WinSoftPro-Bold.otf
/usr/share/fonts/win10-fonts/WinSoftPro-MItal.otf
/usr/share/fonts/win10-fonts/WinSoftPro-Med.otf
/usr/share/fonts/win10-fonts/YuGothB.ttc
/usr/share/fonts/win10-fonts/YuGothL.ttc
/usr/share/fonts/win10-fonts/YuGothM.ttc
/usr/share/fonts/win10-fonts/YuGothR.ttc
/usr/share/fonts/win10-fonts/ahronbd.ttf
/usr/share/fonts/win10-fonts/aldhabi.ttf
/usr/share/fonts/win10-fonts/andlso.ttf
/usr/share/fonts/win10-fonts/angsa.ttf
/usr/share/fonts/win10-fonts/angsab.ttf
/usr/share/fonts/win10-fonts/angsai.ttf
/usr/share/fonts/win10-fonts/angsau.ttf
/usr/share/fonts/win10-fonts/angsaub.ttf
/usr/share/fonts/win10-fonts/angsauz.ttf
/usr/share/fonts/win10-fonts/angsaz.ttf
/usr/share/fonts/win10-fonts/aparaj.ttf
/usr/share/fonts/win10-fonts/aparajb.ttf
/usr/share/fonts/win10-fonts/aparajbi.ttf
/usr/share/fonts/win10-fonts/aparaji.ttf
/usr/share/fonts/win10-fonts/arabtype.ttf
/usr/share/fonts/win10-fonts/arial.ttf
/usr/share/fonts/win10-fonts/arialbd.ttf
/usr/share/fonts/win10-fonts/arialbi.ttf
/usr/share/fonts/win10-fonts/ariali.ttf
/usr/share/fonts/win10-fonts/ariblk.ttf
/usr/share/fonts/win10-fonts/bahnschrift.ttf
/usr/share/fonts/win10-fonts/batang.ttc
/usr/share/fonts/win10-fonts/browa.ttf
/usr/share/fonts/win10-fonts/browab.ttf
/usr/share/fonts/win10-fonts/browai.ttf
/usr/share/fonts/win10-fonts/browau.ttf
/usr/share/fonts/win10-fonts/browaub.ttf
/usr/share/fonts/win10-fonts/browaui.ttf
/usr/share/fonts/win10-fonts/browauz.ttf
/usr/share/fonts/win10-fonts/browaz.ttf
/usr/share/fonts/win10-fonts/calibri.ttf
/usr/share/fonts/win10-fonts/calibrib.ttf
/usr/share/fonts/win10-fonts/calibrii.ttf
/usr/share/fonts/win10-fonts/calibril.ttf
/usr/share/fonts/win10-fonts/calibrili.ttf
/usr/share/fonts/win10-fonts/calibriz.ttf
/usr/share/fonts/win10-fonts/cambria.ttc
/usr/share/fonts/win10-fonts/cambriab.ttf
/usr/share/fonts/win10-fonts/cambriai.ttf
/usr/share/fonts/win10-fonts/cambriaz.ttf
/usr/share/fonts/win10-fonts/comic.ttf
/usr/share/fonts/win10-fonts/comicbd.ttf
/usr/share/fonts/win10-fonts/comici.ttf
/usr/share/fonts/win10-fonts/comicz.ttf
/usr/share/fonts/win10-fonts/consola.ttf
/usr/share/fonts/win10-fonts/consolab.ttf
/usr/share/fonts/win10-fonts/consolai.ttf
/usr/share/fonts/win10-fonts/consolaz.ttf
/usr/share/fonts/win10-fonts/constan.ttf
/usr/share/fonts/win10-fonts/constanb.ttf
/usr/share/fonts/win10-fonts/constani.ttf
/usr/share/fonts/win10-fonts/constanz.ttf
/usr/share/fonts/win10-fonts/corbel.ttf
/usr/share/fonts/win10-fonts/corbelb.ttf
/usr/share/fonts/win10-fonts/corbeli.ttf
/usr/share/fonts/win10-fonts/corbelz.ttf
/usr/share/fonts/win10-fonts/cordia.ttf
/usr/share/fonts/win10-fonts/cordiab.ttf
/usr/share/fonts/win10-fonts/cordiai.ttf
/usr/share/fonts/win10-fonts/cordiau.ttf
/usr/share/fonts/win10-fonts/cordiaub.ttf
/usr/share/fonts/win10-fonts/cordiaui.ttf
/usr/share/fonts/win10-fonts/cordiauz.ttf
/usr/share/fonts/win10-fonts/cordiaz.ttf
/usr/share/fonts/win10-fonts/cour.ttf
/usr/share/fonts/win10-fonts/courbd.ttf
/usr/share/fonts/win10-fonts/courbi.ttf
/usr/share/fonts/win10-fonts/couri.ttf
/usr/share/fonts/win10-fonts/daunpenh.ttf
/usr/share/fonts/win10-fonts/david.ttf
/usr/share/fonts/win10-fonts/davidbd.ttf
/usr/share/fonts/win10-fonts/dokchamp.ttf
/usr/share/fonts/win10-fonts/ebrima.ttf
/usr/share/fonts/win10-fonts/ebrimabd.ttf
/usr/share/fonts/win10-fonts/estre.ttf
/usr/share/fonts/win10-fonts/euphemia.ttf
/usr/share/fonts/win10-fonts/framd.ttf
/usr/share/fonts/win10-fonts/framdit.ttf
/usr/share/fonts/win10-fonts/frank.ttf
/usr/share/fonts/win10-fonts/gadugi.ttf
/usr/share/fonts/win10-fonts/gadugib.ttf
/usr/share/fonts/win10-fonts/gautami.ttf
/usr/share/fonts/win10-fonts/gautamib.ttf
/usr/share/fonts/win10-fonts/georgia.ttf
/usr/share/fonts/win10-fonts/georgiab.ttf
/usr/share/fonts/win10-fonts/georgiai.ttf
/usr/share/fonts/win10-fonts/georgiaz.ttf
/usr/share/fonts/win10-fonts/gisha.ttf
/usr/share/fonts/win10-fonts/gishabd.ttf
/usr/share/fonts/win10-fonts/gulim.ttc
/usr/share/fonts/win10-fonts/himalaya.ttf
/usr/share/fonts/win10-fonts/holomdl2.ttf
/usr/share/fonts/win10-fonts/impact.ttf
/usr/share/fonts/win10-fonts/iskpota.ttf
/usr/share/fonts/win10-fonts/iskpotab.ttf
/usr/share/fonts/win10-fonts/javatext.ttf
/usr/share/fonts/win10-fonts/kaiu.ttf
/usr/share/fonts/win10-fonts/kalinga.ttf
/usr/share/fonts/win10-fonts/kalingab.ttf
/usr/share/fonts/win10-fonts/kartika.ttf
/usr/share/fonts/win10-fonts/kartikab.ttf
/usr/share/fonts/win10-fonts/kokila.ttf
/usr/share/fonts/win10-fonts/kokilab.ttf
/usr/share/fonts/win10-fonts/kokilabi.ttf
/usr/share/fonts/win10-fonts/kokilai.ttf
/usr/share/fonts/win10-fonts/l_10646.ttf
/usr/share/fonts/win10-fonts/latha.ttf
/usr/share/fonts/win10-fonts/lathab.ttf
/usr/share/fonts/win10-fonts/leelawad.ttf
/usr/share/fonts/win10-fonts/leelawdb.ttf
/usr/share/fonts/win10-fonts/lucon.ttf
/usr/share/fonts/win10-fonts/lvnm.ttf
/usr/share/fonts/win10-fonts/lvnmbd.ttf
/usr/share/fonts/win10-fonts/majalla.ttf
/usr/share/fonts/win10-fonts/majallab.ttf
/usr/share/fonts/win10-fonts/malgun.ttf
/usr/share/fonts/win10-fonts/malgunbd.ttf
/usr/share/fonts/win10-fonts/malgunsl.ttf
/usr/share/fonts/win10-fonts/mangal.ttf
/usr/share/fonts/win10-fonts/mangalb.ttf
/usr/share/fonts/win10-fonts/meiryo.ttc
/usr/share/fonts/win10-fonts/meiryob.ttc
/usr/share/fonts/win10-fonts/micross.ttf
/usr/share/fonts/win10-fonts/mingliu.ttc
/usr/share/fonts/win10-fonts/mingliub.ttc
/usr/share/fonts/win10-fonts/mmrtext.ttf
/usr/share/fonts/win10-fonts/mmrtextb.ttf
/usr/share/fonts/win10-fonts/monbaiti.ttf
/usr/share/fonts/win10-fonts/moolbor.ttf
/usr/share/fonts/win10-fonts/mriam.ttf
/usr/share/fonts/win10-fonts/mriamc.ttf
/usr/share/fonts/win10-fonts/msgothic.ttc
/usr/share/fonts/win10-fonts/msjh.ttc
/usr/share/fonts/win10-fonts/msjh.ttf
/usr/share/fonts/win10-fonts/msjhbd.ttc
/usr/share/fonts/win10-fonts/msjhbd.ttf
/usr/share/fonts/win10-fonts/msjhl.ttc
/usr/share/fonts/win10-fonts/msmincho.ttc
/usr/share/fonts/win10-fonts/msuighub.ttf
/usr/share/fonts/win10-fonts/msuighur.ttf
/usr/share/fonts/win10-fonts/msyh.ttc
/usr/share/fonts/win10-fonts/msyh.ttf
/usr/share/fonts/win10-fonts/msyhbd.ttc
/usr/share/fonts/win10-fonts/msyhbd.ttf
/usr/share/fonts/win10-fonts/msyhl.ttc
/usr/share/fonts/win10-fonts/msyi.ttf
/usr/share/fonts/win10-fonts/mvboli.ttf
/usr/share/fonts/win10-fonts/nrkis.ttf
/usr/share/fonts/win10-fonts/ntailu.ttf
/usr/share/fonts/win10-fonts/ntailub.ttf
/usr/share/fonts/win10-fonts/nyala.ttf
/usr/share/fonts/win10-fonts/opens___.ttf
/usr/share/fonts/win10-fonts/pala.ttf
/usr/share/fonts/win10-fonts/palab.ttf
/usr/share/fonts/win10-fonts/palabi.ttf
/usr/share/fonts/win10-fonts/palai.ttf
/usr/share/fonts/win10-fonts/phagspa.ttf
/usr/share/fonts/win10-fonts/phagspab.ttf
/usr/share/fonts/win10-fonts/plantc.ttf
/usr/share/fonts/win10-fonts/raavi.ttf
/usr/share/fonts/win10-fonts/raavib.ttf
/usr/share/fonts/win10-fonts/rod.ttf
/usr/share/fonts/win10-fonts/segmdl2.ttf
/usr/share/fonts/win10-fonts/segoepr.ttf
/usr/share/fonts/win10-fonts/segoeprb.ttf
/usr/share/fonts/win10-fonts/segoesc.ttf
/usr/share/fonts/win10-fonts/segoescb.ttf
/usr/share/fonts/win10-fonts/segoeui.ttf
/usr/share/fonts/win10-fonts/segoeuib.ttf
/usr/share/fonts/win10-fonts/segoeuii.ttf
/usr/share/fonts/win10-fonts/segoeuil.ttf
/usr/share/fonts/win10-fonts/segoeuisl.ttf
/usr/share/fonts/win10-fonts/segoeuiz.ttf
/usr/share/fonts/win10-fonts/seguibl.ttf
/usr/share/fonts/win10-fonts/seguibli.ttf
/usr/share/fonts/win10-fonts/seguiemj.ttf
/usr/share/fonts/win10-fonts/seguihis.ttf
/usr/share/fonts/win10-fonts/seguili.ttf
/usr/share/fonts/win10-fonts/seguisb.ttf
/usr/share/fonts/win10-fonts/seguisbi.ttf
/usr/share/fonts/win10-fonts/seguisli.ttf
/usr/share/fonts/win10-fonts/seguisym.ttf
/usr/share/fonts/win10-fonts/shruti.ttf
/usr/share/fonts/win10-fonts/shrutib.ttf
/usr/share/fonts/win10-fonts/simfang.ttf
/usr/share/fonts/win10-fonts/simhei.ttf
/usr/share/fonts/win10-fonts/simkai.ttf
/usr/share/fonts/win10-fonts/simpbdo.ttf
/usr/share/fonts/win10-fonts/simpfxo.ttf
/usr/share/fonts/win10-fonts/simpo.ttf
/usr/share/fonts/win10-fonts/simsun.ttc
/usr/share/fonts/win10-fonts/simsunb.ttf
/usr/share/fonts/win10-fonts/sylfaen.ttf
/usr/share/fonts/win10-fonts/symbol.ttf
/usr/share/fonts/win10-fonts/tahoma.ttf
/usr/share/fonts/win10-fonts/tahomabd.ttf
/usr/share/fonts/win10-fonts/taile.ttf
/usr/share/fonts/win10-fonts/taileb.ttf
/usr/share/fonts/win10-fonts/times.ttf
/usr/share/fonts/win10-fonts/timesbd.ttf
/usr/share/fonts/win10-fonts/timesbi.ttf
/usr/share/fonts/win10-fonts/timesi.ttf
/usr/share/fonts/win10-fonts/tradbdo.ttf
/usr/share/fonts/win10-fonts/trado.ttf
/usr/share/fonts/win10-fonts/trebuc.ttf
/usr/share/fonts/win10-fonts/trebucbd.ttf
/usr/share/fonts/win10-fonts/trebucbi.ttf
/usr/share/fonts/win10-fonts/trebucit.ttf
/usr/share/fonts/win10-fonts/tunga.ttf
/usr/share/fonts/win10-fonts/tungab.ttf
/usr/share/fonts/win10-fonts/upcdb.ttf
/usr/share/fonts/win10-fonts/upcdbi.ttf
/usr/share/fonts/win10-fonts/upcdi.ttf
/usr/share/fonts/win10-fonts/upcdl.ttf
/usr/share/fonts/win10-fonts/upceb.ttf
/usr/share/fonts/win10-fonts/upcebi.ttf
/usr/share/fonts/win10-fonts/upcei.ttf
/usr/share/fonts/win10-fonts/upcel.ttf
/usr/share/fonts/win10-fonts/upcfb.ttf
/usr/share/fonts/win10-fonts/upcfbi.ttf
/usr/share/fonts/win10-fonts/upcfi.ttf
/usr/share/fonts/win10-fonts/upcfl.ttf
/usr/share/fonts/win10-fonts/upcib.ttf
/usr/share/fonts/win10-fonts/upcibi.ttf
/usr/share/fonts/win10-fonts/upcii.ttf
/usr/share/fonts/win10-fonts/upcil.ttf
/usr/share/fonts/win10-fonts/upcjb.ttf
/usr/share/fonts/win10-fonts/upcjbi.ttf
/usr/share/fonts/win10-fonts/upcji.ttf
/usr/share/fonts/win10-fonts/upcjl.ttf
/usr/share/fonts/win10-fonts/upckb.ttf
/usr/share/fonts/win10-fonts/upckbi.ttf
/usr/share/fonts/win10-fonts/upcki.ttf
/usr/share/fonts/win10-fonts/upckl.ttf
/usr/share/fonts/win10-fonts/upclb.ttf
/usr/share/fonts/win10-fonts/upclbi.ttf
/usr/share/fonts/win10-fonts/upcli.ttf
/usr/share/fonts/win10-fonts/upcll.ttf
/usr/share/fonts/win10-fonts/utsaah.ttf
/usr/share/fonts/win10-fonts/utsaahb.ttf
/usr/share/fonts/win10-fonts/utsaahbi.ttf
/usr/share/fonts/win10-fonts/utsaahi.ttf
/usr/share/fonts/win10-fonts/verdana.ttf
/usr/share/fonts/win10-fonts/verdanab.ttf
/usr/share/fonts/win10-fonts/verdanai.ttf
/usr/share/fonts/win10-fonts/verdanaz.ttf
/usr/share/fonts/win10-fonts/vijaya.ttf
/usr/share/fonts/win10-fonts/vijayab.ttf
/usr/share/fonts/win10-fonts/vrinda.ttf
/usr/share/fonts/win10-fonts/vrindab.ttf
/usr/share/fonts/win10-fonts/yugothib.ttf
/usr/share/fonts/win10-fonts/yugothic.ttf
/usr/share/fonts/win10-fonts/yugothil.ttf
/usr/share/fonts/win10-fonts/yumin.ttf
/usr/share/fonts/win10-fonts/yumindb.ttf
/usr/share/fonts/win10-fonts/yuminl.ttf


%changelog
* Sun Feb 3 2019 Mihai Vasilian <grayasm@gmail.com> 1.1-1.el7
- Collected the fonts from Win7, Win8 and Win10. Total 402 files.
* Sun Oct 2 2016 Mihai Vasilian <grayasm@gmail.com> 1.0-1.el7
- Initial package.
