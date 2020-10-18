; ExecShellWait [/INVOKEIDLIST] action command [parameters] [SW_SHOWDEFAULT | SW_SHOWNORMAL | SW_SHOWMAXIMIZED | SW_SHOWMINIMIZED | SW_HIDE]
;
; Execute the specified program using ExecShell and wait for executed process to quit.
; It will only wait for executable files, not other file types nor URLs.


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    ExecShellWait "" "ping.exe" "-n 5 127.0.0.1" SW_SHOWNORMAL

    ; ExecShellWait will wait for ping to terminate!
    ExecShellWait "open" "https://nsis.sourceforge.io/"
    
    ; SetOutPath "$INSTDIR"
    ; File 105_Instruction_ExecShell.nsi
    ; ExecShellWait "" "notepad.exe" "$INSTDIR\105_Instruction_ExecShell.nsi"
SectionEnd
