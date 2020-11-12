; WriteRegBin root_key  subkey  key_name  valuedata
;
; This command writes a block of binary data to the registry. 
; Valid values for root_key are listed under WriteRegStr. 
; Valuedata is in hexadecimal (e.g. DEADBEEF01223211151). 
; The error flag is set if the binary data could not be written to the registry.
; If the registry key doesn't exist it will be created.

Section
    SetRegView 64
    WriteRegStr HKLM "Software\MyCompany\MyApp" "Name" "MyApplication"
    WriteRegStr HKLM "Software\MyCompany\MyApp" "Copyright" "(c) 2020"

    WriteRegBin HKLM "Software\MyCompany\MyApp" "Binary Value" DEADBEEF01223211151

    ; You can't read binary data from the registry using NSIS because NSIS
    ; can only handle the string data type. You can always write an extension
    ; DLL (plug-in) to do this. You can find an example in Contrib\ExDLL.
    
    ReadRegStr $0 HKLM "Software\MyCompany\MyApp" "Binary Value"
    StrCmp $0 "" 0 +2 ; StrCmp str1 str2 jmp_eq  jmp_neq
    MessageBox MB_OK "Cannot read HKLM\Software\MyCompany\MyApp 'Binary Value'"

SectionEnd