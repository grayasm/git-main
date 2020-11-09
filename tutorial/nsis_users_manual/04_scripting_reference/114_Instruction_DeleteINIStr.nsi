; DeleteINIStr ini_filename section_name str_name
;
; Deletes the string str_name from section [section_name] from ini_filename.
; If the string could not be removed from the ini file, the error flag is set.
; It does not set the error flag if the string could not be found.


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath  $INSTDIR
    File    113_IniFile.ini
    WriteUninstaller "$INSTDIR\uninstall.exe"
    
    ; We can modify the installed ini file:
    DeleteINIStr $INSTDIR\113_IniFile.ini section1 parameter1
    DeleteINIStr $INSTDIR\113_IniFile.ini section1 parameter2
    DeleteINIStr $INSTDIR\113_IniFile.ini section1 parameter3
    DeleteINIStr $INSTDIR\113_IniFile.ini section1 parameter4    
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd
