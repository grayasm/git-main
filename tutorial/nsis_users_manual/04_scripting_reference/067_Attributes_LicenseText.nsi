# LicenseText [text [button_text]]
;
; Used to change the default text on the license page.
; text: Text above the controls to the right of the installation icon.
; button_text: Text on the "I Agree" button.


LicenseText "License"
LicenseData "011_license.txt"

Page license
Page instfiles

Section 1
    DetailPrint "Installing ..."
SectionEnd