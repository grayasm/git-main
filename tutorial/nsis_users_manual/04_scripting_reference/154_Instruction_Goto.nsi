; Goto  label_to_jump_to  |  +offset  |  -offset  |  user_var(target)
;
; If label is specified, goto the label 'label_to_jump_to:'.
; If +offset or -offset is specified, jump is relative by offset instructions. 
; Goto +1 goes to the next instruction
; Goto -1 goes to the previous instruction
;
; If a user variable is specified, jumps to absolute address (generally you 
; will want to get this value from a function like GetLabelAddress). 
; Compiler flag commands and SectionIn aren't instructions so jumping over them 
; has no effect.


Section
    DetailPrint "#1 line"
    Goto 0
    DetailPrint "#2 line"
    Goto +1
    DetailPrint "#3 line"
    Goto +2
    DetailPrint "#4 line"
    Goto -6
    DetailPrint "#5 line"
    Goto label
    DetailPrint "#6 line"
    label:
    DetailPrint "#7 line"
    Return
SectionEnd

# infinite loop