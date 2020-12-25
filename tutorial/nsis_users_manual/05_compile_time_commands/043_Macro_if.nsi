; !if  [!]  value  [op  value2]
; !if  [!]  /FileExists "c:\path\file.exe"

; This command, when paired with an !endif command, will tell the compiler 
; whether or not to compile the lines in between the two lines. 
; If value is non-zero, or the comparison of value and value2 depending on
; the operator results in true, the contained lines will be compiled. 
; Otherwise, they will be skipped. 

; op can be either == or != (case-insensitive string comparison), 
; S== or S!= (case-sensitive string comparison), 
; =, <>, <=, <, > or >= (int/hex/float comparison), 
; & (bitwise AND comparison), && or || (boolean comparison). 

; If [!] is set, the result will be flipped from true to false and vice versa.

!if 1 < 0x2
    !echo "1 is smaller than 2!!"
!else if ! 3.1 > 1.99
    !error "this line should never appear"
!else
    !error "neither should this"
!endif

!if /FileExists ".\cert.pfx"
    !finalize '".\sign.bat" "%1"'
!endif


; default
Section
SectionEnd