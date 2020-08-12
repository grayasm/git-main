Cap.1 Introduction to NSIS

1.1.    About NSIS
    NSIS (Nullsoft Scriptable Install System) is a tool that allows programmers
    to create installers for Windows. It is capable of installing, uninstalling
    setting system settings, extracting files, etc. It is based on a scripting
    language that supports variables, functions and string manipulation.
    NSIS is the smallest installer system available (only 34KB).
    
1.2.    Main Features
    Small overhead size of only 34KB.
    Compatible with all major Windows versions. (95,98,ME,NT4,2000,XP,2003,
        Vista,Server 2008, 7, Server 2008R2, 8, Server 2012, 8.1, Server 2012R2
        and Windows 10)
    Uses 3 different integrated compression methods (ZLib, BZip2, LZMA).
    Script based with a powerful scripting language designed for installers.
    Multiple languages in one installer. It supports more than 60 translations.
    Many features and checks for the target system from simple features like
        folder creation and registry editing to text/binary file modification,
        modification of environment variables and system reboots. Via plug-ins
        you can even call the Windows API directly.
    Custom dialogs and interfaces. NSIS includes a classic and modern wizard
        interface but it is possible to create your own custom interface.
    Plug-in system allows plug-ins to communicate with the installer. They can
        be written in C,C++ or another language and can be used to perform
        installation tasks or extend the installer interface. It can be called
        with 1 line of script code. They are compressed like other installation
        data only when their features are used by the installer.
    Web installation and file patching allows installer (via plug-ins) to
        download files from the internet, make internet connections, patch
        existing files and more.
    Project integration. NSIS compiler features a powerful preprocessor. This
        allows integration of multiple projects into a single installer or
        automatically generate installer builds.
    Easy and human readable file formats.
    
1.3.    Feature List
    https://nsis.sourceforge.io/Docs/Chapter1.html#intro-featurelist
    (short summary)
    Installers have their own VMs that let you write code that can support:
        File extraction (with configurable overwrite parameters)
        File/directory copying, renaming, deletion, searching
        Plug-in DLL calling
        DLL/ActiveX control registration/deregistration
        Executable execution (shell execute and wait options)
        Shortcut creation
        Registry key reading/setting/enumerating/deleting
        INI file reading/writing
        Generic text file reading/writing
        Powerful string and integer manipulation
        Window finding based on class name or title
        User interface manipulation (font/text setting)
        Window message sending
        User interaction with message boxes or custom pages
        Branching, comparisons, etc.
        Error checking
        Reboot support, including delete or rename on reboot
        Installer behaviour commands (such as show/hide/wait/etc)
        User functions in script
        Callback functions for user actions
        
1.4.    Unicode installers
    Possible with NSIS v3.0 only for Windows 2000 or later.
    NSIS variables can hold Unicode characters (0001-FFFF).
    Specific instructions have been added to read/write UTF-16LE strings from/to
    disk.
