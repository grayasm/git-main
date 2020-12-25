; !ifdef  gflag  [bcheck  gflag [...]]
;
; This command, when paired with an !endif command, will tell the compiler
; whether or not to compile the lines in between the two lines. 
; If gflag is globally defined (using !define or the /D switch), 
; then the contained lines will be compiled. Otherwise, they will be skipped. 

; 'bcheck' can be specified as & (boolean and) or | (boolean or) 
; along with more gflags -- precedence is simple, left to right.

!define SOMETHING
!ifdef SOMETHING
    !echo "SOMETHING is defined"
!endif
!undef SOMETHING
!ifdef SOMETHING
    !echo "SOMETHING is defined" # will never be printed
!endif


; default
Section
SectionEnd