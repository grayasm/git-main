# InstallDir definstdir
;
; Set the default install directory. See 02_variables.nsi constants for
; variables that can be used to make this string (e.g. $PROGRAMFILES64, etc)
; The installation directory $INSTDIR is modifiable using StrCpy,ReadRegStr,ReadINIStr,etc.


; Exaple using ReadINIStr to change $INSTDIR
InstallDir "$DESKTOP\DirectoryNotSet"

Function .onInit
    ReadINIStr $0  "$EXEDIR\060_installdir.ini"  "Settings" "on_desktop_dir"
    StrCpy $INSTDIR "$DESKTOP\$0"
FunctionEnd


Page directory
Page instfiles

Section ""
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninst.exe
SectionEnd

Section Uninstall
    Delete $INSTDIR\uninst.exe
    RMDir /r /REBOOTOK $INSTDIR
SectionEnd
