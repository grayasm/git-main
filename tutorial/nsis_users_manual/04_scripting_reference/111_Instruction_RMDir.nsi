; RMDir [/r] [/REBOOTOK] directory_name
;
; Remove the specified directory (fully qualified path with no wildcards).
; Without /r, the directory will only be removed if it is completely empty.
; If /r is specified the directory will be removed recursively, so all
; directories and files in the specified directory will be removed.
; If /REBOOTOK is specified, any file or directory which could not be removed
; during the process will be removed on reboot.
; If any file or directory will be removed on a reboot, the reboot flag will be set.
; The error flag is set if any file or directory cannot be removed.

InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    ; Delete "$INSTDIR\uninstall.exe"
    ; or better remove it recursively
    RMDir /r $INSTDIR
SectionEnd
