; !error [message]
;
; This command will issue an error to the script compiler and will stop execution
; of the script. You can also add a message to this error.

!define VERSION 1.2
!define NOVERSION 0.0

!ifdef VERSION & NOVERSION
  !error "both VERSION and NOVERSION are defined"
!endif

Section
SectionEnd