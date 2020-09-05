; PEAddResource [/OVERWRITE|/REPLACE] file restype resname [reslang]
;
; Adds file as a resource to the installer and uninstaller. 
;   restype specifies the resource type and can be any string or # followed by
;           a standard type or number.
;   resname must be # followed by a number.
;   reslang is optional and specifies the language id of the resource.

PEAddResource "074_attributes_bitmap.bmp"    "#2"    "#1337"
PEAddResource "074_attributes_icon.ico"      "#Icon" "#200"
PEAddResource "074_attributes_png.png"       "PNG"   "#1234"

InstallDir "$DOCUMENTS\074_attributes_test"
Page directory
Page instfiles

Section 1
    SetOutPath $INSTDIR

    ; File can install this resource without problem.
    File "074_attributes_icon.ico"

    ; CreateShortCut needs the resource installed on disk so nothing non standard.
    CreateShortCut "$INSTDIR\shortcut.lnk" "Notepad.exe" "" "$INSTDIR\074_attributes_icon.ico" 0 SW_SHOWNORMAL

    ; I think the intention here is replace installer resources, like it's icon?
SectionEnd