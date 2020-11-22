; SetErrors
;
; Sets the error flag.

Section
    SetErrors
    IfErrors 0 +2
        MessageBox MB_OK "this message box will always show"
SectionEnd