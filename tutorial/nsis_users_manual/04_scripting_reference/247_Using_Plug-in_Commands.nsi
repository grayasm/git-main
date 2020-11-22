; 4.11.1 Using Plug-in Commands
; A plug-in call looks like this:

; InstallOptions::dialog "ini_file_location.ini"
; All parameters are pushed onto the stack (in this case, the plug-in function only needs one parameter).
; Some plug-in commands may not need any parameters on the stack, others might require more of them. 
; To use a plug-in command you will need to read the documentation for the plug-in so that you know 
; what parameters its functions require.