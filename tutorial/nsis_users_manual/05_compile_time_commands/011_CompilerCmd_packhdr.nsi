; !packhdr  tempfile  command
;
; This option makes the compiler use an external EXE packer (such as Petite or UPX)
; to compress the executable header.

!packhdr "$%TEMP%\exehead.tmp" '"C:\Program Files\UPX\upx.exe" "$%TEMP%\exehead.tmp"'

Section
SectionEnd