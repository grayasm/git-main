# Section
; Section [/o] [([!]|[-])section_name] [section_index_output]

;   * begins and opens a new section
;   * if section_name is empty, omitted or begins with a - the it is hidden
;     section and the user will not have the option of disabling it
;   * if section_name is "Uninstall" or "un." then it is an uninstaller section
;   * if section name begins with ! the section name is displayed as bold
;   * if /o switch is specified the section will be unselected by default
;   * if section_index_output is specified it will be !defined with the section index.
;     can be used with SelectionSetText.

Page components

Section "-hidden section"
SectionEnd

Section # hidden section
SectionEnd

Section "!bold section"
SectionEnd

Section /o "optional"
SectionEnd

Section "install something" SEC_IDX
SectionEnd

Function .onInit
    SectionGetText ${SEC_IDX} $0
    MessageBox MB_OK "name of ${SEC_IDX} : $0" ; 'name of 4 : install something'
FunctionEnd

