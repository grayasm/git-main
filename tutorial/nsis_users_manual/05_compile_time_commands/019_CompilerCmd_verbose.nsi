; !verbose  level | push | pop
;
; This command will set the level of verbosity:
;       4=all
;       3=no script
;       2=no info
;       1=no warnings
;       0=none.
;
; Passing push will cause !verbose to push the current verbosity level on a special stack.
; Passing pop will cause !verbose to pop the current verbosity level from the same stack and use it.

!verbose push
!verbose 1
!include WinMessages.nsh
!verbose pop


; default
Section
SectionEnd