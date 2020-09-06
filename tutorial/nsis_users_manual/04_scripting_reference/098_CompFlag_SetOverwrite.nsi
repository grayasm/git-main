; SetOverwrite on | off | try | ifnewer | ifdiff | lastused
;
; This command sets the overwrite flag which is used by the File command
; to determine whether or not the file should overwrite any existing files
; that are present.
; 
; on: default, files are overwritten
; off: if already present, files are not overwritten
; try: files are overwritten if possible otherwise skipped without user interaction
; ifnewer: files are overwritten only if existing ones are older than the new files
; iffdiff: files are overwritten if existing ones are older or newer than the new files
; lastused: ??

RequestExecutionLevel user
AllowSkipFiles on
SetOverwrite try
    
InstallDir "$PROGRAMFILES64\Cannot-create-directory"

Section 1
    ; skipped due to write protection
    SetOutPath $INSTDIR
    File 098_CompFlag_SetOverwrite.nsi
SectionEnd