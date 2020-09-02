# BGGradient [off|(topc botc [textcolor|notext])]
;
; Specifies whether or not to use a gradient background window for entire DESKTOP.
; If 'off' the installer/uninstaller will not show a background window for DESKTOP.
; If no parameters are specified, the default black to blue colors will be used.
; topc botc are specified using RRGGBB (e.g CC00CC)
; "textcolor" or "notext" specify whether to display a text (top-left) or not.


Name "Testing BGGradient"
InstallDir "$PROGRAMFILES64\Testing BGGradient"

BGGradient "0x4037da" "0xd5633b" textcolor
BGFont "Arial" 34 /ITALIC

Page license
Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

; The gradient will be displayed for uninstall.exe also.
Section Uninstall
    delete "$INSTDIR\uninstall.exe"
    rmDir $INSTDIR
SectionEnd
