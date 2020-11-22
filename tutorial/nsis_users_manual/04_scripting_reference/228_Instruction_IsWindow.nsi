; IsWindow  HWND  jump_if_window  [jump_if_not_window]
;
; If HWND is a window, Gotos jump_if_window, otherwise Gotos jump_if_not_window
; (if specified).


Section
    GetDlgItem $0 $HWNDPARENT 1
    IsWindow $0 0 +3
    MessageBox MB_OK "found a window"
    Goto +2
    MessageBox MB_OK "no window"
SectionEnd