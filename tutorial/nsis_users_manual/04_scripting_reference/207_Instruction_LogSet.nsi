; LogSet on | off
;
; Sets whether install logging to $INSTDIR\install.log will happen.
; $INSTDIR must have a value before you call this function or it will not work.
; Note that the NSIS_CONFIG_LOG build setting must be set 
; (scons NSIS_CONFIG_LOG=yes) when building (it is not set by default) 
; to support this. 
; See Building NSIS for more information about recompiling NSIS.

InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    LogSet on
    WriteUninstaller $INSTDIR\uninstall.exe
    File 207_Instruction_LogSet.nsi
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd

; Error: LogSet specified, NSIS_CONFIG_LOG not defined.