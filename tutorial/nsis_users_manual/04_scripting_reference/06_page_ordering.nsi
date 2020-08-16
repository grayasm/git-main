# Page Ordering
; The page ordering is set simply by the order Page, UninstPage and PageEx
; appear in teh script.

Page license
Page components
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section 1
SectionEnd

; NSIS will show first the license page, then the components selection page,
; then the directory selection page and finally the install log where selections
; are executed.
; The uninstaller will show first the uninstall confirmation page and then the
; uninstalltion log.

; YOU CAN SPECIFY THE SAME PAGE TYPE MORE THAN ONCE!