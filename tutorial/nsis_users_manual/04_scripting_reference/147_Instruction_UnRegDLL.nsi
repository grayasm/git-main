; UnRegDLL  dllfile
;
; Loads the specified DLL and calls DllUnregisterServer. 
; The error flag is set if an error occurs (i.e. it can't load the DLL, 
; initialize OLE, find the entry point, or the function returned anything 
; other than ERROR_SUCCESS (=0)).

; see RegDll.nsi example