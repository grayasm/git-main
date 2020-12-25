; ${__UNINSTALL__}
;
; Defined in section, function or PageEx scopes of the uninstaller.

!ifdef __UNINSTALL__
    !error "this shouldn't be here!"
!endif

Function test
    !ifdef __UNINSTALL__
        !error "this shouldn't be here!"
    !endif
FunctionEnd

Function un.test
    !ifndef __UNINSTALL__
        !error "missing predefine!"
    !endif
FunctionEnd