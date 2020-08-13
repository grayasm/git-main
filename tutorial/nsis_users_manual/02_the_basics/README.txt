Cap.2 The Basics

2.1.    Introduction
2.2.    Script Files
    Generic view on NSIS header (.nsh) and script (.nsi) files.
    Break a command on muliple lines, include headers, declare strings and
    escape a character in a string using $
        01_sample_script_file.nsh   (header)
        01_sample_script_file.nsi   (script)
    
2.3.    Scripting structure
    Generic overview on NSIS script structure.
    Touches on Installer Attributes, Pages, Sections/Functions, Compiler Commands
        02_scripting_structure.nsi
    Generic overview of the logical code structures using:
        If,ElseIf,Else,EndIf,
        Switch,Case,Break,Default,EndSwitch
        If,AndIf,EndIf
        While,EndWhile
        For,Next
        Do,LoopUntil
        03_logical_code_structures.nsi
    Generic overview of variables declared with Var or on the stack (registers).
        04_variables.nsi
    How to debug scripts (DetailPrint, DumpState plug-in or dump log to a file)
        05_debugging_scripts.nsi
    Generic overview of the order of execution.
        Pages are displayed in the order they were defined in the script.
        Page components shows all Sections defined in the script.
        Page instfile execute all selected Sections in the order they were defined.
        06_script_execution.nsi
    Compiler commands are executed at compile time (evaluate constants,
        insert code via macro expansion, etc).
        07_compiler_commands.nsi
    Compiler for NSIS is makensis.exe and GUI is makensisw.exe
        08_compiler.bat
        08_compiler.nsi
    Modern UI has an interface like wizards of recent Windows versions.
        09_modern_ui.nsi
    Plug-ins are dlls compiled in C/C++/etc. They export methods with or without
        parameters and are called from the script file with a syntax like:
        DLLName::FunctionName "param 1" "param 2" "param 3"
        10_plugin.nsi (and 10_plugin directory for C++ code)
    
