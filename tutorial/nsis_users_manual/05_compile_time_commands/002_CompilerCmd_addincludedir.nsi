; !addincludedir  directory
;
; Adds another include directory to the include directories list. 
; This list is searched when !include is used. 
; This list's initial value is ${NSISDIR}\Include.

; !addincludedir ..\include
; !include something.nsh

Section
    DetailPrint "NSISDIR=${NSISDIR}"
SectionEnd