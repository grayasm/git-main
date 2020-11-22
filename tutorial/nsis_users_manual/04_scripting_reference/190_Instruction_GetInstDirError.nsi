; GetInstDirError  user_var(error output)
;
; Use in the leave function of a directory page. 
; Reads the flag set if 'DirVerify leave' is used. Possible values:
;       0: No error
;       1: Invalid installation directory
;       2: Not enough space on installation drive

!include LogicLib.nsh
PageEx directory
    DirVerify leave
    PageCallbacks "" "" dirLeave
PageExEnd

Function dirLeave
    GetInstDirError $0
    ${Switch} $0
        ${Case} 0
            MessageBox MB_OK "Valid installation directory."
        ${Break}
        ${Case} 1
            MessageBox MB_OK "Invalid installation directory!"
            Abort
        ${Break}
        ${Case} 2
            MessageBox MB_OK "Not enough free space!"
            Abort
        ${Break}
    ${EndSwitch}
FunctionEnd

InstallDir "F:\temp" ; force invalid path
Page instfiles
Section
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd

