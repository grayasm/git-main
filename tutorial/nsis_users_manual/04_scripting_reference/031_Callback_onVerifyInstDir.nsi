# .onVerifyInstDir (install callback)
;
; Controls whether installation path is valid or not for the installer.
; Called every time the user changes the install directory.
; Do not call MessageBox or anything crazy from this callback.
; If calls Abort the installation path in $INSTDIR is deemed invalid.

InstallDir $EXEPATH

Function .onVerifyInstDir
    IfFileExists $INSTDIR\31_callback_onverifyinstdir.exe PathGood
        Abort ; if condition is not satisfied, don't let us install there
    PathGood:
FunctionEnd

Page directory
Page instfiles

Section
SectionEnd