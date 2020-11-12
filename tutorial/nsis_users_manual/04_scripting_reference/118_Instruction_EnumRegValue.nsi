; EnumRegValue user_var(output) root_key subkey index
;
; Set user variable $x with the name of the 'index'th registry value in root_key\Subkey.
; Valid values for root_key are listed under WriteRegStr. 
; Returns an empty string and sets the error flag if there are no more values 
; or if there is an error.


Section
    SetRegView 64
    WriteRegStr HKLM "Software\MyCompany\MyApp" "Name"    "MyApp"
    WriteRegStr HKLM "Software\MyCompany\MyApp" "Version" "1.0.a+3"
    
    StrCpy $0 0
loop:
    ClearErrors
    EnumRegValue $1 HKLM "Software\MyCompany\MyApp" $0
    IfErrors done
    IntOp $0 $0 + 1
    ReadRegStr $2 HKLM "Software\MyCompany\MyApp" $1
    MessageBox MB_YESNO|MB_ICONQUESTION "$1 = $2$\n$\nMore?" IDYES loop
done:

    ; Clean up
    DeleteRegKey HKLM "Software\MyCompany\MyApp"
SectionEnd
