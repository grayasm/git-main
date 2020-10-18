; Exec command
;
; Execute the specified program and continue immediately.
; Note that the file specified must exist on the target system, 
; not the compiling system.
; $OUTDIR is used as the working directory.
; If the command has spaces use: '"$INSTDIR\command.exe" parameters'.


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath "$INSTDIR"
    File 104_Instruction_exec.nsi
    Exec 'notepad.exe $INSTDIR\104_Instruction_exec.nsi'
SectionEnd

# remove "$DOCUMENTS\MyApp" manually