# ManifestDPIAware notset|true|false
;
; Declare that the installer is DPI-aware. A DPI-aware application is not scaled
; by the DWM (DPI virtualization) so the text is never blurry.
; NSIS does not scale the bitmap used by the tree control on the component page
; and some plugins might have compatibility issues so make sure that you test
; your installer at the different DPI settings if you select true.

ManifestDPIAware true

AddBrandingImage left 100u

Page license setupBranding
Page directory
Page instfiles

Function setupBranding
    GetTempFileName $0
    File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\nsis3-metro.bmp"
    SetBrandingImage /RESIZETOFIT $0
    Delete $0
FunctionEnd

Section ""
    DetailPrint "Installing..."
SectionEnd