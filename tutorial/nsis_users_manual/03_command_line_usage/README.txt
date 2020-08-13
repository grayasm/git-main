Cap.3 Command Line Usage

3.1.    MakeNSIS Usage
    makensis [ option | script.nsi | - ] [...]
    option: https://nsis.sourceforge.io/Docs/Chapter3.html#usagereference
    
    Environment variables
    NSISDIR, NSISCONFDIR, APPDATA or HOME
    
    Examples:
    makensis.exe myscript.nsi
    makensis.exe /V1 myscript.nsi                                   ; quiet mode
    makensis.exe /X"SetCompressor /FINAL lzma" myscript.nsi         ; force compressor
    makensis.exe /DUSE_UPX /DVERSION=1.337 /DNO_IMAGES myscript.nsi ; change behavior
    makensis.exe /XSection sectioncontents.nsi /XSectionEnd         ; parameters order
    
3.2.    Installer Usage
    Generated installers and uninstallers accept a few options on the command line.
    /NCRC disables the CRC check
    /S runs silently
    /D sets the default installation directory $INSTDIR, overriding InstallDir and InstallDirRegKey
    
    _?= sets $INSTDIR and also stops the uninstaller from copying itself to the
    temporary directory and running from there.
    
    Examples:
    installer.exe /NCRC
    installer.exe /S
    installer.exe /NCRC /S /D=C:\Program Files\NSIS
    uninstaller.exe /S _?=C:\Program Files\NSIS
    