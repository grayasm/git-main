; FlushINI ini_filename
;
; Flushes the INI file's buffers. 
; Windows 9x keeps all changes to the INI file in memory. 
; This command causes the changes to be written to the disk immediately. 
; Use it if you edit the INI manually, delete it, move it or copy it right after
; you change it with WriteINIStr, DeleteINISec or DeleteINStr.

Section
    WriteINIStr $TEMP\something.ini test test test
    FlushINI    $TEMP\something.ini
    Delete      $TEMP\something.ini
SectionEnd