# ManifestLongPathAware notset|true|false
;
; Declare that the installer can handle paths longer than MAX_PATH.
; Only supported on Windows 10 Anniversary Update and later.


; Note: when activating the next line compiler returns "Error setting manifest: Incompatible option"
; ManifestLongPathAware true

InstallDir "$PROGRAMFILES64\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware\App_Testing_NSIS_ManifestLongPathAware"

Page directory
Page instfiles

Section ""
    SetOutPath $INSTDIR
    DetailPrint "Installing in $INSTDIR"
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd


Section Uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir /r $INSTDIR
SectionEnd