# LicenseBkColor color | /gray | /windows
;
; Sets the background color of the license data. Color is specified using the
; form RRGGBB (in hexadecimal as in HTML only minus the leading #)
; Default is /gray
; You can also use the Windows OS defined color by using /windows

LicenseBkColor  00FF00
LicenseData     011_license.txt

Page license
Page instfiles

Section ""
    DetailPrint "Installing ..."
SectionEnd