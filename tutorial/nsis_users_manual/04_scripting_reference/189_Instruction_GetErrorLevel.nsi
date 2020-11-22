; GetErrorLevel  user_var(error level output)
;
; Returns the last error level set by SetErrorLevel or -1 if it has never been set.

Section
    GetErrorLevel $0
    IntOp $0 $0 + 1
    SetErrorLevel $0
SectionEnd