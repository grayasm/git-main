; ${NSIS_CHAR_SIZE}
;
; The size of a character code unit (in bytes).
; 1 in ANSI installers and 2 in Unicode installers.
;
; A grapheme cluster consists of a base character plus 
; optional combining characters and diacritics and is defined 
; as one or more code points.
; One or more code units is required to encode a single code point.

!echo "The size of a character code unit is ${NSIS_CHAR_SIZE}"

; default
Section
SectionEnd


; compiler output:

;The size of a character code unit is 1