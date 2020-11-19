; GetFullPathName  [/SHORT]  user_var(output)  path_or_file
;
; Assign the full path of the file specified to user variable $x.
; If the path is not found $x will be empty. 
; If /SHORT is specified, the path is converted to the short filename form.
; To get the long filename, call GetLongPathName using the System plug-in.



Section
    StrCpy $INSTDIR $DOCUMENTS\MyApp
    SetOutPath $INSTDIR
    GetFullPathName $0 ..
    DetailPrint "dir .. = $0"

    GetFullPathName /SHORT $0 $INSTDIR
    DetailPrint "dir .. /SHORT = $0"
    StrCpy $0 C:\Users\mihai\Docume~1\MyApp
    System::Call 'kernel32::GetLongPathName(t r0, t .r1, i ${NSIS_MAX_STRLEN}) i .r2'
    StrCmp $2 error +2
    StrCpy $0 $1
    DetailPrint "kernel32::GetLongPathName = $0"
SectionEnd