; SectionSetText  section_index  section_text
;
; Sets the description for the section section_index. 
; If the text is set to "" then the section will be hidden. 
; The error flag will be set if an out of range section is specified.


InstallDir $DOCUMENTS\MyApp

Page directory
Page components
Page instfiles


Section "" test_section_id
SectionEnd

Function .onInit
  # change section's name to $WINDIR
  SectionSetText ${test_section_id} $WINDIR
FunctionEnd