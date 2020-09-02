; SilentInstall normal | silent | silentlog
;
; Specifies whether or not the installer should be silent.
; If it is 'silent' or 'silentlog', all sections that have the SF_SELECTED flag
; are installed quietly (you can set this flag using SectionSetFlags)

!define SF_SELECTED   1


; Installer window will be hidden.
SilentInstall silent


Section 1 id_1
    ; silent
    SectionSetFlags ${id_1} ${SF_SELECTED}

    ; take 10 sec
    DetailPrint "Installing ..."
    StrCpy $0 0
loop:
    IntCmp $0 10 done +1 done ; eq lt gt
    IntOp $0 $0 + 1
    DetailPrint "$$0=$0"
    Sleep 1000
    Goto loop
done:
SectionEnd

