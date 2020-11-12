; DeleteRegValue root_key subkey key_name
;
; Deletes a registry value. Valid values for root_key are listed under WriteRegStr.
; The error flag is set if the value could not be removed from the registry 
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
    DeleteRegValue HKLM "Software\MyCompany\MyApp" "A String Value"
SectionEnd
