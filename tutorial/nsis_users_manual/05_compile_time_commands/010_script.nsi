; This script is called by 010_CompilerCmd_makensis.nsi via
; !makensis 010_script.nsi


InstallDir "$DOCUMENTS\MyApplication"

Page directory
Page instfiles

Section ""
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
SectionEnd

Section Uninstall
    Delete $INSTDIR\uninstall.exe
    RMDir /r /REBOOTOK $INSTDIR
SectionEnd
