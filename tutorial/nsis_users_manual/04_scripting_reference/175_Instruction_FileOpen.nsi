; FileOpen  user_var(handle output)  filename  openmode
;
; Opens the "filename" file and sets the handle output variable with the handle. 
; The openmode should be one of 
;   "r" (read) 
;   "w" (write, all contents of file are destroyed) or 
;   "a" (append, meaning opened for both read and write, contents preserved). 
; In all open modes, the file pointer is placed at the beginning of the file. 
; If the file cannot be opened the handle output is set to empty and 
; the error flag is set.

; If no absolute path is specified the current folder will be used. 
; The current folder is the folder set using the last SetOutPath instruction. 
; If you have not used SetOutPath the current folder is $EXEDIR.


Section
    FileOpen $0 175_Instruction_FileOpen.nsi r
    FileRead $0 $1
    FileClose $0
    MessageBox MB_OK $1
SectionEnd