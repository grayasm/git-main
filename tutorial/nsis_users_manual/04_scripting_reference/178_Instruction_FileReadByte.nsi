; FileReadByte  handle  user_var(output)
;
; Reads a byte from a file opened with FileOpen.
; The byte is stored in the output as an integer (0-255). 
; If the end of file is reached and no more data is available, 
; the output will be empty and the error flag will be set.

Section
    FileOpen $0 108_timeout.exe r
    StrCpy $R0 0
loop:
    FileReadByte $0 $1
    IfErrors eof 0
    DetailPrint "Byte $R0=$1"
    IntOp $R0 $R0 + 1
    IntCmp $R0 5 eof loop eof
eof:
    FileClose $0
SectionEnd