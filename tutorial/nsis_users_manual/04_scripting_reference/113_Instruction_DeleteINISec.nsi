; DeleteINISec ini_filename section_name
;
; Deletes the entire section [section_name] from ini_filename.
; If the section could not be removed from the ini file, the error flag is set.
; It does not set the error flag if the section could not be found.


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath  $INSTDIR
    File    113_IniFile.ini
    WriteUninstaller "$INSTDIR\uninstall.exe"
    
    ; We can modify the installed ini file:
    DeleteINISec $INSTDIR\113_IniFile.ini section1
    WriteINIStr  $INSTDIR\113_IniFile.ini section2  parameter20 "Added by installer, do not change!"
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd
