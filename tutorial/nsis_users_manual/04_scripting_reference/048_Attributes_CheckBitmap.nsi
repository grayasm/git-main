# CheckBitmap bitmap.bmp
;
; Specifies the bitmap with the checkbox images used in the component-selection
; page treeview. This bitmap should have a size of 96x16 pixels, no more than
; 8bpp (256 colors) and contain six 16x16 images for the different states
; in order: selection mask, not checked, checked, greyed out, unchecked,
; and read-only. Use magenta as mask color.

CheckBitmap "${NSISDIR}\Contrib\Graphics\Checks\simple-round2.bmp"


InstallDir "$PROGRAMFILES64\MyApp"

Page license
Page directory
Page components
Page instfiles

Section Programs
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Manual
SectionEnd

Section Uninstall
    delete "$INSTDIR\uninstall.exe"
    rmDir $INSTDIR
SectionEnd