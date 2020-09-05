# DirText [text] [subtext] [browse_button_text] [browse_dlg_text]
;
; Used to change the default text on the directory page.
; text: Text above the controls, to the right of the installation icon.
; subtext: Text on the directory selection frame.
; browse_button_text: Text on the browse button.
; browse_dlg_text: Text on the "Browse For Folder" dialog, appears after
;                  clicking on "Browse" button.
; Accepts variables.


DirText "Custom directory page!"


AddBrandingImage left 100u

Page license licenseImage
Page custom customPage
Page directory dirImage
Page instfiles instImage
; -----------------------

Function licenseImage
	GetTempFileName $0
	File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\nsis3-vintage.bmp"
	SetBrandingImage /RESIZETOFIT $0
	Delete $0
FunctionEnd

Function customPage
    MessageBox MB_OK "Before executing the custom page!"
    
    GetTempFileName $0
	File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\nsis3-metro.bmp"
	SetBrandingImage /RESIZETOFIT $0
	Delete $0
    
    MessageBox MB_OK "After executing the custom page!"
FunctionEnd

Function dirImage
    GetTempFileName $0
	File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\nsis3-branding.bmp"
	SetBrandingImage /RESIZETOFIT $0
	Delete $0
FunctionEnd

Function instImage
    GetTempFileName $0
	File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\nsis3-grey.bmp"
	SetBrandingImage /RESIZETOFIT $0
	Delete $0
FunctionEnd

Section ""
    MessageBox MB_OK "Before setting orange branding image"

	GetTempFileName $0
	File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\orange.bmp"
	SetBrandingImage /RESIZETOFIT $0
	Delete $0
SectionEnd



