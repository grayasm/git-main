; IfRebootFlag  jump_if_set  [jump_if_not_set]
;
; Checks the reboot flag, and jumps to jump_if_set if the reboot flag is set, 
; otherwise jumps to jump_if_not_set. 
; The reboot flag can be set by Delete and Rename, or manually with SetRebootFlag.


Section
    IfRebootFlag 0 +2
        MessageBox MB_OK "This message will not show!"

    SetRebootFlag true

    IfRebootFlag 0 +2
        MessageBox MB_OK "This message will show!"

    SetRebootFlag false
SectionEnd