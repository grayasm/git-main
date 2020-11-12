; CopyFiles [/SILENT] [/FILESONLY] filespec_on_destsys destination_path [size_of_files_in_kb]
;
; Copies files from the source to the destination on the installing system.
;
; Useful with $EXEDIR if you want to copy from installation media, or to copy 
; from one place to another on the system. 
; You might see a Windows status window of the copy operation if the operation
; takes a lot of time (to disable this, use /SILENT). 
;
; The last parameter can be used to specify the size of the files 
; that will be copied (in kilobytes), so that the installer can approximate 
; the disk space requirements. 
; On error, or if the user cancels the copy (only possible when /SILENT was omitted), 
; the error flag is set. 
; If /FILESONLY is specified, only files are copied.


InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    ; If directory existed do a backup of existing files
    CreateDirectory $INSTDIR\backup
    CopyFiles $INSTDIR\* $INSTDIR\backup
    ; Continue 
    WriteUninstaller "$INSTDIR\uninstall.exe"   
    
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd
