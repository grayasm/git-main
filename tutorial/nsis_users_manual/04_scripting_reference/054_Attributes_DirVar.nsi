# DirVar user_var(dir input/output)
;
; Specifies which variable is to be used to contain the directory selected.
; This variable should be initialized with a default value.
; This allows to easily create two different directory pages that will not
;   require you to move values in and out of $INSTDIR.
; The default variable is $INSTDIR.
; DirVar can only be used in PageEx for directory and uninstConfirm pages.

AddBrandingImage left 100u

Var INSTALL_DIRECTORY_1
Var INSTALL_DIRECTORY_2

Page license setupBranding
PageEx directory
    DirVar $INSTALL_DIRECTORY_1
PageExEnd
PageEx directory
    DirVar $INSTALL_DIRECTORY_2
PageExEnd
Page instfiles


Section
    ; SetOutPath $INSTALL_DIRECTORY_1
    ; SetOutPath $INSTALL_DIRECTORY_2
    DetailPrint "Install to $INSTALL_DIRECTORY_1"
    DetailPrint "Install to $INSTALL_DIRECTORY_2"
SectionEnd


Function setupBranding
    GetTempFileName $0
    File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\nsis3-metro.bmp"
    SetBrandingImage /RESIZETOFIT $0
    Delete $0
FunctionEnd