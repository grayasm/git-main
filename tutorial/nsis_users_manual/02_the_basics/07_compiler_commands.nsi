
### Compiler Commands
# Compiler commands will be executed at compile time on your computer.
# They can be used for conditional compilation, to include header files,
# to execute applications, to change the working directory and more.
# The most common usage is defines, which are compile time constants.

!define VERSION "1.0.3"
Name "My Program ${VERSION}"
OutFile "My Program Installer - ${VERSION}.exe"

# Another common use is macros.
# Macros are used to insert code at compile time, depending on defines and
# using the values of the defines. The macro commands are inserted at compile
# time.
!macro MyFunc UN
Function ${UN}MyFunc
    ; 2 lines commented to avoid compile errors.
    ; Call ${UN}DoRegStuff
    ; ReadRegStr $0 HKLM Software\MyProgram key
    StrCpy $0 "inside ${UN}MyFunc"
    DetailPrint $0    
FunctionEnd
!macroend

!insertmacro MyFunc ""
!insertmacro MyFunc "un."

# The 2 !insertmacro insert 2 functions, one for the installer called MyFunc
# and one for the uninstaller called un.MyFunc
# https://nsis.sourceforge.io/Docs/Chapter5.html#compdefines

Section
    Call MyFunc
SectionEnd