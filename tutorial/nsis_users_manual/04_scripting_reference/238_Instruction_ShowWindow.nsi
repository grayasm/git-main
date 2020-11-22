; ShowWindow  hwnd  show_state
;
; Sets the visibility of a window.
; Possible show_states are the same as the Windows ShowWindow function. 
; SW_* constants are defined in Include\WinMessages.nsh.

!include WinMessages.nsh

Section
    GetDlgItem $0 $HWNDPARENT 1
    
    DetailPrint "Installing 30%"
    Sleep 3000  
    
    ShowWindow $0 ${SW_HIDE}
    DetailPrint "Installing 60%"
    Sleep 3000    
    
    ShowWindow $0 ${SW_SHOW}
    DetailPrint "Installing 100%"
SectionEnd