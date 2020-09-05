# SectionInstType
; SectionInstType insttype_index [insttype_index [...]] [RO]

; This command specifies which install types the current section default to
; the enabled state in. If you specify RO as a parameter then the section
; will be read-only, meaning the user won't be able to change its state.

InstType "Full"     IT_FULL
InstType "Minimal"  IT_MIN

Section "Help"
    SectionInstType ${IT_FULL} ${IT_MIN}
SectionEnd

Section "Bonus content"
    SectionInstType ${IT_FULL}
SectionEnd

