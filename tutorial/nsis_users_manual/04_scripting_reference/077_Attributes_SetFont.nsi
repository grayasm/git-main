; SetFont [/LANG=lang_id] font_face_name font_size
;
; Sets the installer font.
; Please remember that the font you choose must be present on the user's machine
; as well. Don't use rare fonts that only you have.

SetFont /LANG=${LANG_ENGLISH} "English Font" 9

Page license
Page directory
Page instfiles


Section 1
    DetailPrint "What's app English Font 9?"
SectionEnd