; !finalize  command  [compare  comparevalue]
;
; This option will execute 'command' using a call to system() 
; after the output EXE has been generated. 
; You can typically use it to sign (Authenticode) your installer.
; If 'command' contains a '%1' it will be replaced by the executables filename.

Section
SectionEnd

!finalize '012_sign.bat "%1" "Product Installer" http://example.com'

; "D:\workdir\...\nsis_users_manual\05_compile_time_commands\012_CompilerCmd_finalize.exe"
; "Product Installer"
; http://example.com
