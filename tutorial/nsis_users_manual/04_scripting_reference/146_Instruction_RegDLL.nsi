; RegDLL  dllfile  [entrypoint_name]
;
; Loads the specified DLL and calls DllRegisterServer or entrypoint_name.
; The error flag is set if an error occurs (i.e. it can't load the DLL, 
; initialize OLE, find the entry point, or the function returned anything other 
; than ERROR_SUCCESS (=0)).
; Use SetOutPath to set the current directory for DLLs that depend on other DLLs 
; that are now in the path or in the Windows directory. 
; For example, if foo.dll depends on bar.dll which is located in $INSTDIR use:


InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    
    ; VS2019 ATL Project description:
    ; Create small, fast Component Object Model (COM) objects using the
    ; Active Template Library (ATL).
    ; Category: C++, Windows, Desktop
    
    ; The source code looks like this:
;   // DllRegisterServer - Adds entries to the system registry.
;   STDAPI DllRegisterServer(void)
;   {
;	    // registers object, typelib and all interfaces in typelib
;	    HRESULT hr = _AtlModule.DllRegisterServer();
;	    MessageBoxA(NULL, "Greetings from a COMM dll!", "DllRegisterServer", MB_OK | MB_ICONINFORMATION);
;	    return hr;
;   }

    File 146_COMDll.dll    
    RegDLL $INSTDIR\146_COMDll.dll ; expect a MessageBoxA
SectionEnd

Section Uninstall
    UnRegDLL $INSTDIR\146_COMDll.dll
    RMDir /r $INSTDIR
SectionEnd
