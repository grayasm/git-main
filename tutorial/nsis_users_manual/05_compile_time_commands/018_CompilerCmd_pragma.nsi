; !pragma warning <enable|disable|default|error|warning> <code|all>
; !pragma warning <push|pop>
;
; The pragma commands allows you to change compiler features and behavior.


Name    "018_CompilerCmd_pragma"
!pragma warning disable 9000 ; Disable warning about using "Setup.exe" as the name
OutFile "Setup.exe"

InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles
UninstPage instfiles

Section
    SetOutPath "$INSTDIR"
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    RMDir /R "$INSTDIR"
SectionEnd