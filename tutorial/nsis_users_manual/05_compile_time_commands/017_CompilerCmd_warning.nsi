; !warning  [message]
;
; This command will issue a warning to the script compiler. 
; You can also add a message to this warning.

!define USE_DANGEROUS_STUFF

!ifdef USE_DANGEROUS_STUFF
  !warning "using dangerous stuff"
!endif


; default
Section
SectionEnd


; compiler output

; !define: "USE_DANGEROUS_STUFF"=""
; warning: !warning: using dangerous stuff