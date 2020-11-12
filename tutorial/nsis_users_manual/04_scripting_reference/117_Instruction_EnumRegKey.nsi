; EnumRegKey user_var(output) root_key subkey index
;
; Set user variable $x with the name of the 'index'th registry key in root_key\Subkey.
; Valid values for root_key are listed under WriteRegStr. 
; Returns an empty string if there are no more keys, and returns an empty string 
; and sets the error flag if there is an error.

Section
    SetRegView 64
    WriteRegStr HKLM "Software\MyCompany\MyApp\Settings" "Name" "Constanta"
    WriteRegStr HKLM "Software\MyCompany\MyApp\Defaults" "Name" "Constanta"
    
    StrCpy $0 0
loop:
    EnumRegKey $1 HKLM "Software\MyCompany\MyApp" $0
    StrCmp $1 "" done
    IntOp $0 $0 + 1
    MessageBox MB_YESNO|MB_ICONQUESTION "$1$\n$\nMore?" IDYES loop
done:

    ; Clean up
    DeleteRegKey HKLM "Software\MyCompany\MyApp"
SectionEnd
