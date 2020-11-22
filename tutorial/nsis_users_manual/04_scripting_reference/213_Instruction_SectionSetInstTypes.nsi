; SectionSetInstTypes  section_index  inst_types
;
; Sets the install types for the section specified by section_index.
; Note that the section index starts with zero. 
; Every bit of inst_types is a flag that tells if the section is in that 
; install type or not. 

; To enable a section for the install types 1 and 3 use bit flag 0x0101=5


InstallDir $DOCUMENTS\MyApp

InstType "Full"             ; install type 1
InstType "Standard"         ; install type 2
InstType "Minimal"          ; install type 3

Page directory
Page components
Page instfiles

SectionGroup "Group"
    Section section1 SEC01
        SectionIn 1 2 3     ; activ in 1,2,3
    SectionEnd
    Section section2 SEC02
        SectionIn 1 2 3     ; to be changed later to 1,2
    SectionEnd
    Section section3 SEC03
        SectionIn 1 2 3     ; to be changed later to 1
    SectionEnd
SectionGroupEnd


Function .onInit
    # associate SEC01 to installation type 1 2 3 BIN:0111 DEC:7 HEX:0x7
    SectionSetInstTypes ${SEC01}  7
    # associate SEC02 to installation type 1 2   BIN:0011 DEC:3 HEX:0x3
    SectionSetInstTypes ${SEC02}  3
    # associate SEC03 to installation type 1     BIN:0001 DEC:1 HEX:0x1
    SectionSetInstTypes ${SEC03}  1
FunctionEnd