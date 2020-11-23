; !makensis  parameters [compare comparevalue | symbol]
;
; This command will !execute a new instance of MakeNSIS with the parameters you specify.

!makensis '-DGENERATEUNINST "${__FILE__}"' = 0
!system '"signtool" sign ...' = 0
