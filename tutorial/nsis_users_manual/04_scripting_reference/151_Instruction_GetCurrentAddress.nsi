; GetCurrentAddress  user_var(output)
;
; Gets the address of the current instruction (the GetCurrentAddress)
; and stores it in the output user variable. 
; This user variable then can be passed to Call or Goto.

Function func
    DetailPrint "function"
    IntOp $0 $0 + 2 ; Calculate the address after of the instruction after "Goto callFunc" in the Section
    Call $0
    DetailPrint "function end"
FunctionEnd

Section
    DetailPrint "section"
    GetCurrentAddress $0
    Goto callFunc

    DetailPrint "back in section"
    Return

callFunc:
    Call func
    DetailPrint "section end"
SectionEnd

; section
; function
; back in section
; function end
; section end
; Completed