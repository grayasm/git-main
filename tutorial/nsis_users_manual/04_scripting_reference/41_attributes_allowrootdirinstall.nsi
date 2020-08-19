# AllowRootDirInstall (installer attribute)
;
; AllowRootDirInstall true|false
;
; Controls whether or not installs are allowed in the root directory of a drive,
; or directly into a network share.
; Set to true to enable unsafe behaviour (C:\ or \\Server\Share)

AllowRootDirInstall true

InstallDir "C:\"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    DetailPrint "Allowed to install in $INSTDIR"
SectionEnd
