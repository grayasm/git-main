; ${NSIS_PACKEDVERSION}
;
; NSIS version as a 32-bit number.

!if 0x3014000 >= "${NSIS_PACKEDVERSION}"
  !error "NSIS 3.15 or higher is required to build this installer!"
!endif


; default
Section
SectionEnd


; compiler output

;!error: NSIS 3.15 or higher is required to build this installer!