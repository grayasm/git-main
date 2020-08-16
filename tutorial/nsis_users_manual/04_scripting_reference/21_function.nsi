# Function
; Function [function_name]

;   * functions beginning with . (.onInit) are generally reserved for callbacks
;   * functions beginning with .un will be generated in the Uninstaller
;     Hence, normal install Sections and functions cannot call uninstall functions
;     and the Uninstall Section and uninstall functions cannot call normal
;     functions.

Function aUserFunction
    DetailPrint "Inside aUserFunction"
FunctionEnd

Section
    Call aUserFunction
SectionEnd
