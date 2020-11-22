; SetBrandingImage  [/IMGID=item_id_in_dialog]  [/RESIZETOFIT]  path_to_bitmap_file.bmp
;
; Sets the current bitmap file displayed as the branding image.
; If no IMGID is specified, the first image control found will be used, 
; or the image control created by AddBrandingImage.

; Note that this bitmap must be present on the user's machine.
; Use File command to put the bitmap there first.

; If /RESIZETOFIT is specified the image will be automatically resized
; (very poorly) to the image control size. 
; If you used AddBrandingImage you can get this size by compiling your script
; and watching for AddBrandingImage output, it will tell you the size. 
; SetBrandingImage will not work when called from .onInit!


AddBrandingImage left 100u

InstallDir $DOCUMENTS\MyApp

Page directory setImage
Page instfiles setImage

Section
    DetailPrint "Installing section"
SectionEnd


Function setImage
    GetTempFileName $0
    File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\nullsoft.bmp"
    SetBrandingImage /RESIZETOFIT $0
    Delete $0
FunctionEnd