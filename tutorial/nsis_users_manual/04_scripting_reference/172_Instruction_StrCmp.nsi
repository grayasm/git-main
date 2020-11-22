; StrCmp  str1  str2  jump_if_equal  [jump_if_not_equal]
;
; Compares (case insensitively) str1 to str2. 
; If str1 and str2 are equal, Gotos jump_if_equal, otherwise Gotos jump_if_not_equal.

Section
    StrCpy $0 "a string"
    StrCmp $0 "a string" 0 +3
        DetailPrint '$$0 == "a string"'
    Goto +2
        DetailPrint '$$0 != "a string"'
    # do work
SectionEnd