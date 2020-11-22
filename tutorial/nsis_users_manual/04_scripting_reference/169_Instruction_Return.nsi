; Return 
;
; Returns from a function or section.

Function func
    StrCmp $0 "return now" 0 +2
        Return
    # do stuff
FunctionEnd

Section
    Call func
    ;"Return" will return here
SectionEnd