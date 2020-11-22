; LoadLanguageFile  language_file.nlf
;
; Loads a language file for the construction of a language table. 
; All of the language files that ship with NSIS are in Contrib\Language Files

; After you have inserted the language file ${LANG_langfile} will be defined
; as the language id (for example, ${LANG_ENGLISH} will be defined as 1033).
; Use it with LangString, LicenseLangString, LangDLL and VIAddVersionKey.


Page license
Page components
Page instfiles

; First is default
LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\German.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Russian.nlf"

; License data
; Not exactly translated, but it shows what's needed
LicenseLangString myLicenseData ${LANG_ENGLISH} "239_common_license.nsi"
LicenseLangString myLicenseData ${LANG_GERMAN} "239_common_license.nsi"
LicenseLangString myLicenseData ${LANG_RUSSIAN} "239_common_license.nsi"

LicenseData $(myLicenseData)


; Set name using the normal interface (Name command)
LangString Name ${LANG_ENGLISH} "English"
LangString Name ${LANG_GERMAN} "German"
LangString Name ${LANG_RUSSIAN} "Russian"

Name $(Name)


; Directly change the inner lang strings (Same as ComponentText)
LangString ^ComponentsText ${LANG_ENGLISH} "English component page"
LangString ^ComponentsText ${LANG_GERMAN} "German component page"
LangString ^ComponentsText ${LANG_RUSSIAN} "Russian component page"

; Set one text for all languages (simply don't use a LangString)
CompletedText "Languages example completed"

; A LangString for the section name
LangString Sec1Name ${LANG_ENGLISH} "English section #1"
LangString Sec1Name ${LANG_GERMAN} "German section #1"
LangString Sec1Name ${LANG_RUSSIAN} "Russian section #1"

; A multilingual message
LangString Message ${LANG_ENGLISH} "English message"
LangString Message ${LANG_GERMAN} "German message"
LangString Message ${LANG_RUSSIAN} "Russian message"

;Section names set by Language strings
;It works with ! too
Section !$(Sec1Name) sec1
	MessageBox MB_OK $(Message)
SectionEnd

; The old, slow, wasteful way
; Look at this section and see why LangString is so much easier
Section "Section number two"
	StrCmp $LANGUAGE ${LANG_ENGLISH} 0 +2
		MessageBox MB_OK "Installing English stuff"
	StrCmp $LANGUAGE ${LANG_GERMAN} 0 +2
		MessageBox MB_OK "Installing German stuff"
	StrCmp $LANGUAGE ${LANG_RUSSIAN} 0 +2
		MessageBox MB_OK "Installing Russian stuff"
SectionEnd

Function .onInit
	;Language selection dialog
	Push ""
	Push ${LANG_ENGLISH}
	Push English
	Push ${LANG_GERMAN}
	Push German
	Push ${LANG_RUSSIAN}
	Push Russian
	Push A ; A means auto count languages
	       ; for the auto count to work the first empty push (Push "") must remain
	LangDLL::LangDialog "Installer Language" "Please select the language of the installer"

	Pop $LANGUAGE
	StrCmp $LANGUAGE "cancel" 0 +2
		Abort
FunctionEnd