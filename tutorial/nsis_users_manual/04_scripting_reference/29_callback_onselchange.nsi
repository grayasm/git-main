# .onSelChange (install callback)
;
; Called when the selection changes on the components page.
; Useful for using with SectionSetFlags and SectionGetFlags


Function .onSelChange
    SectionGetText $0 $R0
    MessageBox MB_OK|MB_ICONEXCLAMATION ".onSelChange section=$R0"
FunctionEnd


Page components
Page instfiles

Section "Program section"   PROG_SEC_ID
SectionEnd

Section "Help section"      HELP_SEC_ID
SectionEnd