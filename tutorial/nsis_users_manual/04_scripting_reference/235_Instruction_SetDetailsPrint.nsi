; SetDetailsPrint  none | listonly | textonly | both | lastused
;
; Sets mode at which commands print their status. 
;       none has commands be quiet
;       listonly has status text only added to the listbox
;       textonly has status text only printed to the status bar
;       both enables both (the default)

; For extracting many small files, textonly is recommended,
; especially on Win9x with smooth scrolling enabled.


InstallDir $DOCUMENTS\MyApp

Page instfiles

Section
    DetailPrint "progress 30%"
    Sleep 1000
    DetailPrint "progress 60%"
    Sleep 1000
    DetailPrint "progress 100%"   
SectionEnd

Function .onInit
    SetDetailsPrint textonly
FunctionEnd