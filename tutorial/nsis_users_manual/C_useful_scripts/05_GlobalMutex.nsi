; Prevent Multiple Instances

InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
SectionEnd

Function .onInit
    System::Call 'kernel32::CreateMutex(p 0, i 0, t "myMutex") p .r1 ?e'
    Pop $R0
 
    StrCmp $R0 0 +3
        MessageBox MB_OK|MB_ICONEXCLAMATION "The installer is already running."
    Abort
FunctionEnd
