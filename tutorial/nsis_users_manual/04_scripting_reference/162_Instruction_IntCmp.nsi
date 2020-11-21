; IntCmp val1 val2  jump_if_equal  [jump_if_val1_less]  [jump_if_val1_more]
;
; Compares two integers val1 and val2. 
; If val1 and val2 are equal, Gotos jump_if_equal, otherwise
; If val1 < val2, Gotos jump_if_val1_less, otherwise
; If val1 > val2, Gotos jump_if_val1_more.


Section
    StrCpy $0 5
    IntCmp $0 5 is5 lessthan5 morethan5
    is5:
        DetailPrint "$$0 == 5"
        Goto done
    lessthan5:
        DetailPrint "$$0 < 5"
        Goto done
    morethan5:
        DetailPrint "$$0 > 5"
        Goto done
    done:
SectionEnd