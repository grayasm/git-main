; ExecShell [/INVOKEIDLIST] action command [parameters] [SW_SHOWDEFAULT | SW_SHOWNORMAL | SW_SHOWMAXIMIZED | SW_SHOWMINIMIZED | SW_HIDE]
;
; Execute the specified program using ShellExecuteEx.
; Note that action is usually "open", "print", etc, but can be an empty string
; to use the default action. Parameters and the show type are optional.
; $OUTDIR is used as the working directory.

InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    ExecShell "" "ping.exe" "-n 5 127.0.0.1" SW_SHOWNORMAL

    ; ExecShell does not wait for ping to finish. It will execute these immediately!!
    ; ExecShell "open" "https://nsis.sourceforge.io/"
    ; SetOutPath "$INSTDIR"
    ; File 105_Instruction_ExecShell.nsi
    ; ExecShell "" "notepad.exe" "$INSTDIR\105_Instruction_ExecShell.nsi"
SectionEnd
