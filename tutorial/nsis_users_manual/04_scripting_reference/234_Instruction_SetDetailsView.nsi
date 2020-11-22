; SetDetailsView  show | hide
;
; Shows or hides the details on the InstFiles page.
; Overrides the default details view, which is set via ShowInstDetails.

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
    SetDetailsView hide
FunctionEnd