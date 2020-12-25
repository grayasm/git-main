; !tempfile symbol
;
; This command creates a temporary file. 
; It puts its path into a define, named symbol.


!macro AddBuildFile
!tempfile PACKHDRTEMP
!packhdr "${PACKHDRTEMP}" '"C:\Program Files\UPX\upx.exe" "${PACKHDRTEMP}"'
!tempfile FILE
!define /date DATE "%H:%M:%S %d %b, %Y"
!system 'echo built on ${DATE} > "${FILE}"'
!undef DATE
File /oname=build.txt "${FILE}"
!delfile "${FILE}"
!undef FILE
!macroend


InstallDir "$DOCUMENTS\MyApp"

Page license
Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
    !insertmacro AddBuildFile
SectionEnd

Section Uninstall
    RMDir /R $INSTDIR
SectionEnd
