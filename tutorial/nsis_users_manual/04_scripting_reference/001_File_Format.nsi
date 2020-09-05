
; Comment
# Comment
# Comment \
    Another comment line (see `Long commands` section below?)

/*
Comment
Comment
*/

Name /* comment */ 01_file_format


Section

# Command
File "README.txt"

# Plug-in
; nsExec::Exec "myfile"

# Numbers (decimal, hexadecimal or octal)
IntCmp 1 0x1 lbl_equal
    DetailPrint "IntCmp 1 0x1 False"
lbl_equal:
    DetailPrint "IntCmp 1 0x1 True"

# Colors (RGB format, like HTML but without the #)
SetCtlColors $HWND CCCCCC

# Strings
; Use quotes for strings with spaces.
; Quotes only have the property of containing a parameter if they surround the
; rest of the parameter. They can be double " single ' and backward single `
; quote. You can escape quotes using $\:

MessageBox MB_OK "Double quoted string!"
MessageBox MB_OK 'Single quoted "string"!'
MessageBox MB_OK `Backward single quoted ' "string" '!`
MessageBox MB_OK "$\"Escaped double quoted string!$\""

# Variables
; Variables start with $. User variables must be declared.
Var /GLOBAL MYVAR
StrCpy $MYVAR "sample variable"
DetailPrint "Variable $$MYVAR=$MYVAR"


# Long commands
; To extend a command over multiple lines use a backslash (\) at the end of the
; line. The next line will concatenated to the end of it.
MessageBox MB_YESNO|MB_ICONQUESTION \
    "Do you want to remove all files in the folder? \
    (If you have anything you created that you want \
    to keep, click No)"
    
; Line extension for long commands works for comments as well.
SectionEnd





















