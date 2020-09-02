# CompletedText text
;
; Replaces the default text "Completed" that is printed at the end of the
; install if parameter is specified.

CompletedText "Completed 100%"

InstallDir "$PROGRAMFILES64\MyApp"

Page license
Page directory
Page components
Page instfiles

Section Programs
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Manual
SectionEnd

Section Uninstall
    delete "$INSTDIR\uninstall.exe"
    rmDir $INSTDIR
SectionEnd