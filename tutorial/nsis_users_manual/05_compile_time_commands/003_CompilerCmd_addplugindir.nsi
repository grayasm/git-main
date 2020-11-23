; !addplugindir  [/x86-ansi | /x86-unicode] directory
;
; Causes the NSIS compiler to scan the given directory for plug-in DLLs.
; If you don't specify the plug-in architecture it is assumed to match 
; the current target architecture.
; If the architecture does not match the installer will probably crash!


!addplugindir "..\02_the_basics\10_plugin"

Section
    extDll::TestFn "test string" "-1.2345"
    Pop $0
    DetailPrint "extDll::TestFn returned $0"
SectionEnd

; Error: Plugin not found, cannot call extDll::TestFn
;
; Use CMake to build the Dll first.
; Do not copy the Dll anywhere because it is copied automatically.