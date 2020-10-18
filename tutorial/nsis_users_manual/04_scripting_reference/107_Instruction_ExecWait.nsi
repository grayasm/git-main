; ExecWait command [user_var(exit code)]
;
; Execute the specified program and wait for the executed process to quit.
; If the output variable is specified ExecWait sets it with the exit code.
; If not output variable is specified ExecWait sets the error flag for
; (1) a non-zero exit code or (2) if there is an error.
; Specify the command like this:
; ExecWait '"$INSTDIR\command.exe" parameters' $0


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    ExecWait '"ping.exe" -n 5 127.0.0.1' $0
    DetailPrint "ping program returned $0"
SectionEnd