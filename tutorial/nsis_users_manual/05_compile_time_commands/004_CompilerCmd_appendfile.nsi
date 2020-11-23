; !appendfile  [/CHARSET=ACP|OEM|CP#|UTF8[SIG]|UTF16<LE|BE>[BOM]]  [/RawNL]  file  text
;
; Appends text to file. 
; The text is written as ANSI (ACP) unless the file already has a BOM. 
; Using /CHARSET will force a specific character encoding. 
; $\n will be translated to $\r$\n on Windows unless you specify /RawNL.

!tempfile FILE
!appendfile "${FILE}" "XPStyle on$\n"
!appendfile "${FILE}" "Name 'test'$\n"
!include "${FILE}"
!delfile "${FILE}"
!undef FILE

Section
    ; Installer Name='test' is displayed as window Title.
SectionEnd