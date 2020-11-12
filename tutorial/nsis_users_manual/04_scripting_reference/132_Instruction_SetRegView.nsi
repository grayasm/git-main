; SetRegView  32 | 64 | default | lastused
;
; Sets the registry view affected by registry commands.
; On 64-bit versions of Windows there are two views:
;   one for 32-bit applications and
;   one for 64-bit applications.
;
; By default, 32-bit applications running on 64-bit systems (WOW64) 
; only have access to the 32-bit view.
; Using SetRegView 64 allows the installer to access keys in the 64-bit view 
; of the registry. Registry operations will fail if the selected view is not
; supported by Windows.
;
; Affects DeleteRegKey, DeleteRegValue, EnumRegKey, EnumRegValue, ReadRegDWORD,
; ReadRegStr, WriteRegBin, WriteRegDWORD, WriteRegStr and WriteRegExpandStr.
;
; Does not affect InstallDirRegKey. Instead, the registry must be read using 
; ReadRegStr in .onInit.

Section
    SetRegView 32
    ReadRegStr $0 HKLM Software\Microsoft\Windows\CurrentVersion ProgramFilesDir
    DetailPrint $0 # prints C:\Program Files (x86)
    !include x64.nsh
    ${If} ${RunningX64}
      SetRegView 64
      ReadRegStr $0 HKLM Software\Microsoft\Windows\CurrentVersion ProgramFilesDir
      DetailPrint $0 # prints C:\Program Files
    ${EndIf}
    SetRegView Default
SectionEnd