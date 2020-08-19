# ComponentText [text [subtext] [subtext2]]
;
; Used to change the default text on the component page.
; text:     Text above the controls, to the right of the installation icon.
; subtext:  Text next to the installation type selection.
; subtext2: Text to the left of the components list and below the installation type.
;
; Accepts variables. If variables are used, they must be initialized before the
; components page is created.

InstallDir "$PROGRAMFILES64\MyApp"

ComponentText   "Text above the controls, to the right of the installation icon." \
                "Text next to the installation type selection" \
                "Text to the left of the components list and below the installation type."

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