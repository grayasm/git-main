.
    *** The Preprocessor ***

    C# defines several preprocessor directives, which affect the way that
    your program’s source file is interpreted by the compiler. These directives
    affect the text of the source file in which they occur, prior to the
    translation of the program into object code. The term preprocessor
    directive comes from the fact that these instructions were traditionally
    handled by a separate compilation phase called the preprocessor.

    Today’s modern compiler technology no longer requires a separate
    preprocessing stage to handle the directives, but the name has stuck.

    C# defines the following preprocessor directives:

    #define        #elif        #else       #endif
    #endregion     #error       #if         #line
    #pragma        #region      #undef      #warning


    *** Assemblies and the internal Access Modifier ***

    An integral part of C# programming is the assembly. An assembly is a file
    (or files) that contains all deployment and version information for a
    program. Assemblies are fundamental to the .NET environment. They provide
    mechanisms that support safe component interaction, cross-language
    interoperability, and versioning. An assembly also defines a scope.

    An assembly is composed of four sections.
    (1) The first is the assembly manifest. This data includes such things as
    the name of the assembly, its version number, type mapping information,
    and cultural settings.
    (2) The second section is type metadata, which is information about the
    data types used by the program.
    (3) The third part of an assembly is the program code, which is stored in
    Microsoft Intermediate Language (MSIL) format.
    (4) The fourth constituent of an assembly is the resources used by the
    program.

    Fortunately, when using C#, assemblies are produced automatically.
    The exe file created when you compile a C# program is actually an assembly
    that contains your program's executable code as well as other types of
    information. There are many other features and topics that relate to
    assemblies, but a discussion of these is outside the scope of
    this book.
