; ${__PAGEEX__}
;
; Defined as the page type in PageEx scope.

!ifdef __PAGEEX__
    !error "this shouldn't be here!"
!endif

PageEx instfiles
    !ifndef __PAGEEX__
        !error "missing predefine!"
    !endif

    !if ${__PAGEEX__} != instfiles
        !error "wrong page type"
    !endif
PageExEnd