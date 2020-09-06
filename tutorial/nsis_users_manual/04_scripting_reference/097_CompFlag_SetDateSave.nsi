; SetDateSave on | off
;
; Default is on.
; This command sets the file date/time saving flag which is used by the
; File command to determine whether or not to save the last write date and time
; of the file, so that it can be restored on installation.

SetDateSave on


Section
    File 097_CompFlag_SetDateSave.nsi
SectionEnd