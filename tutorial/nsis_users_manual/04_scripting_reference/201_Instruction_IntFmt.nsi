; IntFmt  user_var(output)  format  numberstring
;
; Formats the number in "numberstring" using the format "format",
; and sets the output to user variable $x.
; The format string supports the same syntax as wsprintf except that the
; I[32|64] length fields and the p type are not supported. 
; Example format strings include "%08X" and "%u".

Section
    IntFmt $0 "0x%08X" 195948557
    IntFmt $1 "%c" 0x41

    DetailPrint $0
    DetailPrint $1
SectionEnd