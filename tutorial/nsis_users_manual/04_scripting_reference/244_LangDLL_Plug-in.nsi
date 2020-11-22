; 4.10.2 LangDLL Plug-in
; The LangDLL plug-in allows you to give the user an option to choose the language of the installer.
; Just push the language id (${LANG_langfile}) and its name for every language in your installer, 
; then the number of languages pushed, the caption, and the text that tells the user to select the language, 
; call the plug-in function named LangDialog, pop the returned value into $LANGUAGE and you're good to go.
; If the user clicks on the cancel button the return value will be "cancel".

; For an example of usage see languages.nsi.