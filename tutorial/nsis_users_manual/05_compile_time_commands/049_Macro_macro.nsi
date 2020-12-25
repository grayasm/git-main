; !macro  macro_name  [parameter][...]
;
; Creates a macro named 'macro_name'. 
; All lines between the !macro and the !macroend will be saved. 
; To insert the macro later on, use !insertmacro. 
; !macro definitions can have one or more parameters defined. 
; The parameters may be accessed the same way a !define would (e.g. ${PARMNAME})
; from inside the macro.

!macro SomeMacro parm1 parm2 parm3
    DetailPrint "${parm1}"
    MessageBox MB_OK "${parm2}"
    File "${parm3}"
!macroend

; default
Section
    !insertmacro SomeMacro "this is parm1" "this is parm2" "049_Macro_macro.nsi"
SectionEnd

/* compiler output:

Section: ""
!insertmacro: SomeMacro
DetailPrint: "this is parm1"
MessageBox: 0: "this is parm2"
File: "049_Macro_macro.nsi" [compress] 334/618 bytes
!insertmacro: end of SomeMacro
SectionEnd

*/