; SectionGetText  section_index  user_var(output)
;
; Stores the text description of the section section_index into the output.
; If the section is hidden, stores an empty string. 
; The error flag will be set if an out of range section is specified.


InstallDir $DOCUMENTS\MyApp

Page directory
Page components
Page instfiles


Section test test_section_id
SectionEnd

Function .onInit
  # append $WINDIR to section's name
  SectionGetText ${test_section_id} $0
  StrCpy $0 "$0 - $WINDIR"
  SectionSetText ${test_section_id} $0
FunctionEnd