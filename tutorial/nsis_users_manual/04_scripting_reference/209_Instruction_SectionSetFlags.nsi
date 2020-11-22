; SectionSetFlags  section_index  section_flags
;
; Sets the section's flags. The flag is a 32-bit integer. 
; The first bit (lowest) represents whether the section is currently selected.
; The second bit represents whether the section is a section group .
; The third bit represents whether the section is a section group end.
; The fourth bit represents whether the section is shown in bold or not.
; The fifth bit represents whether the section is read-only.
; The sixth bit represents whether the section group is to be automatically expanded.
; The seventh bit is set for section groups which are partially selected.
; The eighth bit is internally used for partially selected section group toggling.
; The ninth bit is used for reflecting section name changes.
; The error flag will be set if an out of range section is specified.

; Each flag has a name, prefixed with `SF_`:

!define SF_SELECTED   1
!define SF_SECGRP     2
!define SF_SECGRPEND  4
!define SF_BOLD       8
!define SF_RO         16
!define SF_EXPAND     32
!define SF_PSELECTED  64

InstallDir $DOCUMENTS\MyApp

Page directory
Page components
Page instfiles

Section test test_section_id
SectionEnd

Function .onInit
  # set section 'test' as selected and read-only
  IntOp $0 ${SF_SELECTED} | ${SF_RO}
  SectionSetFlags ${test_section_id} $0
FunctionEnd