# InstType install_type_name [index_output] | /NOCUSTOM | /CUSTOMSTRING=str | /COMPONENTSONLYONCUSTOM
;
; Adds an install type to the install type list, or disable the custom install type.
; There can be as many as 32 types, each one of specifying the name of the install type.
; If the name is prefixed with un. it is an uninstaller type.
; You can change the InstType during runtime with InstTypeSetText command.
;
; More here: https://nsis.sourceforge.io/Docs/Chapter4.html#ainsttype

!include "Sections.nsh"
 
Insttype "/CUSTOMSTRING=Please make your choice"
Insttype "English Interface"
Insttype "French Interface"
 
page components
page instfiles
 
Section "Common Files (Required)" 
  SectionIn RO
    # common files here
SectionEnd
 
Section "English Language Files" SEC_ENG 
  SectionIn 1
    # ENG files here
SectionEnd
 
Section /o "French Language Files" SEC_FRA 
  SectionIn 2
    # FRA files here
SectionEnd
 
Function .onInit
  StrCpy $1 ${SEC_ENG}
FunctionEnd
 
Function .onSelChange
    !insertmacro StartRadioButtons $1
        !insertmacro RadioButton ${SEC_ENG}
        !insertmacro RadioButton ${SEC_FRA}
    !insertmacro EndRadioButtons
FunctionEnd