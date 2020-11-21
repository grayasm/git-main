; IfSilent  jump_if_silent  [jump_if_not]
;
; Checks the silent flag, and jumps to jump_if_silent if the installer is silent,
; otherwise jumps to jump_if_not. 
; The silent flag can be set by SilentInstall, SilentUninstall, SetSilent and
; by the user passing /S on the command line.

InstallDir $DOCUMENTS\MyApp

Section
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    
    IfSilent 0 +2
        MessageBox MB_OK "The installer is silent."

SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd

Function .onInit
    SetSilent silent
FunctionEnd