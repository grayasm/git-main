# SectionGroup
; SectionGroup [/e] section_group_name [index_output]

;   * a section group must have at least 1 section.
;   * if the group name begins with a ! it's name will be displayed with bold
;   * if /e is present the section group will be expanded by default
;   * if index_output is specified, the parameter will be !defined with the
;     section index
;   * if prefixed with un. the section group is an uninstaller section group

Page components
Page instfiles

SectionGroup "some stuff"
    Section "a section"
        DetailPrint "Installing 'a section'"
    SectionEnd
    
    Section "another section"
        DetailPrint "Installing 'another section'"
    SectionEnd
SectionGroupEnd
