; Int64Fmt  user_var(output)  format  numberstring
;
; Supports the I and I64 length fields and the p type in addition 
; to the syntax supported by IntFmt.

; This function is only available when building a 64-bit installer.

Section
    Int64Fmt $0 "%I64x" 244837743786702
    DetailPrint $0
SectionEnd

; Error: Instruction only supported by 64-bit targets!