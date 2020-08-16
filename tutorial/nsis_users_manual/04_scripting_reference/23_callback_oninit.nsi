# .onInit (install callback)
;
;   * called when the installer is nearly finished initializing
;   * if function calls Abort, the installer will quit instantly

Function .onInit
    MessageBox MB_YESNO "This will install. Continue?" IDYES NoAbort
        Abort
    NoAbort:
FunctionEnd

Section
SectionEnd