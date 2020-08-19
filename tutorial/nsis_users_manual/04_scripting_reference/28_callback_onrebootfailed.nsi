# .onRebootFailed (install callback)
;
; This callback is called if Reboot fails.
; Do not use in this callback WriteUninstaller, plug-ins, File or WriteRegBin.

Function .onRebootFailed
    MessageBox MB_OK|MB_ICONSTOP "Reboot failed. Please reboot manually." /SD IDOK
FunctionEnd


Section
SectionEnd