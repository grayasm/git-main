; 4.10.3 RTL Languages
; RTL languages are languages that are written from right to left (e.g. Arabic and Hebrew).
; NSIS fully supports RTL languages. 
; In the language file there is a place to specify if the language is RTL or not.
; To find out at runtime if the current language is RTL or not, check the value of the $(^RTL) language string.
; It will be 1 if the language is RTL and 0 otherwise. 
; This can be useful when using plug-ins that create dialogs, they usually have RTL settings too.