# Relative Jumps
; Unlinke labels, relative jumps are relative to the place they are called from.
; You can use relative jumps wherever you can use labels.
; Relative jumps are marked by numbers.
; +1 jumps to the next instruction (the default advancement).
; -2 jumps two instructions backward
; A instruction is executed at run-time when the installer is running.
; A Compiler Command is not an instruction because it is executed at compile time.


!macro relative_jump_test
    DetailPrint "1st macro line"
    DetailPrint "2nd macro line"
!macroend

Section 1
    Goto +2
    DetailPrint "You will never see this message"
    DetailPrint "The previous message was skipped"
    
    Goto +2
    !insertmacro relative_jump_test
SectionEnd


Section 2
    Var /GLOBAL ii
    StrCpy $ii 5
    DetailPrint "$$ii=$ii"
    IntCmp $ii 0 +3 +3 +1  ; IntCmp val1 val2 jmp_if_eq jmp_if_lt jmp_if_gt
    IntOp  $ii $ii - 1
    Goto -3
    DetailPrint "Cycle ended"
SectionEnd
