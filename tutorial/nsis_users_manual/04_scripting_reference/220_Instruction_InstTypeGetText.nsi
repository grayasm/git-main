; InstTypeGetText  inst_type_idx  user_var
;
; Gets the text of the specified InstType.

InstallDir $DOCUMENTS\MyApp

InstType a
InstType b


Page directory
Page components
Page instfiles


Section section1
    SectionIn 1
    DetailPrint "Installing section1"
SectionEnd
Section section2
    SectionIn 2
    DetailPrint "Installing section2"
SectionEnd

Function .onInit
  InstTypeGetText 0 $0
  MessageBox MB_OK "First InstType is $0"       ; prints 'a'
  InstTypeGetText 1 $0
  MessageBox MB_OK "Second InstType is $0"      ; prints 'b'
FunctionEnd