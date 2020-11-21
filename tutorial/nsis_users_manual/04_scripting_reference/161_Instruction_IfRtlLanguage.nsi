; IfRtlLanguage  jump_if_true  [jump_if_false]
;
; Checks if active language is a RTL language.

Section
    IfRtlLanguage 0 +3
        MessageBox MB_OK "IfRtlLanguage is true"
    Goto end
        MessageBox MB_OK "IfRtlLanguage is false"
    end:
SectionEnd