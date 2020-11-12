; ReadRegStr user_var(output) root_key sub_key name
;
; Reads from the registry into the user variable $x. 
; Valid values for root_key are listed under WriteRegStr. 
; The error flag will be set and $x will be set to an empty string ("") 
; if the string is not present. 
; If the value is present, but is of type REG_DWORD, it will be read and 
; converted to a string and the error flag will be set.


Section
    SetRegView 64
    WriteRegStr HKLM "Software\MyCompany\MyApp" "Name" "MyApplication"
    WriteRegStr HKLM "Software\MyCompany\MyApp" "Copyright" "(c) 2020"
    
    ReadRegStr $0 HKLM "Software\MyCompany\MyApp" "Name"
    ReadRegStr $1 HKLM "Software\MyCompany\MyApp" "Copyright"
    
    DetailPrint "Name=$0"
    DetailPrint "Copyright=$1"

    ; Clean up
    DeleteRegKey HKLM "Software\MyCompany\MyApp"
SectionEnd
