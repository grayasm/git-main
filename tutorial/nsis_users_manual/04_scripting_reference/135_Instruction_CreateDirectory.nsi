; CreateDirectory path_to_create
;
; Creates (recursively if necessary) the specified directory. 
; The error flag is set if the directory couldn't be created.

InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    ; If directory existed do a backup of existing files
    CreateDirectory $INSTDIR\backup
    CopyFiles $INSTDIR\* $INSTDIR\backup
    ; Continue 
    WriteUninstaller "$INSTDIR\uninstall.exe"   
    
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd
