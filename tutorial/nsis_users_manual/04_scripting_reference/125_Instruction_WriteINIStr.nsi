; WriteINIStr ini_filename  section_name  entry_name  value
;
; Writes entry_name=value into [section_name] of ini_filename. 
; The error flag is set if the string could not be written to the ini file.

Section
    WriteINIStr $TEMP\something.ini section1 something 123
    WriteINIStr $TEMP\something.ini section1 somethingelse 1234
    WriteINIStr $TEMP\something.ini section2 nsis true
    
    ReadINIStr $0 $TEMP\something.ini section2 nsis
    
    DetailPrint "$TEMP\something.ini"
    DetailPrint "[section2]"
    DetailPrint "nsis=$0"
    
    ; clean up
    Delete $TEMP\something.ini
SectionEnd