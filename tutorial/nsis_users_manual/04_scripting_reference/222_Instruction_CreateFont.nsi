; CreateFont user_var(handle output)  face_name  [height]  [weight]  [/ITALIC]  [/UNDERLINE]  [/STRIKE]
;
; Creates a font and puts its handle into user_var. 
; For more information about the different parameters have a look at MSDN's page 
; about the Win32 API function CreateFont().

; You can get the current font used by NSIS using the ^Font and ^FontSize LangStrings.


!include WinMessages.nsh

Page directory
Page instfiles

Section
    GetDlgItem $0 $HWNDPARENT 1
    CreateFont $1 "Times New Roman" "12" "700" /UNDERLINE
    SendMessage $0 ${WM_SETFONT} $1 1
SectionEnd