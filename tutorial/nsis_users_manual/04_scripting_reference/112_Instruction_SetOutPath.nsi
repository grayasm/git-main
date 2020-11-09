; SetOutPath outpath
;
; Sets the output path ($OUTDIR) and creates it (recursively if necessary),
; if it does not exist. Must be a full pathname, usually is just $INSTDIR
; (you can specify $INSTDIR with a single "-" if you are lazy).


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath "$INSTDIR\topdir\subdir"
    File 112_Instruction_SetOutPath.nsi
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd
