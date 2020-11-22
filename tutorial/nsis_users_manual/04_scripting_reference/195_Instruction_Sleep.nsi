; Sleep  sleeptime_in_ms
;
; Pauses execution in the installer for sleeptime_in_ms milliseconds. 
; sleeptime_in_ms can be a variable, e.g. "$0" or a number, i.e. "4321".

Section
    DetailPrint "sleeping..."
    Sleep 3000
    DetailPrint "back to work"
SectionEnd