Section
#   Logical Code Structures
#   Condionally executing code, or executing code in a loop can be done using
#   StrCmp, IntCmp, IfErrors, Goto and more.

StrCmp $0 'some value' 0 +3
    MessageBox MB_OK '$$0 is some value'
    Goto done

StrCmp $0 'some other value' 0 +3
    MessageBox MB_OK '$$0 is some other value'
    Goto done

# else
    MessageBox MB_OK '$$0 is "$0"'
done:

#   However the LogicLib.nsh header provides very simple macros that allow easy
#   construction of complex logical structures.
!include LogicLib.nsh

${If} $0 == 'some value'
    MessageBox MB_OK '$$0 is some value'

${ElseIf} $0 == 'some other value'
    MessageBox MB_OK '$$0 is some other value'

${Else}
    MessageBox MB_OK '$$0 is "$0"'

${EndIf}

#   The same can also be done using a switch, as shown in the following example.
${Switch} $0
    ${Case} 'some value'
        MessageBox MB_OK '$$0 is some value'
        ${Break}
    ${Case} 'some other value'
        MessageBox MB_OK '$$0 is some other value'
        ${Break}
    ${Default}
        MessageBox MB_OK '$$0 is "$0"'
        ${Break}
${EndSwitch}

# Multiple conditions are also supported. The following example will notify
# the user, if both $0 and $1 are empty.
${If} $0 == ''
${AndIf} $1 == ''
    MessageBox MB_OK|MB_ICONSTOP 'both are empty!'
${EndIf}

# The LogicLib removes the need for labels and relative jumps, thus prevents
# label name conflicts, and removes the need to manually adjust relative jump
# offsets every time the script is changed. It simplifies looping by supporting
# while, do and for loops. Example on how to count to 5.

StrCpy $R1 0
${While} $R1 < 5
    IntOp $R1 $R1 + 1
    DetailPrint $R1
${EndWhile}

${For} $R1 1 5
    DetailPrint $R1
${Next}

StrCpy $R1 0
${Do}
    IntOp $R1 $R1 + 1
    DetailPrint $R1
${LoopUntil} $R1 >= 5
    
SectionEnd

# More examples can be found in:
# https://nsis.sourceforge.io/Examples/LogicLib.nsi
















