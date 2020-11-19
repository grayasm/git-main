; GetFileTime filename  user_var(high dword output)  user_var(low dword output)
;
; Gets the last write time of "filename". Sets the user output variables
; with the high and low dwords of the FILETIME timestamp on success.
; On failure the outputs are empty and the error flag is set.

; QWORD = 8x8 = 64 bits = 0xffff ffff ffff ffff
; DWORD = 8x4 = 32 bits = 0xffff ffff
; WORD  = 8x2 = 16 bits = 0xffff
; BYTE  = 8x1 =  8 bits = 0xff

; NSIS 32 bit build.

InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    File 108_timeout.exe
    WriteUninstaller "$INSTDIR\uninstall.exe"

; Ex: https://nsis.sourceforge.io/Convert_GetFileTime_results_to_day/month/year    
    GetFileTime "$INSTDIR\108_timeout.exe" $1 $0
    System::Int64Op $1 * 0x100000000
    Pop $1
    System::Int64Op $1 + $0
    Pop $0
    System::Call "*(&i2, &i2, &i2, &i2, &i2, &i2, &i2, &i2) i .r1"
    System::Call "Kernel32::FileTimeToSystemTime(*l r0, i r1)"
    System::Call "Kernel32::GetDateFormatA(i 0, i 0, i r1, t 'dd/MM/yy', t .r0, i ${NSIS_MAX_STRLEN})"
    DetailPrint $0 # print results
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd
