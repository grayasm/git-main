; Abort [user_message]
;
; Cancels the install, stops execution of script, and displays user_message
; in the status display. 
; Note: you can use this from Callback functions to do special things.
; Page callbacks also uses Abort for special purposes.


InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    
    Abort "Can't install 148_Instruction_Abort.nsi"
    File 148_Instruction_Abort.nsi
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd