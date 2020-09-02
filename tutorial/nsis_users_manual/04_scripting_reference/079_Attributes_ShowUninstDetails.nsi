; ShowUninstDetails hide | show | nevershow
;
; Sets whether or not the details of the uninstall are shown. 
; hide: will hide the details by default, allowing the user to view them
; show: will show them by default
; nevershow: will prevent the user from ever seeing them.
; Note that sections can override this using SetDetailsView.


ShowUninstDetails nevershow

InstallDir "$DOCUMENTS\79_attributes_ShowUninstDetails"

Section "Install"
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd


Section "Uninstall"
    ; uninstaller
    Delete "$INSTDIR\uninstall.exe"
    RMDir $INSTDIR
    
    ; nevershow
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
