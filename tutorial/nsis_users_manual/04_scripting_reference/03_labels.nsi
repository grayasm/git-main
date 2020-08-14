# Labels
; Labels are the targets of Goto and various branching instructions such as
; IfErrors, MessageBox, IfFileExists and StrCmp.
; They must be within a Section or Function, are local in scope and accessible
; from within the Section or Function.
; Labels beginning with a period (.) are global and you can jump to them from
; any Section or Function.

Section 1
    ; StrCmp str1 str2 jmp_if_eq jmp_if_neq
    StrCmp $0 "a random string" jmp_if_eq
    DetailPrint "$$0 != 'a random string'"
    Goto +2
jmp_if_eq:
    DetailPrint "$$0 == 'a random string'"
SectionEnd
