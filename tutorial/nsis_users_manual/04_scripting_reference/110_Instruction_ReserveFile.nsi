; ReserveFile [/nonfatal] [/r] [/x file|wildcard [...]] file [file...] | [/nonfatal] /plugin file.dll
;
; Reserves a file in the data block for later use.
; Files are added to the data block in the order they appear in the script.
; However if the extraction is "out of order", e.g. last function in the
; script needs to execute early then the installation time can double.
; All previous files needs to be unpacked to temporary location until the 
; required file is met and copied to destination.
; https://nsis-dev.github.io/NSIS-Forums/html/t-293390.html
; For example files extracted in your ".onInit" function should be reserved.
; File extracted only in normal "Section" blocks shouldn't be reserved.


InstallDir "$DOCUMENTS\MyApp"

ReserveFile 110_Instruction_ReserveFile.nsi

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    File /nonfatal "1GB worth of files"
SectionEnd

Function .onInit
    File "/oname=$INSTDIR\ReservedFile.nsi" 110_Instruction_ReserveFile.nsi
FunctionEnd
