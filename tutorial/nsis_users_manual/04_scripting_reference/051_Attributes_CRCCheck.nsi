# CRCCheck on|off|force
;
; Specifies whether or not the installer will perform CRC on itself before
; allowing an install. Note that if the user uses /NCRC on the command line
; when executing the installer, and you didn't speficy 'force', the CRC will
; occur, and the user will be allowed to install a (potentially) corrupted
; installer.

CRCCheck on


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