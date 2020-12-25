; IsDotNETInstalled
;
; NOTE: This is only able to detect .NET v1.x and v2.x!
;
; Based on GetDotNETVersion
;   https://nsis.sourceforge.io/Get_.NET_Version
;
; Usage:
;   Call IsDotNETInstalled
;   Pop $0 ; 0 or 1
;   StrCmp $0 1 found_dotNETFramework_v1_or_v2 no_dotNETFramework

Function IsDotNETInstalled
  Push $0
  System::Call '"$SysDir\MSCOREE.dll"::GetCORVersion(w,i${NSIS_MAX_STRLEN},*i)i.r0?u'
  IntOp $0 $0 ! ; HRESULT (S_OK) -> BOOL
  Exch $0
FunctionEnd

Section
    Call IsDotNETInstalled
    Pop $0
    StrCmp $0 1 found_dotNETFramework_v1_or_v2 no_dotNETFramework
found_dotNETFramework_v1_or_v2:
    DetailPrint "IsDotNETInstalled is TRUE"
Goto end
no_dotNETFramework:
    DetailPrint "IsDotNETInstalled is FALSE"
Goto end
end:    
SectionEnd