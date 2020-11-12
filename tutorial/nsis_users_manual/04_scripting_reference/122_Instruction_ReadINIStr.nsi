; ReadINIStr user_var(output) ini_filename section_name entry_name
;
; Reads from entry_name in [section_name] of ini_filename and stores the value 
; into user variable $x. The error flag will be set and $x will be assigned 
; to an empty string if the entry is not found.


Section
    WriteINIStr $TEMP\something.ini SectionName EntryName Value
    FlushINI    $TEMP\something.ini
    
    ReadINIStr  $0 $TEMP\something.ini SectionName EntryName
    DetailPrint "$TEMP\something.ini"
    DetailPrint "[SectionName]"
    DetailPrint "EntryName=$0"
    
    Delete $TEMP\something.ini
SectionEnd