; FileRead  handle  user_var(output)  [maxlen]
;
; Reads a string (ANSI characters) from a file opened with FileOpen. 
; The string is read until either 
;       a newline (or carriage return newline pair) occurs, or 
;       until a null byte is read, or 
;       until maxlen is met (if specified).
; By default, strings are limited to 1024 characters. 
; A special build with larger NSIS_MAX_STRLEN can be compiled or downloaded.
; If the end of file is reached and no more data is available, the output string
; will be empty and the error flag will be set.


Section
    FileOpen $0 176_Instruction_FileRead.nsi r
loop:    
    FileRead $0 $1
    IfErrors eof 0
    DetailPrint $1
    Goto loop
eof:
    FileClose $0
SectionEnd