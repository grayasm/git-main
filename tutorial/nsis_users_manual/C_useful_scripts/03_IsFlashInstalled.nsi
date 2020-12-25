; IsFlashInstalled
;
; Usage:
;   Call IsFlashInstalled
;   Pop $R0 ; 1 or ""

Function IsFlashInstalled
Push $R0
ReadRegStr $R0 HKCR "CLSID\{D27CDB6E-AE6D-11cf-96B8-444553540000}" ""
StrCmp $R0 "" +2
  StrCpy $R0 "1"
Exch $R0
FunctionEnd


Section
    Call IsFlashInstalled
    Pop $R0
    StrCmp $R0 1 found_FlashInstalled no_FlashInstalled
found_FlashInstalled:
    DetailPrint "IsFlashInstalled is TRUE"
Goto end
no_FlashInstalled:
    DetailPrint "IsFlashInstalled is FALSE"
Goto end
end:
SectionEnd