; !searchreplace  [/ignorecase]  symbol_out  source_string  searchfor  replacewith
;
; Searches source_string, looking for searchfor and replacing all instances
; of it with replacewith.
; Unlike !define, !searchreplace allows you to redefine symbol_out without 
; warning or error.

# defines ${blah} to "i like ponies"
!define blah "i like ponies"
!searchreplace blah "i love ponies" "love" "like"
!echo "blah=${blah}"

; default
Section
SectionEnd

; compiler output:

;blah=i like ponies