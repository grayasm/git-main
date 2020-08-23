# FileErrorText file_error_text [noignore_file_error_text]
;
; Replaces the default text that comes up when a file cannot be writte to.
; This string contain a reference to $0, which is the filename.
; $0 is temporarily changed to thsi value.

FileErrorText "Can not write to file $\r$\n$0"

; force error by attempting to create c:\file.txt
RequestExecutionLevel user
Section
    SetOutPath "C:\"
    File "/oname=file.txt" "56_attributes_fileerrortext.nsi"
SectionEnd