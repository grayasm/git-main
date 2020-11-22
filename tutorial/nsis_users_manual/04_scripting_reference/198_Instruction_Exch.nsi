; Exch  [user_var | stack_index]
;
; When no parameter is specified, exchanges the top two elements of the stack. 
; When a parameter is specified and is a user variable, exchanges 
; the top element of the stack with the parameter. 
; When a parameter is specified and is a positive integer, Exch will swap 
; the item on the top of the stack with the item that is specified by the offset 
; from the top of the stack in the parameter. 
; If there are not enough items on the stack to accomplish the exchange, 
; a fatal error will occur (to help you debug your code :).

Section
    Push 1
    Push 2
    Exch
    Pop $0 ; = 1
    Pop $1 ; = 2
    DetailPrint "$0 $1"
    
    StrCpy $0 1
    Push 2
    Exch $0 ; = 2
    Pop $1  ; = 1
    DetailPrint "$0 $1"
    
    Push 1
    Push 2
    Push 3
    Exch 2
    Pop $0 ; = 1
    Pop $1 ; = 2
    Pop $2 ; = 3
    DetailPrint "$0 $1 $2"
SectionEnd