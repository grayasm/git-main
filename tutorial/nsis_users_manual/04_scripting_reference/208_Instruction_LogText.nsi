; LogText  text
;
; If installer logging is enabled, inserts text "text" into the log file.


InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    LogSet on
    WriteUninstaller $INSTDIR\uninstall.exe
    
    IfFileExists $WINDIR\notepad.exe 0 +2
        LogText "$$WINDIR\notepad.exe exists"
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd

; Error: LogText specified, NSIS_CONFIG_LOG not defined.