; SetCurInstType  inst_type_idx
;
; Sets the current InstType. 
; inst_type_idx should be between 0 and 31. 
; The error flag is not set if an out of range InstType was used.


InstallDir $DOCUMENTS\MyApp

InstType "Full"             ; install type 1
InstType "Standard"         ; install type 2
InstType "Minimal"          ; install type 3

Page directory
Page components
Page instfiles

SectionGroup "Group"
    Section section1 SEC01
        SectionIn 1 2 3
        DetailPrint "Installing section1"
    SectionEnd
    Section section2 SEC02
        SectionIn 1 2
        DetailPrint "Installing section2"
    SectionEnd
    Section section3 SEC03
        SectionIn 1
        DetailPrint "Installing section3"
    SectionEnd
SectionGroupEnd

Function .onInit
    SetCurInstType 1 ; Standard
FunctionEnd