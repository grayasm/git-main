; GetFileTimeLocal localfilename  user_var(high dword output)  user_var(low dword output)
;
; This is similar to GetFileTime, only it acts on the system building 
; the installer (it actually compiles into two StrCpy commands). 
; Sets the two output variables with the file timestamp of the file 
; on the build system.

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
    WriteUninstaller "$INSTDIR\uninstall.exe"

; Ex: https://nsis.sourceforge.io/Convert_GetFileTime_results_to_day/month/year    
    GetFileTimeLocal "108_timeout.exe" $1 $0
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
