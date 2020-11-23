; !delfile  [/nonfatal]  file
;
; This command deletes a file.

!tempfile FILE
!delfile "${FILE}"

Section
    ; This file exists only at compile time - checked with lh13zh
    DetailPrint "FILE=${FILE}"
SectionEnd

!undef FILE