; IfFileExists  file_to_check_for  jump_if_present  [jump_otherwise]
;
; Checks for existence of file(s) file_to_check_for (which can be a wildcard, 
; or a directory), and Gotos jump_if_present if the file exists, otherwise 
; Gotos jump_otherwise. If you want to check to see if a file is a directory, 
; use IfFileExists DIRECTORY\*.*


InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    
    IfFileExists $INSTDIR\*.* 0 +2
        MessageBox MB_OK "Directory exists: $INSTDIR"
        
    IfFileExists $INSTDIR\uninstall.exe 0 +2
        MessageBox MB_OK "File exists: $INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd