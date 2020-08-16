# Sections
;
;   * each section contains zero or more instructions
;   * sections are executed in order by the resulting installer, and if a
;     component page is used, the user will have the option of disabling/enabling
;     each visible section
;   * if a section's name is "Uninstall" or is prefixed with "un." , it's an
;     uninstaller section.

Page license
Page components
Page directory
Page instfiles


Section programs
    DetailPrint "Installing programs"
SectionEnd

Section languages
    DetailPrint "Installing languages"
SectionEnd

Section help
    DetailPrint "Installing help"
SectionEnd

Section samples
    DetailPrint "Installing samples"
SectionEnd
