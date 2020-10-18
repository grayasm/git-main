; File [/nonfatal] [/a] ([/r] [/x file|wildcard [...]] (file|wildcard) [...] | /oname=file.dat infile.dat)
;
; Adds file(s) to be extracted to teh output path ($OUTDIR)
; /oname=X  changes the output name. X can contain variables and can be full or
;           relative path. It will be appended to $OUTDIR. Use quotes when X
;           contains spaces. 
; wildcards are supported
; /r        matching files and directories are recursively searched for in subdirectories
;           If a directory name matches, all of its content is added recursively.
;           Directory structure is preserved.
; /x        excludes files and directories.
; /a        preserves the attributes of the file(s).
; File sets the error flag is (1) overwrite mode is 'try' and file couldn't be
;           overwritten or (2) overwrite mode is 'on' and user selects 'Ignore'
; /nonfatal issues a warning instead of an error if files are not found.

InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    File 108_Instruction_File.nsi
    File /a 108_timeout.exe
    # File *.exe
    # File /r *.dat
    # File /r data
    File /oname=timeout.exe 108_timeout.exe
    File /oname=$TEMP\timeout.exe 108_timeout.exe
    File "/oname=$TEMP\time out with spaces.exe" 108_timeout.exe
    File /nonfatal "a file that might not exist"
    # File /r /x CVS myproject\*.*
    # File /r /x *.res /x *.obj /x *.pch source\*.*
SectionEnd