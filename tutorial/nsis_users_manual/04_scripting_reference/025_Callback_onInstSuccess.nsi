# .onInstSuccess (install callback)

; This callback is called when the install was successful, right before the
; install window closes (which may be after the user clicks 'Close' if
; AutoCloseWindow or SetAutoClose is set to false.

Function .onInstSuccess
    MessageBox MB_YESNO "Congrats, it worked. View readme?" IDNO NoReadme
        Exec "notepad.exe README.txt"
    NoReadme:
FunctionEnd


Section
SectionEnd