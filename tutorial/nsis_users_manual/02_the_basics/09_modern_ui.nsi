### Modern UI
#   * a popular user interface for NSIS is the Modern User Interface. It has
#       an interface like the wizards of the recent Windows versions.
#   * it is a customized resource file with lots of new interface elements.
# readme: https://nsis.sourceforge.io/Docs/Modern%20UI%202/Readme.html
# sample: https://nsis.sourceforge.io/Examples/Modern%20UI/


!include "MUI2.nsh"

Name "Modern UI Test"
OutFile "09_modern_ui.exe"
Unicode True

InstallDir "$LOCALAPPDATA\Modern UI Test"
InstallDirRegKey HKCU "Software\Modern UI Test" ""
RequestExecutionLevel user

; Interface Settings
!define MUI_ABORTWARNINIG


; Pages
!insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES


; Languages
!insertmacro MUI_LANGUAGE "English"


; Sections
Section "Dummy Section" SecDummy
    SetOutPath "$INSTDIR"
    ; --- add your own files here ---
    
    WriteRegStr HKCU "Software\Modern UI Test" "" $INSTDIR
    WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd


; Descriptions
LangString DESC_SecDummy ${LANG_ENGLISH} "A test section."
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecDummy} ${DESC_SecDummy}
!insertmacro MUI_FUNCTION_DESCRIPTION_END

; Uninstaller section
Section "Uninstall"
    ; --- add your own files here ---
    Delete "$INSTDIR\Uninstall.exe"
    RMDir "$INSTDIR"
    DeleteRegKey /ifempty HKCU "Software\Modern UI Test"
SectionEnd
