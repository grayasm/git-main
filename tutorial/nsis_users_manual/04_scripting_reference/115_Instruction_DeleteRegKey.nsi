; DeleteRegKey [/ifempty | /ifnosubkeys | /ifnovalues] root_key subkey
;
; Deletes a registry key. If /ifempty is specified, the registry key will only 
; be deleted if it has no subkeys and no values (otherwise, the whole registry
; tree will be removed).
; Valid values for root_key are listed under WriteRegStr.
; The error flag is set if the key could not be removed from the registry
; (or if it didn't exist to begin with).


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath  $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
    
    SetRegView 64
    WriteRegStr HKLM "Software\MyCompany\MyApp" "A String Value" "dead beef"
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
    
    SetRegView 64
    DeleteRegKey HKLM "Software\MyCompany\MyApp"
    ; HKLM\Software\MyCompany   however will not be removed!
SectionEnd
