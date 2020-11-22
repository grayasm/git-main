; FileReadUTF16LE  handle  user_var(output)  [maxlen]
;
; This function is only available when building a Unicode installer.

; Reads a string (UTF-16LE characters) from a file opened with FileOpen. 
; The string is read until either
;       a newline (or carriage return newline pair) occurs, or 
;       until a null wide-character is read, or 
;       until maxlen is met (if specified). 
; By default, strings are limited to 1024 characters.
; A special build with larger NSIS_MAX_STRLEN can be compiled or downloaded.
; If the end of file is reached and no more data is available, the output string 
; will be empty and the error flag will be set.
; If present, the BOM at the start of the file is skipped.

Unicode true

Section
    ClearErrors
    FileOpen  $0  177_Instruction_FileReadUTF16LE.nsi  r
    IfErrors done
    FileReadUTF16LE $0 $1
    DetailPrint $1
    FileClose $0
done:
SectionEnd