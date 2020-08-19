# Caption text
;
; When used outside PageEx block, sets teh text of the titlebar of the installer.
; By default it is "$(^Name) Setup" where Name is specified by Name instruction.
; When used inside a PageEx block, sets the subcaption of the current page.
; Accepts variables that must be initialized in .onInit or .onGUIInit
; The same string will be used as text on background gradient.

Caption "MyApp Installer"       ; Installer text  : "MyApp Installer"
Name "MyApp"                    ; Uninstaller text: "MyApp Uninstaller"

InstallDir "$PROGRAMFILES64\MyApp"

BGGradient "0x4037da" "0xd5633b" textcolor
BGFont "Arial" 34 /ITALIC

Page license
Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

; The gradient will also be displayed for uninstall.exe
Section Uninstall
    delete "$INSTDIR\uninstall.exe"
    rmDir $INSTDIR
SectionEnd