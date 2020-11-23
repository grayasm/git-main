; !execute  command [compare  comparevalue  |  symbol]
;
; This command will execute 'command' using a call to CreateProcess(). 
; Unlike !system, it does not use the command line processor, so input/output 
; redirection and commands like 'cd', 'dir' and 'type' can not be used. 

; Currently, the only known advantage of !execute over !system is that 
; it does not give trouble when the current working directory is specified 
; using UNC.

; On POSIX platforms, !execute will use system() just like !system.

!execute '"$%WINDIR%\notepad.exe" /P "${NSISDIR}\COPYING"'

Section
SectionEnd