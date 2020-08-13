; Sample plugin for NSIS
; Installer packs/unpacks and calls extDll.dll method TestFn(p,q)

!addplugindir "10_plugin"

Section
    extDll::TestFn "test string" "-1.2345"
    Pop $0
    DetailPrint "extDll::TestFn returned $0"
SectionEnd
