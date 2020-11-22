; GetDlgItem  user_var(output)  dialog  item_id
;
; Retrieves the handle of a control identified by item_id in the specified 
; dialog box dialog. 
; If you want to get the handle of a control in the inner dialog, 
; first use FindWindow to get the handle of the inner dialog.

!include WinMessages.nsh

!define TVM_SETBKCOLOR 0x111D       ; Window Message Background
!define TVM_SETTEXTCOLOR 0x111E     ; Window Message Text

InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    GetDlgItem   $0 $HWNDPARENT 1     ; next/install button
    SendMessage  $0 ${TVM_SETBKCOLOR}   0 0x00BAB0A6
    SendMessage  $0 ${TVM_SETTEXTCOLOR} 0 0xFFFFFF
SectionEnd

; I don't know why it doens't set the colors