; SetAutoClose  true | false
;
; Overrides the default auto window-closing flag, specified for the installer 
; using AutoCloseWindow, and false for the uninstaller.
; Specify
;       'true' to have the install window immediately disappear after the install has completed, or
;       'false' to make it require a manual close.

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
    SetAutoClose true           ; << SetAutoClose
FunctionEnd