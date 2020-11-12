; WriteRegDWORD root_key  subkey  key_name  value
;
; This command writes a DWORD (32-bit integer) to the registry (a user variable 
; can be specified). Valid values for root_key are listed under WriteRegStr.
; The error flag is set if the dword could not be written to the registry.
; If the registry key doesn't exist it will be created.


Section
    SetRegView 64
    WriteRegDWORD HKLM "Software\MyCompany\MyApp" "DWORD Entry"  0xFF10 ;65296
    
    ReadRegDWORD $0 HKLM "Software\MyCompany\MyApp" "DWORD Entry"
    
    DetailPrint "HKLM Software\MyCompany\MyApp 'DWORD Entry'=$0"

    ; Clean up
    DeleteRegKey HKLM "Software\MyCompany\MyApp"
SectionEnd
