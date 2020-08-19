# AutoCloseWindow true|false
;
; Sets whether or not the install window automatically closes when completed.
; This is overrideable from a section using SetAutoClose.

AutoCloseWindow true

Page license
Page directory
Page instfiles

Section install
    MessageBox MB_OK "Installer will automatically close now."
SectionEnd