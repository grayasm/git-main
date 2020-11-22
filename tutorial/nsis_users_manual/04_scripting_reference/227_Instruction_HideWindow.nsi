; HideWindow
;
; Hides the installer window.


Section
    MessageBox MB_OK "Hide window for 3 seconds!"
    HideWindow
    Sleep 3000
    BringToFront
SectionEnd