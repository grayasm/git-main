; WriteRegExpandStr root_key  subkey  key_name  value
;
; Write a REG_EXPAND_STR string to the registry. root_key must be one of:
;   HKCR or HKEY_CLASSES_ROOT
;   HKLM or HKEY_LOCAL_MACHINE
;   HKCU or HKEY_CURRENT_USER
;   HKU or HKEY_USERS
;   HKCC or HKEY_CURRENT_CONFIG
;   HKDD or HKEY_DYN_DATA
;   HKPD or HKEY_PERFORMANCE_DATA
;   SHCTX or SHELL_CONTEXT
;   HKCR32 or HKCR64
;   HKCU32 or HKCU64
;   HKLM32 or HKLM64
;
; If root_key is SHCTX or SHELL_CONTEXT, it will be replaced with HKLM if
; SetShellVarContext is set to all and with HKCU if SetShellVarContext is set to current.
; The error flag is set if the string could not be written to the registry. 
; The type of the string will be REG_SZ for WriteRegStr, or REG_EXPAND_STR for
; WriteRegExpandStr. If the registry key doesn't exist it will be created.

Section
    SetRegView 64
    WriteRegExpandStr HKLM "Software\MyCompany\MyApp" "Expand String Value" "%TEMP%\settings.ini"
    
    ReadRegStr $0 HKLM "Software\MyCompany\MyApp" "Expand String Value"
    
    DetailPrint "Expand String Value=$0"
    ; Expand String Value=%TEMP%\settings.ini
    
    ExpandEnvStrings $1 $0
    DetailPrint "Expand String Value=$1"
    ; Expan String Value=C:\Users\<user>\AppData\Local\Temp\settings.ini


    ; Clean up
    DeleteRegKey HKLM "Software\MyCompany\MyApp"
SectionEnd
