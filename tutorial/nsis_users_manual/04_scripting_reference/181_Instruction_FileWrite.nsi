; FileWrite  handle  string
;
; Writes an ANSI string to a file opened with FileOpen. 
; If an error occurs writing, the error flag will be set.
; If you are building a Unicode installer, the function converts the string
; to ANSI/MBCS. The system default ANSI codepage (ACP) is used during the conversion.


InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    
    FileOpen $0  $INSTDIR\temp.txt  w
    IfErrors done
    FileWrite $0  "#1 first line$\n"
    FileWrite $0  "#2 last line$\n"
    FileClose $0    
done:
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd