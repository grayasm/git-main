; !insertmacro  macro_name  [parameter]  [...]
;
; Inserts the contents of a macro that was created with !macro.
; If the macro was created with parameters, then you must pass as many parameters 
; to the macro as it requires.

!macro Print text
    DetailPrint "${text}"
!macroend

Section
    !insertmacro Print "some text"
    !insertmacro Print "some more text"
SectionEnd