# DirVerify auto|leave
;
; leave: the Next button will not be disabled if the installtion directory is
;        not valid or there is not enough space. You can use GetInstDirError
;        to read the error flag.

AddBrandingImage left 100u

PageEx directory
    DirVerify leave
    PageCallbacks dirPre "" dirLeave
PageExEnd
Page instfiles

Section ""
SectionEnd

Function dirPre
    GetTempFileName $0
    File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\nsis3-metro.bmp"
    SetBrandingImage /RESIZETOFIT $0
    Delete $0
FunctionEnd

Function dirLeave
    MessageBox MB_OK "dirLeave with INSTDIR=$INSTDIR"
FunctionEnd