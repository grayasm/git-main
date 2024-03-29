; FileWriteByte  handle  string
;
; Writes the integer interpretation of 'string' to a file opened with FileOpen.
; The error flag is set if an error occurs while writing. 
; The following code writes a "Carriage Return / Line Feed" pair to the file.

InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    
    FileOpen $0  $INSTDIR\temp.txt  w
    IfErrors done
    FileWrite $0  "#1 first line"
    
    ; Carriage Return (13) + Line Feed (10)
    FileWriteByte $0 "13"
    FileWriteByte $0 "10"

    FileWrite $0  "#2 last line"
    FileClose $0    
done:
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd