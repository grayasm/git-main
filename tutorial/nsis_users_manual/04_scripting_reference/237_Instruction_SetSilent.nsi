; SetSilent  silent | normal
;
; Sets the installer to silent mode or normal mode. 
; See SilentInstall for more information about silent installations. 
; Can only be used in .onInit.

Section
    Sleep 1000

    IfSilent 0 +2
        MessageBox MB_OK "The installer is silent."

    Sleep 1000
SectionEnd

Function .onInit
    SetSilent silent
FunctionEnd