; StrCpy  user_var(destination)  str  [maxlen]  [start_offset]
;
; Sets the user variable $x with str.
; str can contain variables, including the user variable being set 
; (concatenating strings this way is possible, etc).
; If maxlen is specified, the string will be a maximum of maxlen characters.
; If maxlen is negative, the string will be truncated abs(maxlen) characters from the end). 
; If start_offset is specified, the source is offset by it. 
; If start_offset is negative, it will start abs(start_offset) from the end of the string).

Section
    StrCpy $0 "a string"        ; "a string"
    StrCpy $1 "a string" 3      ; "a s"
    StrCpy $2 "a string" -1     ; "a strin"
    StrCpy $3 "a string" "" 2   ; "string"
    StrCpy $4 "a string" "" -3  ; "ing"
    StrCpy $5 "a string" 3 -4   ; "rin"
    StrCpy $6 "$5$5"            ; "rinrin"
    
    DetailPrint $0
    DetailPrint $1
    DetailPrint $2
    DetailPrint $3
    DetailPrint $4
    DetailPrint $5
    DetailPrint $6
SectionEnd