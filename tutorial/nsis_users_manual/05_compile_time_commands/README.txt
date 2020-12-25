    Cap.5 Compile Time Commands

    Compiler Utility Commands
        These commands are similar to the C preprocessor macro instructions.
        !include    !includedir     !addplugindir   !appendfile
        !cd         !delfile        !echo           !error
        !execute    !makensis       !packhdr        !finalize
        !system     !tempfile       !getdllversion  !gettlbversion
        !warning    !pragma         !verbose

    Predefines
    We can use these standard predefines to automatically add the bild time 
    to the title of development versions, add the date to the version number, etc.

    Predefines          Predefines              In Scope
        __COUNTER__     NSIS_VERSION            __GLOBAL__
        __FILE__        NSIS_PACKEDVERSION      __SECTION__
        __FILEDIR__     NSIS_CHAR_SIZE          __FUNCTION__
        __LINE__        NSIS_PTR_SIZE           __PAGEEX__
        __DATE__        U+1 .. U+10FFFF         __UNINSTALL__
        __TIME__                                __MACRO__
        __TIMESTAMP__

    Read environment variables
    It will be replaced at compile time by the environment variable envVarName.
        $%envVarName%

    Conditional compilation
    The compiler maintains a list of defined symbols, which can be used
    for conditional compilation or for symbol replacement.
   
        !define         !ifmacrodef         !searchparse
        !undef          !ifmacrondef        !searchreplace
        !ifdef          !insertmacro
        !ifndef         !macro
        !if             !macroend
        !else           !macroundef
        !endif
