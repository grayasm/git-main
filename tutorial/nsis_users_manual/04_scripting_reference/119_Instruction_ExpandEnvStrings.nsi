; ExpandEnvStrings user_var(output) string
;
; Expands environment variables in string into the user variable $x. 
; If an environment variable doesn't exist, it will not be replaced. 
; For example, if you use "%var%" and var doesn't exists, the result will be "%var%". 
; If there is an error, the variable is set to empty, and the error flag is set.


Section
    ExpandEnvStrings $0 "WINDIR=%WINDIR%$\nTEMP=%TEMP%"
    MessageBox MB_OK  "$0"
SectionEnd