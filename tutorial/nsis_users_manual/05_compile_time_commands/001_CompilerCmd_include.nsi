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

!include 001_header.nsi
!include /NONFATAL file_that_may_exist_or_not.nsh

Section
    ; Math::Script NSIS plugin: https://nsis.sourceforge.io/Docs/Math/Math.txt
    ; Math::Script r0-r9 sets-> $0-$9. 
    ; Math::Script R0-R9 sets-> $R0-$R9
    
    StrCpy $R0 "1e1"
    Math::Script    "   \
        pi=3.14159;     \
        R1 = 2*pi*R0;   \
        r0 = 'Length of circle with radius ' + R0 + ' is equal to ' + R1 + '.'"
    
    ; Value of Math::Script r0 should be in $0
    Push $0
    Call func001
SectionEnd