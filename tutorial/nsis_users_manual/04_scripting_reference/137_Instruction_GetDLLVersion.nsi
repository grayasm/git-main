; GetDLLVersion filename user_var(high dword output) user_var(low dword output)
;
; Gets the version information from the DLL or executable.
; Sets the user output variables with the high and low dwords of version 
; information on success; on failure the outputs are empty and the error 
; flag is set.


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    File 108_timeout.exe
    WriteUninstaller "$INSTDIR\uninstall.exe"

    GetDllVersion "$INSTDIR\108_timeout.exe" $R0 $R1
    IntOp $R2 $R0 / 0x00010000
    IntOp $R3 $R0 & 0x0000FFFF
    IntOp $R4 $R1 / 0x00010000
    IntOp $R5 $R1 & 0x0000FFFF
    StrCpy $0 "$R2.$R3.$R4.$R5"
    
    DetailPrint "DllVersion=$0"    
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd
