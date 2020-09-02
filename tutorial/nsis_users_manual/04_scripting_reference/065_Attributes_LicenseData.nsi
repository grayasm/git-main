# LicenseData licdata.(txt|rtf)
;
; Specifies a text file or a RTF file to use for the license that the user can read.
; The text file must be in DOS text format (\r\n).
; The RTF file must be edited with WordPad not MS Word.
; Use LicenseLangString to show a differet license for every language.


PageEx license
    LicenseText "Readme"
    LicenseData 011_license.rtf
PageExEnd

PageEx license
    LicenseData 011_license.txt
    LicenseForceSelection checkbox
PageExEnd


Section 1
SectionEnd
