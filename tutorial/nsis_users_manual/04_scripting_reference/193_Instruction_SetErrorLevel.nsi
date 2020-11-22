; SetErrorLevel  error_level
;
; Sets the error level of the installer or uninstaller to error_level. 
; See Error Levels for more information.


Section
    IfRebootFlag 0 +2
        SetErrorLevel 4
SectionEnd