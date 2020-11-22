; Reboot
;
; Reboots the computer. 
; Be careful with this one. 
; If it fails, .onRebootFailed is called. 
; In any case, this instruction never returns, just like Quit.

Section
    MessageBox MB_YESNO|MB_ICONQUESTION "Do you wish to reboot the system?" IDNO +2
        Reboot
SectionEnd