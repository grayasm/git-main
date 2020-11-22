; GetCurInstType  user_var
;
; Get the current InstType and stores it in user_var. 
; If the first install type is selected, 0 will be put in user_var.
; If the second install type is selected, 1 will be put in user_var, and so on.
; The value of ${NSIS_MAX_INST_TYPES} (32 by default) means that the user 
; selected a custom set of sections.
; Simply selecting "Custom" in the drop-down menu is not enough to trigger this.
; The value is calculated by the sections actually selected.


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

Function .onSelChange
    GetCurInstType $0       ; << GetCurInstType
    DetailPrint "$$0=$0"
    
    IntCmp $0 0 full end +1
    IntCmp $0 1 standard end +1
    IntCmp $0 2 minimal end +1
    IntCmp $0 32 custom end +1
    Goto end
full:
    MessageBox MB_OK "GetCurInstType Full"
    Goto end
standard:
    MessageBox MB_OK "GetCurInstType Standard"
    Goto end
minimal:
    MessageBox MB_OK "GetCurInstType Minimal"
    Goto end
custom:
    MessageBox MB_OK "GetCurInstType Custom"
    Goto end
end:
FunctionEnd