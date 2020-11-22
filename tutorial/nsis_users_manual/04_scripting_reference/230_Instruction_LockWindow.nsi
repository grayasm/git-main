; LockWindow  on | off
;
; LockWindow on prevents the main window from redrawing itself upon changes.
; When LockWindow off is used, all controls that weren't redrawn since 
; LockWindow on will be redrawn. This makes the pages flickering look nicer 
; because now it flickers a group of controls at the same time, instead of 
; one control at a time. 
; The individual control flickering is more noticeable on old computers.

InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    DetailPrint "progress 30%"
    Sleep 1000
    DetailPrint "progress 60%"
    Sleep 1000
    DetailPrint "progress 100%"   
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd

Function .onInit
    LockWindow on
FunctionEnd