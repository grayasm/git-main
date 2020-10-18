; Rename [/REBOOTOK] source_file dest_file
;
; Rename source_file to dest_file.
; Move a file from anywhere on the system to anywhere else.
; Move a directory to somewhere else on the same drive.
; If the destination exists the move will fail (unless /REBOOTOK is given).
; If no absolute path is specified the current folder will be used.
; The current folder is the folder set using the last SetOutPath instruction.
; If you have not used SetOutPath the current folder is $EXEDIR.


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    File 109_Instruction_Rename.nsi
    Rename 109_Instruction_Rename.nsi Renamed.nsi    
SectionEnd