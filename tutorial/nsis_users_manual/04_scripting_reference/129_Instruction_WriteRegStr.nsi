; WriteRegStr root_key  subkey  key_name  value
;
; Write a string to the registry. See WriteRegExpandStr for more details.

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
