# InstProgressFlags [flag [...]]
;
; Valid values for flag are "smooth" and/or "colored".
; smooth: smooth the progress bar
; colored: color the progress bar with the colors set by InstallColors

InstallColors FFA500 000000
InstProgressFlags smooth colored


InstallDir "$DESKTOP\TestingInstall"
Page directory
Page instfiles

Section ""
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
