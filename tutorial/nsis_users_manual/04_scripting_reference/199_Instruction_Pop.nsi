; Pop user_var(out)
;
; Pops a string off of the stack into user variable $x. 
; If the stack is empty, the error flag will be set.

Section
    StrCpy $0 0
    StrCpy $1 "var $$1"
    StrCpy $2 "var $$2"
    
    Push 1
    Pop $0
    Pop $1      ; non-existant, SetErrors true
    Pop $2      ; non-existant, SetErrors true
    
    DetailPrint "$0"
    DetailPrint "$1"
    DetailPrint "$2"
    
    IfErrors 0 done
        DetailPrint "Error flag was set"
done:
SectionEnd