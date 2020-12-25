; ${__COUNTER__}
;
; Expands to a number (Starting at 0 and incrementing by 1 every time it is used)

!echo "first  __COUNTER__ value is ${__COUNTER__}"
!echo "do something ..."
!echo "second __COUNTER__ value is ${__COUNTER__}"


; default
Section
SectionEnd


; compiler output

;first  __COUNTER__ value is 1
;do something ...
;second __COUNTER__ value is 2