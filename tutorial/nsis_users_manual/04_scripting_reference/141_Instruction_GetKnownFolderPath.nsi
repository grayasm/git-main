; GetKnownFolderPath  user_var(output)  knownfolderid
;
; Get the path of a known folder. 
; The error flag is set and the output variable is empty if the call fails 
; or the knownfolderid guid is not available. 
; This function is only able to resolve known folders on Windows Vista or higher.

!include WinCore.nsh
!include LogicLib.nsh

Name "MyApp"

Section
    DetailPrint ".onInit INSTDIR=$INSTDIR"
SectionEnd

Function .onInit
${If} $InstDir == ""
  GetKnownFolderPath $InstDir ${FOLDERID_UserProgramFiles} ; This exists on Win7+
  StrCmp $InstDir "" 0 +2 
  StrCpy $InstDir "$LocalAppData\Programs" ; Fallback directory
  StrCpy $InstDir "$InstDir\$(^Name)"
${EndIf}
FunctionEnd