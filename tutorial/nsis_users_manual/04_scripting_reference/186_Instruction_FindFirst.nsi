; FindFirst  user_var(handle output)  user_var(filename output)  filespec
;
; Performs a search for 'filespec', placing the first file found
; in filename_output (a user variable). 
; It also puts the handle of the search into handle_output (also a user variable). 
; If no files are found, both outputs are set to empty and the error flag is set.
; FindClose must be used to close the handle. 
; Note that the filename output is without path.


InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    ; create 5 .txt files
    StrCpy $R0 0
begin:
    FileOpen $0 $INSTDIR\file$R0.txt w
    FileClose $0
    IntOp $R0 $R0 + 1
    IntCmp $R0 5 end begin end
end:

    Call find_func
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd

Function find_func
    FindFirst $0 $1 $INSTDIR\*.txt      ; << FindFirst
loop:
    StrCmp $1 "" done
    DetailPrint $1
    FindNext $0 $1                      ; << FindNext
    Goto loop
done:
    FindClose $0                        ; << FindClose
FunctionEnd