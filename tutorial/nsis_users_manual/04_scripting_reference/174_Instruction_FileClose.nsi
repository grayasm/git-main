; FileClose handle
;
; Closes a file handle opened with FileOpen.

Section
    FileOpen $0 174_Instruction_FileClose.nsi  r
    FileRead $0 $1
    FileClose $0
    MessageBox MB_OK $1
SectionEnd
