; ${__SECTION__}
;
; Defined as the section name, without any prefixes, in section scope.

!ifdef __SECTION__
    !error "this shouldn't be here!"
!endif

Section test
    !ifndef __SECTION__
        !error "missing predefine!"
    !endif

    !if ${__SECTION__} != test
        !error "wrong predefine value!"
    !endif
SectionEnd

Section !test
    !if ${__SECTION__} != test
        !error "wrong predefine value!"
    !endif
SectionEnd

Section un.test
    !if ${__SECTION__} != test
        !error "wrong predefine value!"
    !endif
SectionEnd