; InstTypeSetText  inst_type_idx  text
;
; Sets the text of the specified InstType. 
; If the text is empty then the InstType is removed.
; By using a previously unused inst_type_idx number you can create new InstTypes.
; To add/remove Sections to this new InstType see SectionSetInstTypes. 
; Unlike SectionIn the index is zero based, which means the first install 
; type's index is 0.


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
  # set first installation type's name to $WINDIR
  InstTypeSetText 0 $WINDIR
  # set second installation type's name to $TEMP
  InstTypeSetText 1 $TEMP
FunctionEnd