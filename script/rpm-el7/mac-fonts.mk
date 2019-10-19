all:
	echo "Done"

clean:
	echo "Done"

# Copy this as Makefile inside mac-fonts.tar.gz

# make DESTDIR=/opt/mac-fonts install
install:
	install -D -m 0644  HelveticaNeue/Helvetica-Neu-Bold.ttf			$(DESTDIR)/HelveticaNeue/Helvetica-Neu-Bold.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeueBd.ttf				$(DESTDIR)/HelveticaNeue/HelveticaNeueBd.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeue-BlackCond.ttf		$(DESTDIR)/HelveticaNeue/HelveticaNeue-BlackCond.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeueHv.ttf				$(DESTDIR)/HelveticaNeue/HelveticaNeueHv.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeueIt.ttf				$(DESTDIR)/HelveticaNeue/HelveticaNeueIt.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeue-Light.ttf			$(DESTDIR)/HelveticaNeue/HelveticaNeue-Light.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeueLt.ttf				$(DESTDIR)/HelveticaNeue/HelveticaNeueLt.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeue-Medium.ttf			$(DESTDIR)/HelveticaNeue/HelveticaNeue-Medium.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeueMed.ttf				$(DESTDIR)/HelveticaNeue/HelveticaNeueMed.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeue-Thin.ttf			$(DESTDIR)/HelveticaNeue/HelveticaNeue-Thin.ttf
	install -D -m 0644  HelveticaNeue/HelveticaNeue.ttf					$(DESTDIR)/HelveticaNeue/HelveticaNeue.ttf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-Black.otf		$(DESTDIR)/SFCompact_otf/SFCompactDisplay-Black.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-Bold.otf			$(DESTDIR)/SFCompact_otf/SFCompactDisplay-Bold.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-Heavy.otf		$(DESTDIR)/SFCompact_otf/SFCompactDisplay-Heavy.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-Light.otf		$(DESTDIR)/SFCompact_otf/SFCompactDisplay-Light.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-Medium.otf		$(DESTDIR)/SFCompact_otf/SFCompactDisplay-Medium.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-Regular.otf		$(DESTDIR)/SFCompact_otf/SFCompactDisplay-Regular.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-Semibold.otf		$(DESTDIR)/SFCompact_otf/SFCompactDisplay-Semibold.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-SemiBold.otf		$(DESTDIR)/SFCompact_otf/SFCompactDisplay-SemiBold.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-Thin.otf			$(DESTDIR)/SFCompact_otf/SFCompactDisplay-Thin.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-Ultralight.otf	$(DESTDIR)/SFCompact_otf/SFCompactDisplay-Ultralight.otf
	install -D -m 0644  SFCompact_otf/SFCompactDisplay-UltraLight.otf	$(DESTDIR)/SFCompact_otf/SFCompactDisplay-UltraLight.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-BoldItalic.otf		$(DESTDIR)/SFCompact_otf/SFCompactText-BoldItalic.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-Bold.otf			$(DESTDIR)/SFCompact_otf/SFCompactText-Bold.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-HeavyItalic.otf		$(DESTDIR)/SFCompact_otf/SFCompactText-HeavyItalic.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-Heavy.otf			$(DESTDIR)/SFCompact_otf/SFCompactText-Heavy.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-LightItalic.otf		$(DESTDIR)/SFCompact_otf/SFCompactText-LightItalic.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-Light.otf			$(DESTDIR)/SFCompact_otf/SFCompactText-Light.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-MediumItalic.otf	$(DESTDIR)/SFCompact_otf/SFCompactText-MediumItalic.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-Medium.otf			$(DESTDIR)/SFCompact_otf/SFCompactText-Medium.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-RegularItalic.otf	$(DESTDIR)/SFCompact_otf/SFCompactText-RegularItalic.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-Regular.otf			$(DESTDIR)/SFCompact_otf/SFCompactText-Regular.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-SemiboldItalic.otf	$(DESTDIR)/SFCompact_otf/SFCompactText-SemiboldItalic.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-SemiBoldItalic.otf	$(DESTDIR)/SFCompact_otf/SFCompactText-SemiBoldItalic.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-Semibold.otf		$(DESTDIR)/SFCompact_otf/SFCompactText-Semibold.otf
	install -D -m 0644  SFCompact_otf/SFCompactText-SemiBold.otf		$(DESTDIR)/SFCompact_otf/SFCompactText-SemiBold.otf
	install -D -m 0644  SFCompact_ttf/SFCompactDisplay-Black.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactDisplay-Black.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactDisplay-Bold.ttf			$(DESTDIR)/SFCompact_ttf/SFCompactDisplay-Bold.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactDisplay-Heavy.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactDisplay-Heavy.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactDisplay-Light.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactDisplay-Light.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactDisplay-Medium.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactDisplay-Medium.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactDisplay-Regular.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactDisplay-Regular.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactDisplay-SemiBold.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactDisplay-SemiBold.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactDisplay-Thin.ttf			$(DESTDIR)/SFCompact_ttf/SFCompactDisplay-Thin.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactDisplay-UltraLight.ttf	$(DESTDIR)/SFCompact_ttf/SFCompactDisplay-UltraLight.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-BoldItalic.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactText-BoldItalic.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-Bold.ttf			$(DESTDIR)/SFCompact_ttf/SFCompactText-Bold.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-HeavyItalic.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactText-HeavyItalic.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-Heavy.ttf			$(DESTDIR)/SFCompact_ttf/SFCompactText-Heavy.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-LightItalic.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactText-LightItalic.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-Light.ttf			$(DESTDIR)/SFCompact_ttf/SFCompactText-Light.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-MediumItalic.ttf	$(DESTDIR)/SFCompact_ttf/SFCompactText-MediumItalic.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-Medium.ttf			$(DESTDIR)/SFCompact_ttf/SFCompactText-Medium.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-RegularItalic.ttf	$(DESTDIR)/SFCompact_ttf/SFCompactText-RegularItalic.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-Regular.ttf			$(DESTDIR)/SFCompact_ttf/SFCompactText-Regular.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-SemiBoldItalic.ttf	$(DESTDIR)/SFCompact_ttf/SFCompactText-SemiBoldItalic.ttf
	install -D -m 0644  SFCompact_ttf/SFCompactText-SemiBold.ttf		$(DESTDIR)/SFCompact_ttf/SFCompactText-SemiBold.ttf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-BlackItalic.otf		$(DESTDIR)/SFPro_otf/SF-Pro-Display-BlackItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-Black.otf				$(DESTDIR)/SFPro_otf/SF-Pro-Display-Black.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-BoldItalic.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Display-BoldItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-Bold.otf				$(DESTDIR)/SFPro_otf/SF-Pro-Display-Bold.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-HeavyItalic.otf		$(DESTDIR)/SFPro_otf/SF-Pro-Display-HeavyItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-Heavy.otf				$(DESTDIR)/SFPro_otf/SF-Pro-Display-Heavy.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-LightItalic.otf		$(DESTDIR)/SFPro_otf/SF-Pro-Display-LightItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-Light.otf				$(DESTDIR)/SFPro_otf/SF-Pro-Display-Light.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-MediumItalic.otf		$(DESTDIR)/SFPro_otf/SF-Pro-Display-MediumItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-Medium.otf				$(DESTDIR)/SFPro_otf/SF-Pro-Display-Medium.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-RegularItalic.otf		$(DESTDIR)/SFPro_otf/SF-Pro-Display-RegularItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-Regular.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Display-Regular.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-SemiboldItalic.otf		$(DESTDIR)/SFPro_otf/SF-Pro-Display-SemiboldItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-Semibold.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Display-Semibold.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-ThinItalic.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Display-ThinItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-Thin.otf				$(DESTDIR)/SFPro_otf/SF-Pro-Display-Thin.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-UltralightItalic.otf	$(DESTDIR)/SFPro_otf/SF-Pro-Display-UltralightItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Display-Ultralight.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Display-Ultralight.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-BoldItalic.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Text-BoldItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-Bold.otf					$(DESTDIR)/SFPro_otf/SF-Pro-Text-Bold.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-HeavyItalic.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Text-HeavyItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-Heavy.otf					$(DESTDIR)/SFPro_otf/SF-Pro-Text-Heavy.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-LightItalic.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Text-LightItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-Light.otf					$(DESTDIR)/SFPro_otf/SF-Pro-Text-Light.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-MediumItalic.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Text-MediumItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-Medium.otf				$(DESTDIR)/SFPro_otf/SF-Pro-Text-Medium.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-RegularItalic.otf			$(DESTDIR)/SFPro_otf/SF-Pro-Text-RegularItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-Regular.otf				$(DESTDIR)/SFPro_otf/SF-Pro-Text-Regular.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-SemiboldItalic.otf		$(DESTDIR)/SFPro_otf/SF-Pro-Text-SemiboldItalic.otf
	install -D -m 0644  SFPro_otf/SF-Pro-Text-Semibold.otf				$(DESTDIR)/SFPro_otf/SF-Pro-Text-Semibold.otf
	install -D -m 0644  SFPro_ttf/SFProDisplay-BlackItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProDisplay-BlackItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-Black.ttf				$(DESTDIR)/SFPro_ttf/SFProDisplay-Black.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-BoldItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProDisplay-BoldItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-Bold.ttf					$(DESTDIR)/SFPro_ttf/SFProDisplay-Bold.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-HeavyItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProDisplay-HeavyItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-Heavy.ttf				$(DESTDIR)/SFPro_ttf/SFProDisplay-Heavy.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-LightItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProDisplay-LightItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-Light.ttf				$(DESTDIR)/SFPro_ttf/SFProDisplay-Light.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-MediumItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProDisplay-MediumItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-Medium.ttf				$(DESTDIR)/SFPro_ttf/SFProDisplay-Medium.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-RegularItalic.ttf		$(DESTDIR)/SFPro_ttf/SFProDisplay-RegularItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-Regular.ttf				$(DESTDIR)/SFPro_ttf/SFProDisplay-Regular.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-SemiboldItalic.ttf		$(DESTDIR)/SFPro_ttf/SFProDisplay-SemiboldItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-Semibold.ttf				$(DESTDIR)/SFPro_ttf/SFProDisplay-Semibold.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-SemiBold.ttf				$(DESTDIR)/SFPro_ttf/SFProDisplay-SemiBold.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-ThinItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProDisplay-ThinItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-Thin.ttf					$(DESTDIR)/SFPro_ttf/SFProDisplay-Thin.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-UltralightItalic.ttf		$(DESTDIR)/SFPro_ttf/SFProDisplay-UltralightItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-Ultralight.ttf			$(DESTDIR)/SFPro_ttf/SFProDisplay-Ultralight.ttf
	install -D -m 0644  SFPro_ttf/SFProDisplay-UltraLight.ttf			$(DESTDIR)/SFPro_ttf/SFProDisplay-UltraLight.ttf
	install -D -m 0644  SFPro_ttf/SFProText-BoldItalic.ttf				$(DESTDIR)/SFPro_ttf/SFProText-BoldItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProText-Bold.ttf					$(DESTDIR)/SFPro_ttf/SFProText-Bold.ttf
	install -D -m 0644  SFPro_ttf/SFProText-HeavyItalic.ttf				$(DESTDIR)/SFPro_ttf/SFProText-HeavyItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProText-Heavy.ttf					$(DESTDIR)/SFPro_ttf/SFProText-Heavy.ttf
	install -D -m 0644  SFPro_ttf/SFProText-LightItalic.ttf				$(DESTDIR)/SFPro_ttf/SFProText-LightItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProText-Light.ttf					$(DESTDIR)/SFPro_ttf/SFProText-Light.ttf
	install -D -m 0644  SFPro_ttf/SFProText-MediumItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProText-MediumItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProText-Medium.ttf					$(DESTDIR)/SFPro_ttf/SFProText-Medium.ttf
	install -D -m 0644  SFPro_ttf/SFProText-RegularItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProText-RegularItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProText-Regular.ttf					$(DESTDIR)/SFPro_ttf/SFProText-Regular.ttf
	install -D -m 0644  SFPro_ttf/SFProText-SemiboldItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProText-SemiboldItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProText-SemiBoldItalic.ttf			$(DESTDIR)/SFPro_ttf/SFProText-SemiBoldItalic.ttf
	install -D -m 0644  SFPro_ttf/SFProText-Semibold.ttf				$(DESTDIR)/SFPro_ttf/SFProText-Semibold.ttf
	install -D -m 0644  SFPro_ttf/SFProText-SemiBold.ttf				$(DESTDIR)/SFPro_ttf/SFProText-SemiBold.ttf


.PHONY: all clean install
