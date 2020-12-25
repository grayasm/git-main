; !ifmacrodef  gflag  [bcheck  gflag  [...]]]
;
; This command, when paired with an !endif command, will tell the compiler 
; whether or not to compile the lines in between the two lines. 
; If the macro gflag exists, then the contained lines will be compiled. 
; Otherwise, they will be skipped. 

; 'bcheck' can be specified as & (boolean and) or | (boolean or) 
; along with more gflags -- precedence is simple, left to right.

!macro SomeMacro
!macroend
!ifmacrodef SomeMacro
    !echo "SomeMacro is defined"
!endif


; default
Section
SectionEnd