; !include [/NONFATAL]  [/CHARSET=ACP|OEM|CP#|UTF8|UTF16LE|UTF16BE] file
;
; This command will include 'file' as if it was part of the original script. 
; Note that if a file is included in another directory, the current directory 
;   is still where the script was compiled from, not where the included file 
;   resides.
; If the compiler can't find the file it will look for it in every include directory. 
; See !addincludedir for more information. 
; If the /nonfatal switch is used and no files are found, a warning will 
;   be issued instead of an error.
; /charset can be used to specify a codepage for plain text files without a BOM.

!include WinMessages.nsh
!include Library.nsh
!include /CHARSET=CP1252 C:\MyConfig.nsi
!include ..\MyConfig.nsh
!include /NONFATAL file_that_may_exist_or_not.nsh