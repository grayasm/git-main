# .onMouseOverSection (install callback)

;   * called whenever the mouse position over the sections tree has changed
;   * allows to set a description for each section
;   * section id is stored temporarily in $0

Function .onMouseOverSection
    FindWindow $R0 "#32770" "" $HWNDPARENT
    GetDlgItem $R0 $R0 1043  ; description item must be added to the UI
    
    StrCmp $0 0 "" +2
        SendMessage $R0 ${WM_SETTEXT} 0 "STR: first section description"

    StrCmp $0 1 "" +2
        SendMessage $R0 ${WM_SETTEXT} 0 "STR: second section description"
FunctionEnd


Page components
Page instfiles

SectionGroup "some stuff"
    Section "a section"
        DetailPrint "Installing 'a section'"
    SectionEnd

    Section "another section"
        DetailPrint "Installing 'another section'"
    SectionEnd
SectionGroupEnd
