; ${__GLOBAL__}
;
; Defined in the global scope.

Section test
    !ifdef ${__GLOBAL__}
        !error "this shouldn't be here!"
    !endif
SectionEnd

PageEx instfiles
    !ifdef ${__GLOBAL__}
        !error "this shouldn't be here!"
    !endif
PageExEnd