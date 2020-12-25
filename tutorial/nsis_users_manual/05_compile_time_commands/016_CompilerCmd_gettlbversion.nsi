; !gettlbversion  [/noerrors]  [/packed]  localfilename  define_basename
;
; Get the version information from a .TLB file.

!gettlbversion /packed "$%WINDIR%\System32\stdole32.tlb" TLBVER_
!echo "${TLBVER_HIGH}.${TLBVER_LOW}"


; default
Section
SectionEnd


; compiler output:

; !gettlbversion: C:\WINDOWS\System32\stdole32.tlb (1.0)->(TLBVER_<HIGH/LOW>)
; 1.0 