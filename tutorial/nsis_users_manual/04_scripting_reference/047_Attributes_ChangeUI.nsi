# ChangeUI dialog ui_file.exe
;
; Replaces dialog (IDD_LICENSE, IDD_DIR, IDD_SELCOM, IDD_INST, IDD_INSTFILES,
; IDD_UNINST or IDD_VERIFY) with a dialog from ui_file.exe with the same
; resource ID.
; For some examples UIs look at Contrib\UIs under your NSIS directory.

;   IDD_LICENSE must contain IDC_EDIT1 (RICHEDIT control)
;   IDD_DIR     must contain IDC_DIR (edit box), IDC_BROWSE (button) and IDC_CHECK1 (checkbox)
;   IDD_SELCOM  must contain IDC_TREE1 (SysTreeView32 control) and IDC_COMBO1 (combo box)
;   IDD_INST    must contain IDC_BACK (button), IDC_CHILDRECT (static control), IDC_VERSTR (static)
;               and IDCANCEL (bn). If an image control (static with SS_BITMAP style) will be
;               found it will be used as the default for SetBrandingImage.
;   IDD_INSTFILES must contain IDC_LIST1 (SysListView32 ctrl) IDC_PROGRESS (msctls_progress32 ctrl) IDC_SHOWDETAILS (bn)
;   IDD_UNINST  must contain IDC_EDIT1 (edit box)
;   IDD_VERIFY  must contain IDC_STR (static)

ChangeUI all "${NSISDIR}\Contrib\UIs\sdbarker_tiny.exe"

InstallDir "$PROGRAMFILES64\MyApp"

Page license
Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd


Section Uninstall
    delete "$INSTDIR\uninstall.exe"
    rmDir $INSTDIR
SectionEnd