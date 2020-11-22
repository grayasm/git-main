; FindClose handle
;
; Closes a search opened with FindFirst.

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