; BringToFront
;
; Makes the installer window visible and brings it to the top of the window list. 
; If an application was executed that shows itself in front of the installer, 
; BringToFront would bring the installer back in focus.

; Recent Windows versions restrict the setting of foreground windows. 
; If the user is working with another application during installation,
; the user may be notified using a different method.


Section
    MessageBox MB_OK "Hide window for 3 seconds!"
    HideWindow
    Sleep 3000
    BringToFront
SectionEnd