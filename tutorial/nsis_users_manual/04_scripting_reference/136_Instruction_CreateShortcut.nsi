; CreateShortcut    [/NoWorkingDir] link.lnk target.file 
;                   [parameters 
;                   [icon.file [icon_index_number 
;                   [start_options 
;                   [keyboard_shortcut 
;                   [description]]]]]]
;
;   Creates a shortcut link.lnk that links to target.file with optional parameters.
;   You must specify an absolute path to the .lnk file.
;
;   icon.file, icon_index_number is the shortcut Icon. For default icon settings 
;               use empty strings for both icon.file and icon_index_number.
;   start_options should be one of: SW_SHOWNORMAL, SW_SHOWMAXIMIZED, 
;               SW_SHOWMINIMIZED, or an empty string. 
;   keyboard_shortcut should be in the form of 'flag|c' where flag can be 
;               a combination (using |) of: ALT, CONTROL, EXT, or SHIFT. 
;               c is the character to use (a-z, A-Z, 0-9, F1-F24, etc). 
;               Note that no spaces are allowed in this string.
;               Example: "ALT|CONTROL|F8". 
;
;   $OUTDIR is stored as the shortcut's working directory property. 
;   You can change it by using SetOutPath before creating the shortcut 
;   or use /NoWorkingDir if you don't need to set the working directory property. 
;
;   description should be the description of the shortcut, or comment as it 
;               is called under XP.
;
;   The error flag is set if the shortcut cannot be created 
;   (i.e. either of the paths (link or target) does not exist, or some other error).

InstallDir "$DOCUMENTS\MyApp"

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    ; Use this as the app executable
    File 108_timeout.exe
    WriteUninstaller "$INSTDIR\uninstall.exe"
    
    CreateDirectory "$SMPROGRAMS\My Company"
    CreateShortcut  "$SMPROGRAMS\My Company\MyApp.lnk" "$INSTDIR\108_timeout.exe" \
                    "5" \
                    "$INSTDIR\108_timeout.exe" 1 \
                    SW_SHOWNORMAL \
                    ALT|CONTROL|SHIFT|F5 "Timeout 5 seconds!"
SectionEnd

Section Uninstall
    RMDir /r $INSTDIR
SectionEnd
