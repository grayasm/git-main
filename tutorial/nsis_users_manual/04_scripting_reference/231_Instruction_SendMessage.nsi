; SendMessage HWND  msg  wparam  lparam  [user_var(return value)]  [/TIMEOUT=time_in_ms]
;
; Sends a message to HWND.
; If a user variable $x is specified as the last parameter,
;       or one before the last if you use /TIMEOUT, 
;       the return value from SendMessage will be stored in it.
; Note that when specifying 'msg' you must just use the integer value of the message.
; Include WinMessages.nsh to have all Windows messages defined in your script. 
; If you wish to send strings use "STR:a string" as wParam or lParam where needed.
; Use /TIMEOUT=time_in_ms to specify the duration, in milliseconds, of the time-out period.

!include WinMessages.nsh

Section
    GetDlgItem  $1 $HWNDPARENT 1
    SendMessage $1 ${WM_SETTEXT} 0 "STR:Goodbye"    ; does not work??
SectionEnd



