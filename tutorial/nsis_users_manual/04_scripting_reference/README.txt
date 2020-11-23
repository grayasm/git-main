    Cap.4 Scripting Reference
    
    4.1 Script File Format
        ; comment
        # comment
        /* comment */
        IntCmp $0 120 eqlbl gtlbl ltlbl     ; Numbers
        StrCmp $0 "a string" eqlbl neqlbl   ; Strings
        StrCpy $0 120                       ; Variables $0->$9 $R0->$R9
        Push 120                            ; Stack push 120
        Pop  $0                             ; Stack pop 120 into $0
        Call func                           ; Call a function
        ; and much more

    4.2 Variables
        Var /GLOBAL var1
        StrCpy $var1 "string sample"
        $0 -> $9, $R0 -> $R9
        $INSTDIR            -> installation directory
        $PROGRAMFILES64     -> C:\Program Files\
        
    4.3 Labels
        Goto end
        end:

    4.4 Relative Jumps
        Goto +1 -> jumps to next line, 0 does not jump.

    4.5 Pages
        Internal pages: license, components, directory, instfiles, uninstConfirm
        Page internal_page [pre_function] [show_function] [leave_function] [/ENABLECANCEL]
        or
        Page custom [creator_function] [leave_function] [caption] [/ENABLECANCEL]
        or
        PageEx [un.] (custom|uninstConfirm|license|components|directory|instfiles)

    4.6 Sections
        Section [/o] [([!] | [-]) section_name] [section_index]
        /o optional
        /! bold
        /- hidden

        InstallDir $DOCUMENTS\MyApp
        InstType "Full"
        InstType "Standard"
        InstType "Minimal"
        Page directory
        Page components
        Page instfiles
        SectionGroup "Group"
            Section "section 1" S1_ID
                SectionIn 1 2 3
                DetailPrint "Installing files of section 1"
                SetOutPath $INSTDIR
                WriteUninstaller $INSTDIR\uninstall.exe                
            SectionEnd
            Section "section 2" S2_ID
                SectionIn 1 2
                DetailPrint "Installing files of section 2"
            SectionEnd
            Section "section 3" S3_ID
                SectionIn 1
                DetailPrint "Installing files of section 3"
            SectionEnd
        SectionGroupEnd
        Section Uninstall
            RMDir /r $INSTDIR
        SectionEnd
        Function .onInit
            ; can adjust other settings before running the installation
        FunctionEnd

    4.7 Functions
        ; callbacks
        .onInit
        .onSelChange
        un.onInit
        un.onSelChange
        
        ; user defined
        Function func
        FunctionEnd
        
    4.8 Installer Attributes
        AddBrandingImage left 100u
        AutoCloseWindow true
        DirText [text] [subtext] [browse_button_text] [browse_dlg_text]
        
    4.9 Instructions
        GetTempFileName $0
        File /oname=$0 "${NSISDIR}\Contrib\Graphics\Wizard\nullsoft.bmp"
        SetBrandingImage /RESIZETOFIT $0
        Delete $0
        or
        IntOp $0 1 + 1
        IntOp $0 $0 + 1     ; $0 is 2
        IntOp $0 $0 << 2    ; $0 is 4
        IntOp $0 $0 ~       ; $0 is -3
        IntOp $0 $0 & 0xF   ; $0 is 2
    
    4.10 Multiple Languages
    4.11 Plug-in DLLs
    4.12 Silent Installers / Unistallers