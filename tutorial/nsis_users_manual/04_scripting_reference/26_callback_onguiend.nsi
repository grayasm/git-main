# .onGUIEnd (install callback)

; This callback is called right after the installer window closes.
; Use it to free any user interface related plug-in if needed.

Function .onGUIEnd
    MessageBox MB_OK ".onGUIEnd called"
FunctionEnd

Section
SectionEnd
