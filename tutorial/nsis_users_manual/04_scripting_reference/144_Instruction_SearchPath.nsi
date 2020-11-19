; SearchPath  user_var(output)  filename
;
; Assign to the user variable $x, the full path of the file named by 
; the second parameter. The error flag will be set and $x will be empty 
; if the file cannot be found. 
; Uses WIN32 SearchPath(...) to search the system paths for the file.

Section
; searches in the system directory
    SearchPath $0 notepad.exe
    StrCmp $0 "" 0 +3
    DetailPrint "Path not found"
    Goto +2
    DetailPrint "Path found: $0"
    
; searches in the current directory
    SearchPath $0 108_timeout.exe
    StrCmp $0 "" 0 +3
    DetailPrint "Path not found"
    Goto +2
    DetailPrint "Path found: $0"
SectionEnd