; SilentUnInstall normal | silent
;
; Specifies whether or not the uninstaller should be silent.
; If it is 'silent' the uninstall sections will run quietly,
; with no screen output from the uninstaller itself

!define SF_SELECTED   1
!define SF_SECGRP     2
!define SF_SECGRPEND  4
!define SF_BOLD       8
!define SF_RO         16
!define SF_EXPAND     32
!define SF_PSELECTED  64

SilentUnInstall silent

InstallDir "$DOCUMENTS\81_attributes_SilentUninstall"

Section 1 id_1
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd


Section Uninstall id_2
    ; SectionSetFlags advanced
    IntOp $0 ${SF_SELECTED} | ${SF_RO}
    SectionSetFlags ${id_2} $0
    
    ; uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir $INSTDIR
    
    ; take 10 sec
    DetailPrint "Uninstalling ..."
    StrCpy $0 0
loop:
    IntCmp $0 10 done +1 done ; eq lt gt
    IntOp $0 $0 + 1
    DetailPrint "$$0=$0"
    Sleep 1000
    Goto loop
done:
SectionEnd