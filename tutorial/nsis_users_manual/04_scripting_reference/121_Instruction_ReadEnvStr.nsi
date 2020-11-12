; ReadEnvStr user_var(output) name
;
; Reads from the environment string "name" and sets the value into the user
; variable $x. If there is an error reading the string, the user variable is set 
; to empty, and the error flag is set.


Section
    ReadEnvStr $0 WINDIR
    ReadEnvStr $1 TEMP
    
    DetailPrint "WINDIR=$0"
    DetailPrint "TEMP=$1"    
SectionEnd