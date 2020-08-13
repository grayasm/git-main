### Debugging Scripts
# The more you work with NSIS the more complex the scripts will become.
# This will increase the potential of mistakes especially when dealing with lots
# of variables. There are a few possibilities to help you debugging the code.
#   1. print the value of the variable (MessageBox, DetailPrint)
#   2. using DumpState plug-in: https://nsis.sourceforge.io/DumpState
#      by default all actions of the Installer are printed out in the Log Window
#   3. dump to log file:
#      https://nsis.sourceforge.io/Docs/AppendixD.html#dumplogtofile

Section
    Push $0
    StrCpy $0 "The value of $$0 is $0"
    DetailPrint $0                      ; 1) MessageBox or DetailPrint
    Pop $0
SectionEnd