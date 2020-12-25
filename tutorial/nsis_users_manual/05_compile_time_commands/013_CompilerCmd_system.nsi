; !system  command [compare  comparevalue  |  symbol]
;
; This command will execute 'command' using a call to system(). 
; You can store the return value in a define ('symbol') or halt execution 
; if the return value compared (using 'compare') to 'comparevalue' is false. 
; 'compare' can be '<' or '>' or '<>' or '='.

!system '"%WINDIR%\notepad.exe" "${NSISDIR}\COPYING"'

!system 'echo !define something > newinclude.nsh'
!include newinclude.nsh
!ifdef something
  !echo "something is defined"
!endif

; default
Section
SectionEnd