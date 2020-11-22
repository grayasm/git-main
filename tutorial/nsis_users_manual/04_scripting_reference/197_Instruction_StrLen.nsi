; StrLen  user_var(length output)  str
;
; Sets user variable $x to the length of str.

Section
    StrLen $0 "123456" ; 6
    DetailPrint "StrLen of '123456'=$0"
SectionEnd