
### Compiler
# To create the installer you need to compile your script.
# MakeNSIS.exe is the NSIS compiler.
# MakeNSISW.exe is the NSIS Compiler Interface (GUI)

DirText "The default text on the directory page"
DirText "2nd DirText will give a warning in the compiler output"

Page components
Page directory
Page instfiles

Section
SectionEnd