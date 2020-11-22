; Push  string
;
; Pushes a string onto the stack. 
; The string can then be Pop'ed off of the stack.

Section
    Push "a string"
    Pop $0
    DetailPrint $0
SectionEnd