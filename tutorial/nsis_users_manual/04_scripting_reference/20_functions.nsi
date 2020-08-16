# Functions
;   * Functions are similar with Sections in that they contain zero ore more
;     instructions.
;   * User functions are not called by the installer directly, instead they are
;     called from Sections using the Call instruction
;   * Callback functions will be called by the installer when a certain event occurs

Function aUserFunction
    DetailPrint "Inside aUserFunction"
FunctionEnd

Section
    Call aUserFunction
SectionEnd
