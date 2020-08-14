# Variables
; All variables are global and can be used in Section,Function
; By defalt variables are limited to 1024 characters.
; Var [/GLOBAL] var_name

Var example

Function TestVar
    Var /GLOBAL example2
    
    StrCpy $example  "example value"
    StrCpy $example2 "another example value"
FunctionEnd


# Other Writeable Variables
; Registers
; $0 $1 $2 $3 $4 $5 $6 $7 $8 $9 $R0 $R1 $R2 $R3 $R4 $R5 $R6 $R7 $R8 $R9
; Are used in shared functions and macros. You don't need to declare these
; variables. It is recommended to use the stack to save and restore their
; original value. They can be used for communication with plug-ins because
; they can be read & written by the plug-ins DLLs.

Section 1
    DetailPrint "Before $$0=$0"
    Push $0
    StrCpy $0 -100.2
    DetailPrint "After  $$0=$0"
    Pop $0

; $INSTDIR
; modifiable using StrCpy, ReadRegStr, ReadINIStr, etc.
; In the uninstaller it contains the directory where the uninstaller is.
    DetailPrint "$$INSTDIR=$INSTDIR"

; CMDLINE
; The command line of the installer.
    DetailPrint "$$CMDLINE=$CMDLINE"
    
; LANGUAGE
; The identifier of the language that is currently used. English is 1033.
    DetailPrint "$$LANGUAGE=$LANGUAGE"
SectionEnd


# Contants
; Some of the new constants will not work on every OS. For example
; $CDBURN_AREA will only work on Windows XP and it will be empty in Windows 98.
Section 2
    DetailPrint "$$PROGRAMFILES=$PROGRAMFILES"      ; C:\Program Files (x86)
    DetailPrint "$$PROGRAMFILES32=$PROGRAMFILES32"  ; C:\Program Files (x86)
    DetailPrint "$$PROGRAMFILES64=$PROGRAMFILES64"  ; C:\Program Files
    DetailPrint "$$COMMONFILES=$COMMONFILES"        ; C:\Program Files (x86)\Common Files
    DetailPrint "$$COMMONFILES32=$COMMONFILES32"    ; C:\Program Files (x86)\Common Files
    DetailPrint "$$COMMONFILES64=$COMMONFILES64"    ; C:\Program Files\Common Files
    DetailPrint "$$DESKTOP=$DESKTOP"                ; C:\Users\mihai\Desktop
    DetailPrint "$$EXEDIR=$EXEDIR"                  ; Installer directory
    DetailPrint "$$EXEFILE=$EXEFILE"                ; Installer base name
    DetailPrint "$$EXEPATH=$EXEPATH"                ; Installer full path
    DetailPrint "$$NSISDIR=${NSISDIR}"              ; Where NSIS is installed
    DetailPrint "$$WINDIR=$WINDIR"                  ; C:\Windows
    DetailPrint "$$SYSDIR=$SYSDIR"                  ; C:\Windows\System
    DetailPrint "$$TEMP=$TEMP"                      ; C:\Users\mihai\AppData\Local\Temp
    DetailPrint "$$STARTMENU=$STARTMENU"            ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\Start Menu
    DetailPrint "$$SMPROGRAMS=$SMPROGRAMS"          ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\Start Menu\Programs
    DetailPrint "$$SMSTARTUP=$SMSTARTUP"            ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
    DetailPrint "$$QUICKLAUNCH=$QUICKLAUNCH"        ; C:\Users\mihai\AppData\Roaming\Microsoft\Internet Explorer\Quick Launch
    DetailPrint "$$DOCUMENTS=$DOCUMENTS"            ; C:\Users\mihai\Documents
    DetailPrint "$$SENDTO=$SENDTO"                  ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\SendTo
    DetailPrint "$$RECENT=$RECENT"                  ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\Recent
    DetailPrint "$$FAVORITES=$FAVORITES"            ; C:\Users\mihai\Favorites
    DetailPrint "$$MUSIC=$MUSIC"                    ; C:\Users\mihai\Music
    DetailPrint "$$PICTURES=$PICTURES"              ; C:\Users\mihai\Pictures
    DetailPrint "$$VIDEOS=$VIDEOS"                  ; C:\Users\mihai\Videos
    DetailPrint "$$NETHOOD=$NETHOOD"                ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\Network Shortcuts
    DetailPrint "$$FONTS=$FONTS"                    ; C:\WINDOWS\Fonts
    DetailPrint "$$TEMPLATES=$TEMPLATES"            ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\Templates
    DetailPrint "$$APPDATA=$APPDATA"                ; C:\Users\mihai\AppData\Roaming
    DetailPrint "$$LOCALAPPDATA=$LOCALAPPDATA"      ; C:\Users\mihai\AppData\Local
    DetailPrint "$$PRINTHOOD=$PRINTHOOD"            ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\Printer Shortcuts
    DetailPrint "$$INTERNET_CACHE=$INTERNET_CACHE"  ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\INetCache
    DetailPrint "$$COOKIES=$COOKIES"                ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\INetCookies
    DetailPrint "$$HISTORY=$HISTORY"                ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\History
    DetailPrint "$$PROFILE=$PROFILE"                ; C:\Users\mihai
    DetailPrint "$$ADMINTOOLS=$ADMINTOOLS"          ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Administrative Tools
    DetailPrint "$$RESOURCES=$RESOURCES"            ; C:\WINDOWS\resources
    DetailPrint "$$RESOURCES_LOCALIZED=$RESOURCES_LOCALIZED"    ; C:\WINDOWS\resources\0409
    DetailPrint "$$CDBURN_AREA=$CDBURN_AREA"        ; C:\Users\mihai\AppData\Roaming\Microsoft\Windows\Burn\Burn
    DetailPrint "$$HWNDPARENT=$HWNDPARENT"          ; HWND of the main window (in decimal)  =1970530
    DetailPrint "$$PLUGINSDIR=$PLUGINSDIR"          ; TMP directory created and deleted by the installer
SectionEnd


# Constants Used in Strings
; $$  use to represent $
; $\r use to represent a carriage return (\r)
; $\n use to represent a newline (\n)
; $\t use to represent a tab (\t)
Section 3
    DetailPrint "$$ use to reprent a $"
    DetailPrint "$\r use to represent a carriage return (\r)"
    DetailPrint "$\n use to represent a newline (\n)"
    DetailPrint "$\t use to represent a tab (\t)"
SectionEnd



