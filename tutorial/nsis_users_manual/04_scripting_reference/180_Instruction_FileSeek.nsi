; FileSeek  handle  offset  [mode]  [user_var(new position)]
;
; Seeks a file opened with FileOpen. 
; If mode is omitted or specified as SET, the file is positioned to "offset", 
;       relative to the beginning of the file. 
; If mode is specified as CUR, then the file is positioned to "offset", 
;       relative to the current file position. 
; If mode is specified as END, then the file is positioned to "offset", 
;       relative to the end of the file.
; If the final parameter "new position" is specified, the new file position 
; will be stored in that variable.

Section
    ClearErrors
    FileOpen $0  180_Instruction_FileSeek.nsi  r
    IfErrors done
    FileSeek $0 -22 END
    FileRead $0 $1
    DetailPrint $1
    FileClose $0
done:
SectionEnd

; FileSeek $0 -100 END