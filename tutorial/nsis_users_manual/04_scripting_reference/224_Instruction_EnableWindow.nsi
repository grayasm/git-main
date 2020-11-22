; EnableWindow  hwnd  state(1|0)
;
; Enables or disables mouse and keyboard input to the specified window or control.
; Possible states are 0 (disabled) or 1 (enabled).


Section
    MessageBox MB_OK "Disable dialog item 1 for 5 seconds!"
    GetDlgItem $0 $HWNDPARENT 1
    EnableWindow $0 0
    Sleep 5000
    EnableWindow $0 1
SectionEnd