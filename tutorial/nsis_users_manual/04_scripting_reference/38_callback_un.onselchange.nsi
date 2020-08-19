# un.onSelChange (uninstall callback)
;
; Called when the selection changes on the components page.
; Useful for using with SectionSetFlags, SectionGetFlags.
; The section id of the changed section is stored in $0.



InstallDir "$PROGRAMFILES64\MyApp"

Page license
Page components
Page directory
Page instfiles


Section "Install files"         IDX_FL
    SetOutPath $INSTDIR
SectionEnd

Section "Install uninstaller"   IDX_UN
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    delete $INSTDIR\uninstall.exe
    rmDir $INSTDIR
SectionEnd

Function .onSelChange
    SectionGetText $0 $R0
    MessageBox MB_OK|MB_ICONEXCLAMATION ".onSelChange section=$R0"
FunctionEnd


; cannot trigger this, maybe due to missing components page in uninstaller?
Function un.onSelChange
    SectionGetText $0 $R0
    MessageBox MB_OK|MB_ICONEXCLAMATION ".onSelChange section=$R0"
FunctionEnd
