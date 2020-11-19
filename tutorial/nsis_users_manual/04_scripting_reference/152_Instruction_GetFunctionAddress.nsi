; GetFunctionAddress  user_var(output)  function_name
;
; Gets the address of the function and stores it in the output user variable.
; This user variable then can be passed to Call or Goto. 
; Note that if you Goto an address which is the output of GetFunctionAddress, 
; your function will never be returned to
; (when the function you Goto'd to returns, you return instantly).

Function func
    DetailPrint "function"
FunctionEnd

Section
    GetFunctionAddress $0 func
    Call $0
SectionEnd