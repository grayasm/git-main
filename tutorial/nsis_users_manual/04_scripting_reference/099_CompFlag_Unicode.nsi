; Unicode   true | false
;
; Generate a Unicode installer.
; It can only be used outside of sections and functions and before any data is compressed.

Unicode true

; persian for "directory"
InstallDir "$DOCUMENTS\فهرست راهنما"

Section
    SetOutPath $INSTDIR
    File 099_CompFlag_Unicode.nsi
SectionEnd