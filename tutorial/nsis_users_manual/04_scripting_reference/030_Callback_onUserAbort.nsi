# .onUserAbort (install callback)
;
; This callback is called when the user hits the 'cancel' button, and the
; install hasn't already failed. If this function calls Abort, the install
; will not be aborted.

Function .onUserAbort
    MessageBox MB_YESNO "Abort install?" IDYES NoCancelAbort
        Abort ; causes the installer to not quit
    NoCancelAbort:
FunctionEnd

Page components
Page instfiles

Section "Programs"
SectionEnd

Section "Manual"
SectionEnd