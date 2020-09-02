# BGFont [font_face [height [weight] [/ITALIC] [/UNDERLINE] [/STRIKE]]]
;
; Specifies the font used to show the text on the background gradient.
; To set the color use BGGradient. This will show a full screen window on DESKTOP.
; The default font will be used if no parameter are specified.

Name "Testing BGFont"

BGGradient "0x4037da" "0xd5633b" textcolor
BGFont "Arial" 34 /ITALIC

Page directory
Page instfiles
    
Section
    DetailPrint "What Font is this?"
SectionEnd