; CallInstDLL  dllfile  function_name 
;
; Calls a function named function_name inside a NSIS extension DLL, a plug-in.
; See the example plugin for how to make one. 
; Extension DLLs can access the stack and variables. 
; Note: To automatically extract and call plug-in DLLs, use a plug-in command
; instead of CallInstDLL.

; I already wrote a plug-in.
; See: nsis_users_manual\02_the_basics\10_plugin
