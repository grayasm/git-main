; ReadRegDWORD user_var(output) root_key sub_key name
;
; Reads a 32-bit DWORD from the registry into the user variable $x. 
; Valid values for root_key are listed under WriteRegStr. 
; The error flag will be set and $x will be set to an empty string 
; ("" which is interpreted as 0 in math operations) if the DWORD is not present.
; If the value is present, but is not a DWORD, it will be read as a string 
; and the error flag will be set.


Section
    SetRegView 64
    WriteRegDWORD HKLM "Software\MyCompany\MyApp" "DWORD Entry"  0xFF10 ;65296
    
    ReadRegDWORD $0 HKLM "Software\MyCompany\MyApp" "DWORD Entry"
    
    DetailPrint "HKLM Software\MyCompany\MyApp 'DWORD Entry'=$0"

    ; Clean up
    DeleteRegKey HKLM "Software\MyCompany\MyApp"
SectionEnd
