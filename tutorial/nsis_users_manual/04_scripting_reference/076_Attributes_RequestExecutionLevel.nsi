; RequestExecutionLevel none | user | highest | admin
;
; Specifies the requested execution level for Windows Vista and higher.
; The value is embedded in the installer and uninstaller's XML manifest and
; tells Windows which privilege level the installer requires.
;
; none - same as admin
; user - no administrative privileges
; highest - if member of administrators group will cause the prompt to verify privilage escalation.
; admin - request administrator level

RequestExecutionLevel user

InstallDir "$PROGRAMFILES64\Cannot-create-directory"

Section 1
    ; force error due to write protection
    SetOutPath $INSTDIR
    File 76_attributes_requestexecutionlevel.nsi
SectionEnd