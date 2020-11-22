; FindWindow  user_var(hwnd output)  windowclass  [windowtitle]  [windowparent]  [childafter]
;
; Searches for a window. 
; Behaves like Win32's FindWindowEx(). 
; Searches by windowclass (and/or windowtitle if specified). 
; If windowparent or childafter are specified, the search will be restricted as such.
; If windowclass or windowtitle is specified as "", they will not be used for the search. 
; If the window is not found the user variable is set to 0.


Section
    FindWindow $1 "#32770"  "" $HWNDPARENT  ; Finds the inner dialog
    FindWindow $2 "EDIT"    "" $1           ; Finds the first edit control in the inner dialog
    
    MessageBox MB_OK "The inner dialog: $1$\nThe first edit control: $2"    
SectionEnd