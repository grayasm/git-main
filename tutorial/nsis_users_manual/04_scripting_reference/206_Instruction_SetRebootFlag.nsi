; SetRebootFlag  true | false
;
; Sets the reboot flag to either true or false.
; The flag's value can be read using IfRebootFlag.

Section
    SetRebootFlag true
    IfRebootFlag 0 +2
        MessageBox MB_OK "this message box will always show"
        
    SetRebootFlag false
SectionEnd