; GetDLLVersionLocal localfilename  user_var(high dword output)  user_var(low dword output)
;
; This is similar to GetDLLVersion, only it acts on the system building 
; the installer (it actually compiles into two StrCpy commands). 
; Sets the two output variables with the DLL version information of the DLL 
; on the build system. 
; Use !getdllversion if you need to use the values with VIProductVersion.

InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"

    GetDllVersion "$EXEPATH\108_timeout.exe" $R0 $R1
    IntOp $R2 $R0 / 0x00010000
    IntOp $R3 $R0 & 0x0000FFFF
    IntOp $R4 $R1 / 0x00010000
    IntOp $R5 $R1 & 0x0000FFFF
    StrCpy $0 "$R2.$R3.$R4.$R5"
    
    DetailPrint "DllVersionLocal=$0"    
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd
