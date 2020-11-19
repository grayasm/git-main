; SetFileAttributes  filename  attribute1|attribute2|...
;
; Sets the file attributes of 'filename'.
; Valid attributes can be combined with | and are:
;
;       NORMAL or FILE_ATTRIBUTE_NORMAL (you can use 0 to abbreviate this)
;       ARCHIVE or FILE_ATTRIBUTE_ARCHIVE
;       HIDDEN or FILE_ATTRIBUTE_HIDDEN
;       OFFLINE or FILE_ATTRIBUTE_OFFLINE
;       READONLY or FILE_ATTRIBUTE_READONLY
;       SYSTEM or FILE_ATTRIBUTE_SYSTEM
;       TEMPORARY or FILE_ATTRIBUTE_TEMPORARY
;
; The error flag will be set if the file's attributes cannot be set
; (i.e. the file doesn't exist, or you don't have the right permissions). 
; You can only set attributes. It's not possible to unset them. 
; If you want to remove an attribute use NORMAL. This way all attributes are erased.
; This command doesn't support wildcards.


InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"

    ; You can check if exe is HIDDEN now.
    File 108_timeout.exe    
    SetFileAttributes $INSTDIR\108_timeout.exe FILE_ATTRIBUTE_HIDDEN
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd