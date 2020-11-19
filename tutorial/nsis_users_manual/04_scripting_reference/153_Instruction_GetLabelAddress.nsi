; GetLabelAddress  user_var(output)  label
;
; Gets the address of the label and stores it in the output user variable.
; This user variable then can be passed to Call or Goto. 
; Note that you may only call this with labels accessible from your function,
; but you can call it from anywhere (which is potentially dangerous). 
; Note that if you Call the output of GetLabelAddress, code will be executed
; until it Return's (explicitly or implicitly at the end of a function), 
; and then you will be returned to the statement after the Call.


Section
    label:
    DetailPrint "label"
    GetLabelAddress $0 label
    IntOp $0 $0 + 4
    Goto $0
    DetailPrint "done"
SectionEnd

; label
; done
; Completed