; SectionGetSize  section_index  user_var
;
; Gets the size of the section specified by section_index and stores
; the value in the given user variable.
; Note that the index starts with zero. 
; The error flag will be set if the section index is out of range.


Section test test_section_id
    DetailPrint "Installing section test"
SectionEnd

Function .onInit
  # increase required size of section 'test' by 100 KiB
  SectionGetSize ${test_section_id} $0
  IntOp $0 $0 + 100
  SectionSetSize ${test_section_id} $0
FunctionEnd