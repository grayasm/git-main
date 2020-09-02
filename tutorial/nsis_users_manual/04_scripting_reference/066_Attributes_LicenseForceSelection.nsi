# LicenseForceSelection (checkbox [accept_text] | radiobuttons [accept_text] [decline_text] | off)
;
; Specifies if the displayed license must be explicitly accepted or not.
; This can be done either by a checkbox or by radiobuttons.
; By default the "next button" is disabled and will only be enabled if
; the checkbox is enabled or the correct radio button is selected.


PageEx license
    LicenseText "Readme"
    LicenseData 011_license.txt
    LicenseForceSelection checkbox
PageExEnd

PageEx license
    LicenseText "Readme"
    LicenseData 011_license.txt
    LicenseForceSelection checkbox "I accept"
PageExEnd

PageEx license
    LicenseText "Readme"
    LicenseData 011_license.txt
    LicenseForceSelection radiobuttons
PageExEnd

PageEx license
    LicenseText "Readme"
    LicenseData 011_license.txt
    LicenseForceSelection radiobuttons "I accept"
PageExEnd

PageEx license
    LicenseText "Readme"
    LicenseData 011_license.txt
    LicenseForceSelection radiobuttons "I accept" "I decline"
PageExEnd

PageEx license
    LicenseText "Readme"
    LicenseData 011_license.txt
    LicenseForceSelection radiobuttons "" "I decline"
PageExEnd

PageEx license
    LicenseText "Readme"
    LicenseData 011_license.txt
    LicenseForceSelection off
PageExEnd

Page instfiles

Section 1
    DetailPrint "Installing ..."
SectionEnd
