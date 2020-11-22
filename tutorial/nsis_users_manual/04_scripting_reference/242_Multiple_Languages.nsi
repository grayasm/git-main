; 4.10 Multiple Languages
; As of version 2 NSIS fully supports multiple languages. 
; The interface of one installer can support multiple languages.

; Use LoadLanguageFile for every language to load the default interface texts and language properties. 
; Visit the NSIS translations forum for more information about creating new language files.

; The default interface texts can easily be changed using instructions like ComponentText etc.

; You can also use the contents of the standard language strings in your own strings
; (for example, $(^Name) contains the installer's name set using the Name instruction). 
; The names of all standard language strings are listed as comments just above the strings in the language files.
; The language files are located in Contrib\Language Files.

; To create your own language strings, use LangString.

; For an example of an installer with multiple languages, see languages.nsi.