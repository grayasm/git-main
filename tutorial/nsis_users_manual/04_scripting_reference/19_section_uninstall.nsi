# Uninstall Section
; A special section "Uninstall" must be created to generate the uninstaller.
; This section should remove all files, registry keys etc etc that were
; installed by the installer from the system.

Name    "19_section_uninstall"
OutFile "19_section_uninstall.exe"

InstallDir "$PROGRAMFILES\myapp"

Page directory
Page instfiles
UninstPage instfiles

Section
    SetOutPath "$INSTDIR"
    CreateShortCut "$SMSTARTUP\Uninstall this app.lnk" "$INSTDIR\uninstall.exe"
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    Delete "$SMSTARTUP\Uninstall this app.lnk"
    Delete "$INSTDIR\uninstall.exe"
    RMDir "$INSTDIR"
SectionEnd
