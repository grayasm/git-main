# Page Options


Page license
Page components
Page directory
Page instfiles



# License page
LicenseText "Text above the controls, to the right of the installation icon."   "I agree btn"
LicenseData 007_licdata.txt
LicenseForceSelection radiobuttons "I accept" "I decline"


# Components selection page
ComponentText "Text above the controls, to the right of the installation icon" \
    "Text next to the installation type selection" \
    "Text to the left of the components list and below the installation type"

# Directory selection page
DirText "Text above the controls, to the right fo the installation icon" \
    "Text on the directory selection frame" \
    "Browse btn" \
    "Text on the $\"Browse For Folder$\" dialog, appears after clicking on $\"Browse$\" button"

; DirVar user_var(dir input/output)
; Allows to create two different directory pages that will not require you to 
; move values in and out of $INSTDIR
; Can only be used in PageEx.
Var ANOTHER_DIR
PageEx directory
    DirVar $ANOTHER_DIR
    DirVerify leave
PageExEnd

; DirVerify auto | leave
; DirVerify leave : will not check if the installation directory is valid or
;                   if there is enough space. The Next button will be active.

# Un/Installation log page
; Replaces the default details button text of "Show details" if parameter
; is specified (otherwise the default is used)."
DetailsButtonText "Show details btn"
; Replaces the default text ("Completed") that is printed at the end 
; of the install if parameter is specified. Otherwise, the default is used.
CompletedText "Replaces the default text ($\"Completed$\")"


Section 1
SectionEnd
