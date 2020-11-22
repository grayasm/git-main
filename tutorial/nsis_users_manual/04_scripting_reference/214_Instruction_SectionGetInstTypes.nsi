; SectionGetInstTypes  section_index  user_var(output)
;
; Retrieves the install types flags array of a section. 
; The error flag will be set if the section index is out of range.


InstallDir $DOCUMENTS\MyApp

InstType "Full"             ; install type 1
InstType "Standard"         ; install type 2
InstType "Minimal"          ; install type 3

Page directory
Page components
Page instfiles

SectionGroup "Group"
    Section section1 SEC01
        DetailPrint "Installing section 1"
    SectionEnd
    Section section2 SEC02
        DetailPrint "Installing section 2"
    SectionEnd
    Section section3 SEC03
        DetailPrint "Installing section 3"
    SectionEnd
SectionGroupEnd


Function .onInit
    # associate section 'SEC01' with installation types 1,2,3, on top of its existing associations
    SectionGetInstTypes ${SEC01} $1
    IntOp $1 $1 | 7                     ; 7 = binary 0111
    SectionSetInstTypes ${SEC01} $1
    
    # associate section 'SEC02' with installation types 1,2, on top of its existing associations
    SectionGetInstTypes ${SEC02} $2
    IntOp $2 $2 | 3                     ; 3 = binary 0011
    SectionSetInstTypes ${SEC02} $2
    
    # associate section 'SEC03' with installation types 1 on top of its existing associations
    SectionGetInstTypes ${SEC03} $3
    IntOp $3 $3 | 1                     ; 1 = binary 0001
    SectionSetInstTypes ${SEC03} $3
FunctionEnd