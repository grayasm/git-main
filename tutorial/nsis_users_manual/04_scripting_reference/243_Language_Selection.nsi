; 4.10.1 Language Selection
; When the installer starts up it goes through these steps to select the interface language:

; Get user's default Windows UI language
; Find a perfect match for the language
; If there is no perfect match, find a primary language match
; If there is no match, use the first language defined in the script 
; (make sure your first language is a common one like English)
; If the language variable $LANGUAGE has changed during .onInit, NSIS goes through steps 2 to 4 again.