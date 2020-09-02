; ShowInstDetails hide | show | nevershow
;
; Sets whether or not the details of the install are shown.
;       hide: will hide the details by default, allowing the user to view them
;       show: will show them by default
;       nevershow: will prevent the user from ever seeing them.
; Note that sections can override this using SetDetailsView.

ShowInstDetails nevershow

InstallDir "$DOCUMENTS\78_attributes_ShowInstDetails"

Section
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
