; SectionSetSize  section_index  new_size
;
; Sets the size of the section specified by section_index. 
; Note that the index starts with zero. 
; The Value for Size must be entered in KiloByte and supports only whole numbers.


Section test test_section_id
    DetailPrint "Installing section test"
SectionEnd

Function .onInit
  # set required size of section 'test' to 100 bytes
  SectionSetSize ${test_section_id} 100
FunctionEnd