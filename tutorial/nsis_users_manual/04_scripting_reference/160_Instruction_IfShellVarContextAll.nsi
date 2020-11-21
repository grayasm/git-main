; IfShellVarContextAll  jump_if_true  [jump_if_false]
;
; Checks if SetShellVarContext is set to all


Section
    SetShellVarContext current
    StrCpy $0 $DESKTOP
    SetShellVarContext all
    StrCpy $1 $DESKTOP
    MessageBox MB_OK $0$\n$1
    
    IfShellVarContextAll 0 +3
        MessageBox MB_OK "IfShellVarContectAll is true"
    Goto end
        MessageBox MB_OK "IfShellVarContectAll is false"
    end:
SectionEnd

; C:\Users\mihai\Desktop
; C:\Users\Public\Desktop
; IfShellVarContectAll is true
