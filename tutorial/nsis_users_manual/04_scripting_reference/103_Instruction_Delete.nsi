; Delete [/REBOOTOK] file
;
; Delete file (which can be a file or wildcard, but should be specified with
; a full path) from the target system.
; If /REBOOTOK is specified and the file cannot be deleted then the file
; is deleted when the system reboots -- the reboot flag will be set.

InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles
UninstPage instfiles

Section
    SetOutPath "$INSTDIR"
    CreateShortCut "$SMSTARTUP\Uninstall this app.lnk" "$INSTDIR\uninstall.exe"
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    Delete "$SMSTARTUP\Uninstall this app.lnk"
    Delete "$INSTDIR\uninstall.exe"
    RMDir "$INSTDIR"
SectionEnd
