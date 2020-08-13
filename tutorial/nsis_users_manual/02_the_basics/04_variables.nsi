
### Variables declared with Var
# You can declare your own variables ($VARNAME) with the Var command.
# Variables are global and can be used in any Section or Function.

Var BLA                 ; declare the variable

Section bla
    StrCpy $BLA "123"   ; Now you can use the variable $BLA
    DetailPrint "$$BLA value is $BLA"
SectionEnd


### Variables on the stack (LIFO)
# In addition there is a stack, which can also be used for temporary storage.
# To access the stack use the commands Push and Pop.
# For shared code, there are 20 registers available ($0 $1 .. $9 $R0 $R1 .. $R9)
# https://nsis.sourceforge.io/Docs/Chapter4.html#varother
# These static variables don't have to be declared and you won't get any name
# conflicts. Always restore the register to previous value after use.

Function bla
    Push $R0
    Push $R1
    
    ; .... code ...
    
    Pop $R1
    Pop $R0
FunctionEnd