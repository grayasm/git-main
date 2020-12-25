; $%envVarName%
;
; $%envVarName% will be replaced at compile time by the environment variable envVarName.

!echo "%TEMP% is $%TEMP%"


; default
Section
SectionEnd

; compiler output:

;%TEMP% is C:\Users\mihai\AppData\Local\Temp