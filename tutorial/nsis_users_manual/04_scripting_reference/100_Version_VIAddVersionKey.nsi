; VIAddVersionKey [/LANG=lang_id] keyname value
;
; Adds a string entry to the version information stored in the installer and
; uninstaller. These can be viewed in the File Properties Version or Details tab.
; /LANG=0 can be used to indicate a language neutral language id.
; keyname can be one of the following:
;       ProductName
;       Comments
;       CompanyName
;       LegalCopyright
;       FileDescription
;       FileVersion
;       ProductVersion
;       InternalName
;       LegalTrademarks
;       OriginalFilename
;       PrivateBuild
;       SpecialBuild

LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"
LangString Name ${LANG_ENGLISH} "English"

VIProductVersion 1.2.3.4
VIFileVersion 1.2.3.4

VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "Test Application"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "A test comment"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Fake company"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "Test Application is a trademark of Fake company"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "© Fake company"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "Test Application"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "1.2.3"


Section
SectionEnd