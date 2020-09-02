# un.onRebootFailed (uninstall callback)
;
; This callback is called if Reboot fails.
; WriteUninstaller, plug-ins, File and WriteRegBin should be not used in this callback.

InstallDir "$PROGRAMFILES64\MyApp"

Page license
Page directory
Page instfiles


Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    delete "$INSTDIR\uninstall.exe"
    rmDir $INSTDIR
    MessageBox MB_YESNO|MB_ICONQUESTION "Do you wish to reboot the system?" IDNO +2
    Reboot
    ; Reboots the computer.
    ; Be careful with this one. If it fails .onRebootFailed is called.
    ; In any case, this instruction never returns, just like Quit.
SectionEnd


Function un.onRebootFailed
    MessageBox MB_OK|MB_ICONSTOP "Reboot failed. Please reboot manually." /SD IDOK
FunctionEnd