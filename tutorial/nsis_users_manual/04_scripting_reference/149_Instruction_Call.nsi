; Call  function_name  | :label_name | user_var(input)
;
; Calls the function named function_name or the label named label_name or
; a variable that specifies an address. 
; An address is returned by GetCurrentAddress, GetFunctionAddress or 
; GetLabelAddress. A call returns when it encounters a Return instruction. 
; Sections and functions are automatically ended with a Return instruction. 
; Uninstall functions cannot be called from installer functions and sections, 
; and vice-versa.

Function func
  Call :label
  DetailPrint "#1: This will only appear 1 time."
label:
  DetailPrint "#2: This will appear before and after message #1."
  Call :.global_label
FunctionEnd

Section
  Call func
  Return

.global_label:
  DetailPrint "#3: The global label was called"
SectionEnd

; #2: This will apear before and after message #1.
; #3: The global label was called
; #1: This will only appear 1 time.
; #2: This will appear before and after message #1.
; #3: The global label was called
; Completed