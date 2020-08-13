
### Script Execution
#   * When a user runs an installer or uninstaller, pages are displayed in
#       the order they are defined in the script.
#   * When the Page instfiles is reached, sections corresponding to the selected
#       components, are executed in the order they were defined in the script.
#   * If the Page components is not displayed then all sections are executed
#       assuming they were not unselected or somehow disabled by the script.
#   * Beside code in sections, there's also code in callback functions.
#       If defined they might be executed before the sections code.


Section "Section A"
    DetailPrint "Executing Section A"
SectionEnd

Section "Section B"
    DetailPrint "Executing Section B"
SectionEnd