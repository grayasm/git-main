; GetIEVersion
;
; Returns 1-11 (IE Version) or '' (IE is not installed) on top of the stack
;
; Usage:
;   Call GetIEVersion
;   Pop $R0 ; $R0 is "5" etc.

Function GetIEVersion
  Push $R0
  ReadRegStr $R0 HKLM "Software\Microsoft\Internet Explorer" "svcVersion" ; IE v10+
  StrCpy $R0 $R0 2
  IntCmp $R0 9 "" "" lbl_done
  ClearErrors
  ReadRegStr $R0 HKLM "Software\Microsoft\Internet Explorer" "Version" ; IE v4..9
  IfErrors lbl_123
    StrCpy $R0 $R0 1 ; Note: This truncates 5.50 to 5 etc.
    Goto lbl_done
  lbl_123:
  !if "${NSIS_PTR_SIZE}" > 4
  StrCpy $R0 ""
  !else
  ReadRegStr $R0 HKLM "Software\Microsoft\Internet Explorer" "IVer" ; IE v1..3
  IntCmp $R0 99 "" "" +3
    StrCpy $R0 ""
    Goto lbl_done
  IntOp $R0 $R0 & 3 ; 100..103->0..3
  IntCmp $R0 2 +2 "" +2
    IntOp $R0 $R0 + 1 ; Bump 100->v1 and 101->v2 (Is 101 v1.5 or 2.0?)
  !endif
  lbl_done:
  Exch $R0
FunctionEnd

Section
    Call GetIEVersion
    Pop $R0
    DetailPrint "GetIEVersion=$R0"
SectionEnd