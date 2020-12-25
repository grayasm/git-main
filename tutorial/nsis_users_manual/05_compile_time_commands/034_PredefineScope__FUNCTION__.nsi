; ${__FUNCTION__}
;
; Defined as the function name, without any prefixes, in function scope.

!ifdef __FUNCTION__
    !error "this shouldn't be here!"
!endif

Function test
    !ifndef __FUNCTION__
        !error "missing predefine!"
    !endif

    !if ${__FUNCTION__} != test
        !error "wrong predefine value!"
    !endif
FunctionEnd

Function un.test
    !if ${__FUNCTION__} != test
        !error "wrong predefine value!"
    !endif
FunctionEnd