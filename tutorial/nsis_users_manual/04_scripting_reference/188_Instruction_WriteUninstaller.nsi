; WriteUninstaller  [Path\]exename.exe
;
; Writes the uninstaller to the filename (and optionally path) specified. 
; Only valid from within an install section or function and requires that 
; you have an uninstall section in your script. 
; You can call this one or more times to write out one or more copies of 
; the uninstaller.

InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd