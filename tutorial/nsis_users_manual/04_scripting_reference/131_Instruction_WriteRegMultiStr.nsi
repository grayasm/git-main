; WriteRegMultiStr /REGEDIT5  root_key  subkey  key_name  value
;
; Writes a multi-string value. The /REGEDIT5 switch must be used and specifies
; that the data is in the hex format used by .reg files on Windows 2000 and later.


Section
    SetRegView 64
    WriteRegStr HKLM "Software\MyCompany\MyApp" "Name" "MyApplication"
    WriteRegStr HKLM "Software\MyCompany\MyApp" "Copyright" "(c) 2020"

    WriteRegMultiStr /REGEDIT5 HKLM "Software\MyCompany\MyApp" "Multi Value" 66,00,6f,00,6f,00,00,00,62,00,61,00,72,00,00,00,00,00
    ; Multi Value=
    ; foo
    ; bar
SectionEnd