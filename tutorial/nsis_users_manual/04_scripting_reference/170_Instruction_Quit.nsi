; Quit
;
; Causes the installer to exit as soon as possible. 
; After Quit is called, the installer will exit and no callback functions 
; will get a chance to run.


Section
    MessageBox MB_OK "#1 is visible"
    MessageBox MB_OK "#2 last visible - quit before #3"
    Quit
    MessageBox MB_OK "#3 is visible"
SectionEnd
