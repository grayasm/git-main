; FileWriteUTF16LE  [/BOM]  handle  string
;
; This function is only available when building a Unicode installer.

; Writes a Unicode (UTF-16LE) string to a file opened with FileOpen. 
; If an error occurs, the error flag will be set.
; A BOM can be added to empty files with /BOM.

Unicode true

InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    FileOpen $0  $INSTDIR\file.dat  w
    IfErrors done
    FileWriteUTF16LE $0 "some text"
    FileClose $0
done:
SectionEnd