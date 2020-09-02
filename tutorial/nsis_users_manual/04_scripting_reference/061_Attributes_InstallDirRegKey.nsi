# InstallDirRegKey root_key subkey key_name
;
; This attribute tells the installer to check a string in the registry and use it
; as the install dir if that string is valid. If this attribute is present
; it will override the InstallDir attribute if the registry key is valid, otherwise
; it will fall back to the InstallDir value.
; If the registry key is "C:\Program Files\Foo\app.exe" it will remove the "app.exe"
; and keep only the directory location.


; On 2nd run the registry key will be valid
InstallDir "$DESKTOP\InstallDirNotFromRegistry"
InstallDirRegKey HKLM  "SOFTWARE\MyTestingApp" "InstallDir"

Page directory
Page instfiles

Section ""
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
    WriteRegStr HKLM "SOFTWARE\MyTestingApp" "InstallDir" "$DESKTOP\InstallDirFromRegistry"
SectionEnd

Section Uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir /r /REBOOTOK $INSTDIR
    DeleteRegKey HKLM "SOFTWARE\MyTestingApp"
SectionEnd
