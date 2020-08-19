# AddBrandingImage (installer attribute)
;
; AddBrandingImage (left|right|top|bottom) (width|height) [padding]
;
; Adds a branding image on the top, bottom, left or right of the installer.
; Its size will be set according to the width/height specified, the installer
; width/height and the installers font.
; The final size will not always be what you requested; see the output.
; It depends on the installer font therefore you SetFont before AddBrandingImage.
; The default padding value is 2.
; The numbers can be suffixed with u to specify dialog units instead of pixels.

AddBrandingImage top    170     0
AddBrandingImage left   0       0
AddBrandingImage right  0       0

Section
    SetBrandingImage 40_branding_image.bmp
SectionEnd
