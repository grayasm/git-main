; LangString name language_id | 0 string
;
; Defines a multilingual string. 
; This means its value may be different for every language.
; It allows you to easily make your installer multilingual without the need 
; to add massive switches to the script.

; Each language string has a name that identifies it and a value for 
; each language used by the installer. They can be used in any runtime string 
; in the script. To use a language string all you need to add to the string
; is $(LangString_name_here) where you want the LangString to be inserted.

; see 239_Instruction_LoadLanguageFile.nsi
