all:
	echo "Done"

clean:
	echo "Done"


# Either install all files invidually or run a for loop over win10-fonts dir:
#
# for file in /path/to/win10-fonts/*;do
#     install -m 755 "$file" ~/
# done


# make DESTDIR=/opt/win10-fonts install
install:
	install -D -m 0644 AdobeArabic-BoldItalic.otf 	$(DESTDIR)/AdobeArabic-BoldItalic.otf
	install -D -m 0644 AdobeArabic-Bold.otf			$(DESTDIR)/AdobeArabic-Bold.otf
	install -D -m 0644 AdobeArabic-Italic.otf		$(DESTDIR)/AdobeArabic-Italic.otf
	install -D -m 0644 AdobeArabic-Regular.otf		$(DESTDIR)/AdobeArabic-Regular.otf
	install -D -m 0644 AdobeHebrew-BoldItalic.otf	$(DESTDIR)/AdobeHebrew-BoldItalic.otf
	install -D -m 0644 AdobeHebrew-Bold.otf			$(DESTDIR)/AdobeHebrew-Bold.otf
	install -D -m 0644 AdobeHebrew-Italic.otf		$(DESTDIR)/AdobeHebrew-Italic.otf
	install -D -m 0644 AdobeHebrew-Regular.otf		$(DESTDIR)/AdobeHebrew-Regular.otf
	install -D -m 0644 ahronbd.ttf					$(DESTDIR)/ahronbd.ttf
	install -D -m 0644 aldhabi.ttf					$(DESTDIR)/aldhabi.ttf
	install -D -m 0644 andlso.ttf					$(DESTDIR)/andlso.ttf
	install -D -m 0644 angsab.ttf					$(DESTDIR)/angsab.ttf
	install -D -m 0644 angsai.ttf					$(DESTDIR)/angsai.ttf
	install -D -m 0644 angsa.ttf					$(DESTDIR)/angsa.ttf
	install -D -m 0644 angsaub.ttf					$(DESTDIR)/angsaub.ttf
	install -D -m 0644 angsaui.ttf					$(DESTDIR)/angsaub.ttf
	install -D -m 0644 angsau.ttf					$(DESTDIR)/angsau.ttf
	install -D -m 0644 angsauz.ttf					$(DESTDIR)/angsauz.ttf
	install -D -m 0644 angsaz.ttf					$(DESTDIR)/angsaz.ttf
	install -D -m 0644 aparajbi.ttf					$(DESTDIR)/aparajbi.ttf
	install -D -m 0644 aparajb.ttf					$(DESTDIR)/aparajb.ttf
	install -D -m 0644 aparaji.ttf					$(DESTDIR)/aparaji.ttf
	install -D -m 0644 aparaj.ttf					$(DESTDIR)/aparaj.ttf
	install -D -m 0644 arabtype.ttf					$(DESTDIR)/arabtype.ttf
	install -D -m 0644 arialbd.ttf					$(DESTDIR)/arialbd.ttf
	install -D -m 0644 arialbi.ttf					$(DESTDIR)/arialbi.ttf
	install -D -m 0644 ariali.ttf					$(DESTDIR)/ariali.ttf
	install -D -m 0644 arial.ttf					$(DESTDIR)/arial.ttf
	install -D -m 0644 ariblk.ttf					$(DESTDIR)/ariblk.ttf
	install -D -m 0644 bahnschrift.ttf				$(DESTDIR)/bahnschrift.ttf
	install -D -m 0644 batang.ttc					$(DESTDIR)/batang.ttc
	install -D -m 0644 browab.ttf					$(DESTDIR)/browab.ttf
	install -D -m 0644 browai.ttf					$(DESTDIR)/browai.ttf
	install -D -m 0644 browa.ttf					$(DESTDIR)/browa.ttf
	install -D -m 0644 browaub.ttf					$(DESTDIR)/browaub.ttf
	install -D -m 0644 browaui.ttf					$(DESTDIR)/browaui.ttf
	install -D -m 0644 browau.ttf					$(DESTDIR)/browau.ttf
	install -D -m 0644 browauz.ttf					$(DESTDIR)/browauz.ttf
	install -D -m 0644 browaz.ttf					$(DESTDIR)/browaz.ttf
	install -D -m 0644 Caladea-BoldItalic.ttf		$(DESTDIR)/Caladea-BoldItalic.ttf
	install -D -m 0644 Caladea-Bold.ttf				$(DESTDIR)/Caladea-Bold.ttf
	install -D -m 0644 Caladea-Italic.ttf			$(DESTDIR)/Caladea-Italic.ttf
	install -D -m 0644 Caladea-Regular.ttf			$(DESTDIR)/Caladea-Regular.ttf
	install -D -m 0644 calibrib.ttf					$(DESTDIR)/calibrib.ttf
	install -D -m 0644 calibrii.ttf					$(DESTDIR)/calibrii.ttf
	install -D -m 0644 calibrili.ttf				$(DESTDIR)/calibrili.ttf
	install -D -m 0644 calibril.ttf					$(DESTDIR)/calibril.ttf
	install -D -m 0644 calibri.ttf					$(DESTDIR)/calibri.ttf
	install -D -m 0644 calibriz.ttf					$(DESTDIR)/calibriz.ttf
	install -D -m 0644 CAMBRIA_0.TTC				$(DESTDIR)/CAMBRIA_0.TTC
	install -D -m 0644 cambriab.ttf					$(DESTDIR)/cambriab.ttf
	install -D -m 0644 cambriai.ttf					$(DESTDIR)/cambriai.ttf
	install -D -m 0644 cambria.ttc					$(DESTDIR)/cambria.ttc
	install -D -m 0644 cambriaz.ttf					$(DESTDIR)/cambriaz.ttf
	install -D -m 0644 Candarab.ttf					$(DESTDIR)/Candarab.ttf
	install -D -m 0644 Candarai.ttf					$(DESTDIR)/Candarai.ttf
	install -D -m 0644 Candara.ttf					$(DESTDIR)/Candara.ttf
	install -D -m 0644 Candaraz.ttf					$(DESTDIR)/Candaraz.ttf
	install -D -m 0644 Carlito-BoldItalic.ttf		$(DESTDIR)/Carlito-BoldItalic.ttf
	install -D -m 0644 Carlito-Bold.ttf				$(DESTDIR)/Carlito-Bold.ttf
	install -D -m 0644 Carlito-Italic.ttf			$(DESTDIR)/Carlito-Italic.ttf
	install -D -m 0644 Carlito-Regular.ttf			$(DESTDIR)/Carlito-Regular.ttf
	install -D -m 0644 comicbd.ttf					$(DESTDIR)/comicbd.ttf
	install -D -m 0644 comici.ttf					$(DESTDIR)/comici.ttf
	install -D -m 0644 comic.ttf					$(DESTDIR)/comic.ttf
	install -D -m 0644 comicz.ttf					$(DESTDIR)/comicz.ttf
	install -D -m 0644 consolab.ttf					$(DESTDIR)/consolab.ttf
	install -D -m 0644 consolai.ttf					$(DESTDIR)/consolai.ttf
	install -D -m 0644 consola.ttf					$(DESTDIR)/consola.ttf
	install -D -m 0644 consolaz.ttf					$(DESTDIR)/consolaz.ttf
	install -D -m 0644 constanb.ttf					$(DESTDIR)/constanb.ttf
	install -D -m 0644 constani.ttf					$(DESTDIR)/constani.ttf
	install -D -m 0644 constan.ttf					$(DESTDIR)/constan.ttf
	install -D -m 0644 constanz.ttf					$(DESTDIR)/constanz.ttf
	install -D -m 0644 corbelb.ttf					$(DESTDIR)/corbelb.ttf
	install -D -m 0644 corbeli.ttf					$(DESTDIR)/corbeli.ttf
	install -D -m 0644 corbel.ttf					$(DESTDIR)/corbel.ttf
	install -D -m 0644 corbelz.ttf					$(DESTDIR)/corbelz.ttf
	install -D -m 0644 cordiab.ttf					$(DESTDIR)/cordiab.ttf
	install -D -m 0644 cordiai.ttf					$(DESTDIR)/cordiai.ttf
	install -D -m 0644 cordia.ttf					$(DESTDIR)/cordia.ttf
	install -D -m 0644 cordiaub.ttf					$(DESTDIR)/cordiaub.ttf
	install -D -m 0644 cordiaui.ttf					$(DESTDIR)/cordiaui.ttf
	install -D -m 0644 cordiau.ttf					$(DESTDIR)/cordiau.ttf
	install -D -m 0644 cordiauz.ttf					$(DESTDIR)/cordiauz.ttf
	install -D -m 0644 cordiaz.ttf					$(DESTDIR)/cordiaz.ttf
	install -D -m 0644 courbd.ttf					$(DESTDIR)/courbd.ttf
	install -D -m 0644 courbi.ttf					$(DESTDIR)/courbi.ttf
	install -D -m 0644 couri.ttf					$(DESTDIR)/couri.ttf
	install -D -m 0644 cour.ttf						$(DESTDIR)/cour.ttf
	install -D -m 0644 daunpenh.ttf					$(DESTDIR)/daunpenh.ttf
	install -D -m 0644 davidbd.ttf					$(DESTDIR)/davidbd.ttf
	install -D -m 0644 david.ttf					$(DESTDIR)/david.ttf
	install -D -m 0644 DejaVuMathTeXGyre.ttf		$(DESTDIR)/DejaVuMathTeXGyre.ttf
	install -D -m 0644 DejaVuSans-BoldOblique.ttf	$(DESTDIR)/DejaVuSans-BoldOblique.ttf
	install -D -m 0644 DejaVuSans-Bold.ttf					$(DESTDIR)/DejaVuSans-Bold.ttf
	install -D -m 0644 DejaVuSansCondensed-BoldOblique.ttf	$(DESTDIR)/DejaVuSansCondensed-BoldOblique.ttf
	install -D -m 0644 DejaVuSansCondensed-Bold.ttf			$(DESTDIR)/DejaVuSansCondensed-Bold.ttf
	install -D -m 0644 DejaVuSansCondensed-Oblique.ttf		$(DESTDIR)/DejaVuSansCondensed-Oblique.ttf
	install -D -m 0644 DejaVuSansCondensed.ttf				$(DESTDIR)/DejaVuSansCondensed.ttf
	install -D -m 0644 DejaVuSans-ExtraLight.ttf			$(DESTDIR)/DejaVuSans-ExtraLight.ttf
	install -D -m 0644 DejaVuSansMono-BoldOblique.ttf		$(DESTDIR)/DejaVuSansMono-BoldOblique.ttf
	install -D -m 0644 DejaVuSansMono-Bold.ttf				$(DESTDIR)/DejaVuSansMono-Bold.ttf
	install -D -m 0644 DejaVuSansMono-Oblique.ttf			$(DESTDIR)/DejaVuSansMono-Oblique.ttf
	install -D -m 0644 DejaVuSansMono.ttf					$(DESTDIR)/DejaVuSansMono.ttf
	install -D -m 0644 DejaVuSans-Oblique.ttf				$(DESTDIR)/DejaVuSans-Oblique.ttf
	install -D -m 0644 DejaVuSans.ttf						$(DESTDIR)/DejaVuSans.ttf
	install -D -m 0644 DejaVuSerif-BoldItalic.ttf			$(DESTDIR)/DejaVuSerif-BoldItalic.ttf
	install -D -m 0644 DejaVuSerif-Bold.ttf					$(DESTDIR)/DejaVuSerif-Bold.ttf
	install -D -m 0644 DejaVuSerifCondensed-BoldItalic.ttf	$(DESTDIR)/DejaVuSerifCondensed-BoldItalic.ttf
	install -D -m 0644 DejaVuSerifCondensed-Bold.ttf		$(DESTDIR)/DejaVuSerifCondensed-Bold.ttf
	install -D -m 0644 DejaVuSerifCondensed-Italic.ttf		$(DESTDIR)/DejaVuSerifCondensed-Italic.ttf
	install -D -m 0644 DejaVuSerifCondensed.ttf				$(DESTDIR)/DejaVuSerifCondensed.ttf
	install -D -m 0644 DejaVuSerif-Italic.ttf				$(DESTDIR)/DejaVuSerif-Italic.ttf
	install -D -m 0644 DejaVuSerif.ttf						$(DESTDIR)/DejaVuSerif.ttf
	install -D -m 0644 dokchamp.ttf							$(DESTDIR)/dokchamp.ttf
	install -D -m 0644 ebrimabd.ttf							$(DESTDIR)/ebrimabd.ttf
	install -D -m 0644 ebrima.ttf							$(DESTDIR)/ebrima.ttf
	install -D -m 0644 EmojiOneColor-SVGinOT.ttf			$(DESTDIR)/EmojiOneColor-SVGinOT.ttf
	install -D -m 0644 estre.ttf					$(DESTDIR)/estre.ttf
	install -D -m 0644 euphemia.ttf					$(DESTDIR)/euphemia.ttf
	install -D -m 0644 framdit.ttf					$(DESTDIR)/framdit.ttf
	install -D -m 0644 framd.ttf					$(DESTDIR)/framd.ttf
	install -D -m 0644 frank.ttf					$(DESTDIR)/frank.ttf
	install -D -m 0644 Gabriola.ttf					$(DESTDIR)/Gabriola.ttf
	install -D -m 0644 gadugib.ttf					$(DESTDIR)/gadugib.ttf
	install -D -m 0644 gadugi.ttf					$(DESTDIR)/gadugi.ttf
	install -D -m 0644 gautamib.ttf					$(DESTDIR)/gautamib.ttf
	install -D -m 0644 gautami.ttf					$(DESTDIR)/gautami.ttf
	install -D -m 0644 GenBasBI.ttf					$(DESTDIR)/GenBasBI.ttf
	install -D -m 0644 GenBasB.ttf					$(DESTDIR)/GenBasB.ttf
	install -D -m 0644 GenBasI.ttf					$(DESTDIR)/GenBasI.ttf
	install -D -m 0644 GenBasR.ttf					$(DESTDIR)/GenBasR.ttf
	install -D -m 0644 GenBkBasBI.ttf				$(DESTDIR)/GenBkBasBI.ttf
	install -D -m 0644 GenBkBasB.ttf				$(DESTDIR)/GenBkBasB.ttf
	install -D -m 0644 GenBkBasI.ttf				$(DESTDIR)/GenBkBasI.ttf
	install -D -m 0644 GenBkBasR.ttf				$(DESTDIR)/GenBkBasR.ttf
	install -D -m 0644 georgiab.ttf					$(DESTDIR)/georgiab.ttf
	install -D -m 0644 georgiai.ttf					$(DESTDIR)/georgiai.ttf
	install -D -m 0644 georgia.ttf					$(DESTDIR)/georgia.ttf
	install -D -m 0644 georgiaz.ttf					$(DESTDIR)/georgiaz.ttf
	install -D -m 0644 gishabd.ttf					$(DESTDIR)/gishabd.ttf
	install -D -m 0644 gisha.ttf					$(DESTDIR)/gisha.ttf
	install -D -m 0644 gulim.ttc					$(DESTDIR)/gulim.ttc
	install -D -m 0644 himalaya.ttf					$(DESTDIR)/himalaya.ttf
	install -D -m 0644 holomdl2.ttf					$(DESTDIR)/holomdl2.ttf
	install -D -m 0644 impact.ttf					$(DESTDIR)/impact.ttf
	install -D -m 0644 Inkfree.ttf					$(DESTDIR)/Inkfree.ttf
	install -D -m 0644 iskpotab.ttf					$(DESTDIR)/iskpotab.ttf
	install -D -m 0644 iskpota.ttf					$(DESTDIR)/iskpota.ttf
	install -D -m 0644 javatext.ttf					$(DESTDIR)/javatext.ttf
	install -D -m 0644 kaiu.ttf						$(DESTDIR)/kaiu.ttf
	install -D -m 0644 kalingab.ttf					$(DESTDIR)/kalingab.ttf
	install -D -m 0644 kalinga.ttf					$(DESTDIR)/kalinga.ttf
	install -D -m 0644 kartikab.ttf					$(DESTDIR)/kartikab.ttf
	install -D -m 0644 kartika.ttf					$(DESTDIR)/kartika.ttf
	install -D -m 0644 KhmerUIb.ttf					$(DESTDIR)/KhmerUIb.ttf
	install -D -m 0644 KhmerUI.ttf					$(DESTDIR)/KhmerUI.ttf
	install -D -m 0644 kokilabi.ttf					$(DESTDIR)/kokilabi.ttf
	install -D -m 0644 kokilab.ttf					$(DESTDIR)/kokilab.ttf
	install -D -m 0644 kokilai.ttf					$(DESTDIR)/kokilai.ttf
	install -D -m 0644 kokila.ttf					$(DESTDIR)/kokila.ttf
	install -D -m 0644 l_10646.ttf					$(DESTDIR)/l_10646.ttf
	install -D -m 0644 LaoUIb.ttf					$(DESTDIR)/LaoUIb.ttf
	install -D -m 0644 LaoUI.ttf					$(DESTDIR)/LaoUI.ttf
	install -D -m 0644 lathab.ttf					$(DESTDIR)/lathab.ttf
	install -D -m 0644 latha.ttf					$(DESTDIR)/latha.ttf
	install -D -m 0644 LeelaUIb.ttf					$(DESTDIR)/LeelaUIb.ttf
	install -D -m 0644 leelawad.ttf					$(DESTDIR)/leelawad.ttf
	install -D -m 0644 leelawdb.ttf					$(DESTDIR)/leelawdb.ttf
	install -D -m 0644 LeelawUI.ttf					$(DESTDIR)/LeelawUI.ttf
	install -D -m 0644 LeelUIsl.ttf					$(DESTDIR)/LeelUIsl.ttf
	install -D -m 0644 LiberationMono-BoldItalic.ttf		$(DESTDIR)/LiberationMono-BoldItalic.ttf
	install -D -m 0644 LiberationMono-Bold.ttf				$(DESTDIR)/LiberationMono-Bold.ttf
	install -D -m 0644 LiberationMono-Italic.ttf			$(DESTDIR)/LiberationMono-Italic.ttf
	install -D -m 0644 LiberationMono-Regular.ttf			$(DESTDIR)/LiberationMono-Regular.ttf
	install -D -m 0644 LiberationSans-BoldItalic.ttf		$(DESTDIR)/LiberationSans-BoldItalic.ttf
	install -D -m 0644 LiberationSans-Bold.ttf				$(DESTDIR)/LiberationSans-Bold.ttf
	install -D -m 0644 LiberationSans-Italic.ttf			$(DESTDIR)/LiberationSans-Italic.ttf
	install -D -m 0644 LiberationSansNarrow-BoldItalic.ttf	$(DESTDIR)/LiberationSansNarrow-BoldItalic.ttf
	install -D -m 0644 LiberationSansNarrow-Bold.ttf		$(DESTDIR)/LiberationSansNarrow-Bold.ttf
	install -D -m 0644 LiberationSansNarrow-Italic.ttf		$(DESTDIR)/LiberationSansNarrow-Italic.ttf
	install -D -m 0644 LiberationSansNarrow-Regular.ttf		$(DESTDIR)/LiberationSansNarrow-Regular.ttf
	install -D -m 0644 LiberationSans-Regular.ttf			$(DESTDIR)/LiberationSans-Regular.ttf
	install -D -m 0644 LiberationSerif-BoldItalic.ttf		$(DESTDIR)/LiberationSerif-BoldItalic.ttf
	install -D -m 0644 LiberationSerif-Bold.ttf				$(DESTDIR)/LiberationSerif-Bold.ttf
	install -D -m 0644 LiberationSerif-Italic.ttf			$(DESTDIR)/LiberationSerif-Italic.ttf
	install -D -m 0644 LiberationSerif-Regular.ttf			$(DESTDIR)/LiberationSerif-Regular.ttf
	install -D -m 0644 LinBiolinum_RB_G.ttf					$(DESTDIR)/LinBiolinum_RB_G.ttf
	install -D -m 0644 LinBiolinum_R_G.ttf					$(DESTDIR)/LinBiolinum_R_G.ttf
	install -D -m 0644 LinBiolinum_RI_G.ttf					$(DESTDIR)/LinBiolinum_RI_G.ttf
	install -D -m 0644 LinLibertine_DR_G.ttf				$(DESTDIR)/LinLibertine_DR_G.ttf
	install -D -m 0644 LinLibertine_RB_G.ttf				$(DESTDIR)/LinLibertine_RB_G.ttf
	install -D -m 0644 LinLibertine_RBI_G.ttf				$(DESTDIR)/LinLibertine_RBI_G.ttf
	install -D -m 0644 LinLibertine_R_G.ttf					$(DESTDIR)/LinLibertine_R_G.ttf
	install -D -m 0644 LinLibertine_RI_G.ttf				$(DESTDIR)/LinLibertine_RI_G.ttf
	install -D -m 0644 LinLibertine_RZ_G.ttf				$(DESTDIR)/LinLibertine_RZ_G.ttf
	install -D -m 0644 LinLibertine_RZI_G.ttf				$(DESTDIR)/LinLibertine_RZI_G.ttf
	install -D -m 0644 lucon.ttf					$(DESTDIR)/lucon.ttf
	install -D -m 0644 lvnmbd.ttf					$(DESTDIR)/lvnmbd.ttf
	install -D -m 0644 lvnm.ttf						$(DESTDIR)/lvnm.ttf
	install -D -m 0644 majallab.ttf					$(DESTDIR)/majallab.ttf
	install -D -m 0644 majalla.ttf					$(DESTDIR)/majalla.ttf
	install -D -m 0644 malgunbd.ttf					$(DESTDIR)/malgunbd.ttf
	install -D -m 0644 malgunsl.ttf					$(DESTDIR)/malgunsl.ttf
	install -D -m 0644 malgun.ttf					$(DESTDIR)/malgun.ttf
	install -D -m 0644 mangalb.ttf					$(DESTDIR)/mangalb.ttf
	install -D -m 0644 mangal.ttf					$(DESTDIR)/mangal.ttf
	install -D -m 0644 meiryob.ttc					$(DESTDIR)/meiryob.ttc
	install -D -m 0644 meiryo.ttc					$(DESTDIR)/meiryo.ttc
	install -D -m 0644 micross.ttf					$(DESTDIR)/micross.ttf
	install -D -m 0644 mingliub.ttc					$(DESTDIR)/mingliub.ttc
	install -D -m 0644 mingliu.ttc					$(DESTDIR)/mingliu.ttc
	install -D -m 0644 mmrtextb.ttf					$(DESTDIR)/mmrtextb.ttf
	install -D -m 0644 mmrtext.ttf					$(DESTDIR)/mmrtext.ttf
	install -D -m 0644 monbaiti.ttf					$(DESTDIR)/monbaiti.ttf
	install -D -m 0644 moolbor.ttf					$(DESTDIR)/moolbor.ttf
	install -D -m 0644 mriamc.ttf					$(DESTDIR)/mriamc.ttf
	install -D -m 0644 mriam.ttf					$(DESTDIR)/mriam.ttf
	install -D -m 0644 msgothic.ttc					$(DESTDIR)/msgothic.ttc
	install -D -m 0644 msjhbd.ttc					$(DESTDIR)/msjhbd.ttc
	install -D -m 0644 msjhbd.ttf					$(DESTDIR)/msjhbd.ttf
	install -D -m 0644 msjhl.ttc					$(DESTDIR)/msjhl.ttc
	install -D -m 0644 msjh.ttc						$(DESTDIR)/msjh.ttc
	install -D -m 0644 msjh.ttf						$(DESTDIR)/msjh.ttf
	install -D -m 0644 msmincho.ttc					$(DESTDIR)/msmincho.ttc
	install -D -m 0644 msuighub.ttf					$(DESTDIR)/msuighub.ttf
	install -D -m 0644 msuighur.ttf					$(DESTDIR)/msuighur.ttf
	install -D -m 0644 msyhbd.ttc					$(DESTDIR)/msyhbd.ttc
	install -D -m 0644 msyhbd.ttf					$(DESTDIR)/msyhbd.ttf
	install -D -m 0644 msyhl.ttc					$(DESTDIR)/msyhl.ttc
	install -D -m 0644 msyh.ttc						$(DESTDIR)/msyh.ttc
	install -D -m 0644 msyh.ttf						$(DESTDIR)/msyh.ttf
	install -D -m 0644 msyi.ttf						$(DESTDIR)/msyi.ttf
	install -D -m 0644 mvboli.ttf					$(DESTDIR)/mvboli.ttf
	install -D -m 0644 NirmalaB.ttf					$(DESTDIR)/NirmalaB.ttf
	install -D -m 0644 NirmalaS.ttf					$(DESTDIR)/NirmalaS.ttf
	install -D -m 0644 Nirmala.ttf					$(DESTDIR)/Nirmala.ttf
	install -D -m 0644 nrkis.ttf					$(DESTDIR)/nrkis.ttf
	install -D -m 0644 ntailub.ttf					$(DESTDIR)/ntailub.ttf
	install -D -m 0644 ntailu.ttf					$(DESTDIR)/ntailu.ttf
	install -D -m 0644 nyala.ttf					$(DESTDIR)/nyala.ttf
	install -D -m 0644 OpenSans-BoldItalic.ttf		$(DESTDIR)/OpenSans-BoldItalic.ttf
	install -D -m 0644 OpenSans-Bold.ttf			$(DESTDIR)/OpenSans-Bold.ttf
	install -D -m 0644 OpenSans-Italic.ttf			$(DESTDIR)/OpenSans-Italic.ttf
	install -D -m 0644 OpenSans-Regular.ttf			$(DESTDIR)/OpenSans-Regular.ttf
	install -D -m 0644 opens___.ttf					$(DESTDIR)/opens___.ttf
	install -D -m 0644 palabi.ttf					$(DESTDIR)/palabi.ttf
	install -D -m 0644 palab.ttf					$(DESTDIR)/palab.ttf
	install -D -m 0644 palai.ttf					$(DESTDIR)/palai.ttf
	install -D -m 0644 pala.ttf						$(DESTDIR)/pala.ttf
	install -D -m 0644 phagspab.ttf					$(DESTDIR)/phagspab.ttf
	install -D -m 0644 phagspa.ttf					$(DESTDIR)/phagspa.ttf
	install -D -m 0644 plantc.ttf					$(DESTDIR)/plantc.ttf
	install -D -m 0644 PT_Serif-Web-BoldItalic.ttf	$(DESTDIR)/PT_Serif-Web-BoldItalic.ttf
	install -D -m 0644 PT_Serif-Web-Bold.ttf		$(DESTDIR)/PT_Serif-Web-Bold.ttf
	install -D -m 0644 PT_Serif-Web-Italic.ttf		$(DESTDIR)/PT_Serif-Web-Italic.ttf
	install -D -m 0644 PT_Serif-Web-Regular.ttf		$(DESTDIR)/PT_Serif-Web-Regular.ttf
	install -D -m 0644 raavib.ttf					$(DESTDIR)/raavib.ttf
	install -D -m 0644 raavi.ttf					$(DESTDIR)/raavi.ttf
	install -D -m 0644 rod.ttf						$(DESTDIR)/rod.ttf
	install -D -m 0644 segmdl2.ttf					$(DESTDIR)/segmdl2.ttf
	install -D -m 0644 segoeprb.ttf					$(DESTDIR)/segoeprb.ttf
	install -D -m 0644 segoepr.ttf					$(DESTDIR)/segoepr.ttf
	install -D -m 0644 segoescb.ttf					$(DESTDIR)/segoescb.ttf
	install -D -m 0644 segoesc.ttf					$(DESTDIR)/segoesc.ttf
	install -D -m 0644 segoeuib.ttf					$(DESTDIR)/segoeuib.ttf
	install -D -m 0644 segoeuii.ttf					$(DESTDIR)/segoeuii.ttf
	install -D -m 0644 segoeuil.ttf					$(DESTDIR)/segoeuil.ttf
	install -D -m 0644 segoeuisl.ttf				$(DESTDIR)/segoeuisl.ttf
	install -D -m 0644 segoeui.ttf					$(DESTDIR)/segoeui.ttf
	install -D -m 0644 segoeuiz.ttf					$(DESTDIR)/segoeuiz.ttf
	install -D -m 0644 seguibli.ttf					$(DESTDIR)/seguibli.ttf
	install -D -m 0644 seguibl.ttf					$(DESTDIR)/seguibl.ttf
	install -D -m 0644 seguiemj.ttf					$(DESTDIR)/seguiemj.ttf
	install -D -m 0644 seguihis.ttf					$(DESTDIR)/seguihis.ttf
	install -D -m 0644 seguili.ttf					$(DESTDIR)/seguili.ttf
	install -D -m 0644 seguisbi.ttf					$(DESTDIR)/seguisbi.ttf
	install -D -m 0644 seguisb.ttf					$(DESTDIR)/seguisb.ttf
	install -D -m 0644 seguisli.ttf					$(DESTDIR)/seguisli.ttf
	install -D -m 0644 seguisym.ttf					$(DESTDIR)/seguisym.ttf
	install -D -m 0644 Shonarb.ttf					$(DESTDIR)/Shonarb.ttf
	install -D -m 0644 Shonar.ttf					$(DESTDIR)/Shonar.ttf
	install -D -m 0644 shrutib.ttf					$(DESTDIR)/shrutib.ttf
	install -D -m 0644 shruti.ttf					$(DESTDIR)/shruti.ttf
	install -D -m 0644 simfang.ttf					$(DESTDIR)/simfang.ttf
	install -D -m 0644 simhei.ttf					$(DESTDIR)/simhei.ttf
	install -D -m 0644 simkai.ttf					$(DESTDIR)/simkai.ttf
	install -D -m 0644 simpbdo.ttf					$(DESTDIR)/simpbdo.ttf
	install -D -m 0644 simpfxo.ttf					$(DESTDIR)/simpfxo.ttf
	install -D -m 0644 simpo.ttf					$(DESTDIR)/simpo.ttf
	install -D -m 0644 simsunb.ttf					$(DESTDIR)/simsunb.ttf
	install -D -m 0644 simsun.ttc					$(DESTDIR)/simsun.ttc
	install -D -m 0644 SitkaB.ttc					$(DESTDIR)/SitkaB.ttc
	install -D -m 0644 SitkaI.ttc					$(DESTDIR)/SitkaI.ttc
	install -D -m 0644 Sitka.ttc					$(DESTDIR)/Sitka.ttc
	install -D -m 0644 SitkaZ.ttc					$(DESTDIR)/SitkaZ.ttc
	install -D -m 0644 SourceCodePro-BlackIt.ttf	$(DESTDIR)/SourceCodePro-BlackIt.ttf
	install -D -m 0644 SourceCodePro-Black.ttf		$(DESTDIR)/SourceCodePro-Black.ttf
	install -D -m 0644 SourceCodePro-BoldIt.ttf		$(DESTDIR)/SourceCodePro-BoldIt.ttf
	install -D -m 0644 SourceCodePro-Bold.ttf				$(DESTDIR)/SourceCodePro-Bold.ttf
	install -D -m 0644 SourceCodePro-ExtraLightIt.ttf		$(DESTDIR)/SourceCodePro-ExtraLightIt.ttf
	install -D -m 0644 SourceCodePro-ExtraLight.ttf			$(DESTDIR)/SourceCodePro-ExtraLight.ttf
	install -D -m 0644 SourceCodePro-It.ttf					$(DESTDIR)/SourceCodePro-It.ttf
	install -D -m 0644 SourceCodePro-LightIt.ttf			$(DESTDIR)/SourceCodePro-LightIt.ttf
	install -D -m 0644 SourceCodePro-Light.ttf				$(DESTDIR)/SourceCodePro-Light.ttf
	install -D -m 0644 SourceCodePro-MediumIt.ttf			$(DESTDIR)/SourceCodePro-MediumIt.ttf
	install -D -m 0644 SourceCodePro-Medium.ttf				$(DESTDIR)/SourceCodePro-Medium.ttf
	install -D -m 0644 SourceCodePro-Regular.ttf			$(DESTDIR)/SourceCodePro-Regular.ttf
	install -D -m 0644 SourceCodePro-SemiboldIt.ttf			$(DESTDIR)/SourceCodePro-SemiboldIt.ttf
	install -D -m 0644 SourceCodePro-Semibold.ttf			$(DESTDIR)/SourceCodePro-Semibold.ttf
	install -D -m 0644 SourceSansPro-BlackIt.ttf			$(DESTDIR)/SourceSansPro-BlackIt.ttf
	install -D -m 0644 SourceSansPro-Black.ttf				$(DESTDIR)/SourceSansPro-Black.ttf
	install -D -m 0644 SourceSansPro-BoldIt.ttf				$(DESTDIR)/SourceSansPro-BoldIt.ttf
	install -D -m 0644 SourceSansPro-Bold.ttf				$(DESTDIR)/SourceSansPro-Bold.ttf
	install -D -m 0644 SourceSansPro-ExtraLightIt.ttf		$(DESTDIR)/SourceSansPro-ExtraLightIt.ttf
	install -D -m 0644 SourceSansPro-ExtraLight.ttf			$(DESTDIR)/SourceSansPro-ExtraLight.ttf
	install -D -m 0644 SourceSansPro-It.ttf					$(DESTDIR)/SourceSansPro-It.ttf
	install -D -m 0644 SourceSansPro-LightIt.ttf			$(DESTDIR)/SourceSansPro-LightIt.ttf
	install -D -m 0644 SourceSansPro-Light.ttf				$(DESTDIR)/SourceSansPro-Light.ttf
	install -D -m 0644 SourceSansPro-Regular.ttf			$(DESTDIR)/SourceSansPro-Regular.ttf
	install -D -m 0644 SourceSansPro-SemiboldIt.ttf			$(DESTDIR)/SourceSansPro-SemiboldIt.ttf
	install -D -m 0644 SourceSansPro-Semibold.ttf			$(DESTDIR)/SourceSansPro-Semibold.ttf
	install -D -m 0644 sylfaen.ttf					$(DESTDIR)/sylfaen.ttf
	install -D -m 0644 symbol.ttf					$(DESTDIR)/symbol.ttf
	install -D -m 0644 tahomabd.ttf					$(DESTDIR)/tahomabd.ttf
	install -D -m 0644 tahoma.ttf					$(DESTDIR)/tahoma.ttf
	install -D -m 0644 taileb.ttf					$(DESTDIR)/taileb.ttf
	install -D -m 0644 taile.ttf					$(DESTDIR)/taile.ttf
	install -D -m 0644 timesbd.ttf					$(DESTDIR)/timesbd.ttf
	install -D -m 0644 timesbi.ttf					$(DESTDIR)/timesbi.ttf
	install -D -m 0644 timesi.ttf					$(DESTDIR)/timesi.ttf
	install -D -m 0644 times.ttf					$(DESTDIR)/times.ttf
	install -D -m 0644 tradbdo.ttf					$(DESTDIR)/tradbdo.ttf
	install -D -m 0644 trado.ttf					$(DESTDIR)/trado.ttf
	install -D -m 0644 trebucbd.ttf					$(DESTDIR)/trebucbd.ttf
	install -D -m 0644 trebucbi.ttf					$(DESTDIR)/trebucbi.ttf
	install -D -m 0644 trebucit.ttf					$(DESTDIR)/trebucit.ttf
	install -D -m 0644 trebuc.ttf					$(DESTDIR)/trebuc.ttf
	install -D -m 0644 tungab.ttf					$(DESTDIR)/tungab.ttf
	install -D -m 0644 tunga.ttf					$(DESTDIR)/tunga.ttf
	install -D -m 0644 upcdbi.ttf					$(DESTDIR)/upcdbi.ttf
	install -D -m 0644 upcdb.ttf					$(DESTDIR)/upcdb.ttf
	install -D -m 0644 upcdi.ttf					$(DESTDIR)/upcdi.ttf
	install -D -m 0644 upcdl.ttf					$(DESTDIR)/upcdl.ttf
	install -D -m 0644 upcebi.ttf					$(DESTDIR)/upcebi.ttf
	install -D -m 0644 upceb.ttf					$(DESTDIR)/upceb.ttf
	install -D -m 0644 upcei.ttf					$(DESTDIR)/upcei.ttf
	install -D -m 0644 upcel.ttf					$(DESTDIR)/upcel.ttf
	install -D -m 0644 upcfbi.ttf					$(DESTDIR)/upcfbi.ttf
	install -D -m 0644 upcfb.ttf					$(DESTDIR)/upcfb.ttf
	install -D -m 0644 upcfi.ttf					$(DESTDIR)/upcfi.ttf
	install -D -m 0644 upcfl.ttf					$(DESTDIR)/upcfl.ttf
	install -D -m 0644 upcibi.ttf					$(DESTDIR)/upcibi.ttf
	install -D -m 0644 upcib.ttf					$(DESTDIR)/upcib.ttf
	install -D -m 0644 upcii.ttf					$(DESTDIR)/upcii.ttf
	install -D -m 0644 upcil.ttf					$(DESTDIR)/upcil.ttf
	install -D -m 0644 upcjbi.ttf					$(DESTDIR)/upcjbi.ttf
	install -D -m 0644 upcjb.ttf					$(DESTDIR)/upcjb.ttf
	install -D -m 0644 upcji.ttf					$(DESTDIR)/upcji.ttf
	install -D -m 0644 upcjl.ttf					$(DESTDIR)/upcjl.ttf
	install -D -m 0644 upckbi.ttf					$(DESTDIR)/upckbi.ttf
	install -D -m 0644 upckb.ttf					$(DESTDIR)/upckb.ttf
	install -D -m 0644 upcki.ttf					$(DESTDIR)/upcki.ttf
	install -D -m 0644 upckl.ttf					$(DESTDIR)/upckl.ttf
	install -D -m 0644 upclbi.ttf					$(DESTDIR)/upclbi.ttf
	install -D -m 0644 upclb.ttf					$(DESTDIR)/upclb.ttf
	install -D -m 0644 upcli.ttf					$(DESTDIR)/upcli.ttf
	install -D -m 0644 upcll.ttf					$(DESTDIR)/upcll.ttf
	install -D -m 0644 UrdTypeb.ttf					$(DESTDIR)/UrdTypeb.ttf
	install -D -m 0644 UrdType.ttf					$(DESTDIR)/UrdType.ttf
	install -D -m 0644 utsaahbi.ttf					$(DESTDIR)/utsaahbi.ttf
	install -D -m 0644 utsaahb.ttf					$(DESTDIR)/utsaahb.ttf
	install -D -m 0644 utsaahi.ttf					$(DESTDIR)/utsaahi.ttf
	install -D -m 0644 utsaah.ttf					$(DESTDIR)/utsaah.ttf
	install -D -m 0644 Vanib.ttf					$(DESTDIR)/Vanib.ttf
	install -D -m 0644 Vani.ttf						$(DESTDIR)/Vani.ttf
	install -D -m 0644 verdanab.ttf					$(DESTDIR)/verdanab.ttf
	install -D -m 0644 verdanai.ttf					$(DESTDIR)/verdanai.ttf
	install -D -m 0644 verdana.ttf					$(DESTDIR)/verdana.ttf
	install -D -m 0644 verdanaz.ttf					$(DESTDIR)/verdanaz.ttf
	install -D -m 0644 vijayab.ttf					$(DESTDIR)/vijayab.ttf
	install -D -m 0644 vijaya.ttf					$(DESTDIR)/vijaya.ttf
	install -D -m 0644 vrindab.ttf					$(DESTDIR)/vrindab.ttf
	install -D -m 0644 vrinda.ttf					$(DESTDIR)/vrinda.ttf
	install -D -m 0644 WinSoftPro-BItal.otf			$(DESTDIR)/WinSoftPro-BItal.otf
	install -D -m 0644 WinSoftPro-Bold.otf			$(DESTDIR)/WinSoftPro-Bold.otf
	install -D -m 0644 WinSoftPro-Med.otf			$(DESTDIR)/WinSoftPro-Med.otf
	install -D -m 0644 WinSoftPro-MItal.otf			$(DESTDIR)/WinSoftPro-MItal.otf
	install -D -m 0644 YuGothB.ttc					$(DESTDIR)/YuGothB.ttc
	install -D -m 0644 yugothib.ttf					$(DESTDIR)/yugothib.ttf
	install -D -m 0644 yugothic.ttf					$(DESTDIR)/yugothic.ttf
	install -D -m 0644 yugothil.ttf					$(DESTDIR)/yugothil.ttf
	install -D -m 0644 YuGothL.ttc					$(DESTDIR)/YuGothL.ttc
	install -D -m 0644 YuGothM.ttc					$(DESTDIR)/YuGothM.ttc
	install -D -m 0644 YuGothR.ttc					$(DESTDIR)/YuGothR.ttc
	install -D -m 0644 yumindb.ttf					$(DESTDIR)/yumindb.ttf
	install -D -m 0644 yuminl.ttf					$(DESTDIR)/yuminl.ttf
	install -D -m 0644 yumin.ttf					$(DESTDIR)/yumin.ttf


.PHONY: all clean install
