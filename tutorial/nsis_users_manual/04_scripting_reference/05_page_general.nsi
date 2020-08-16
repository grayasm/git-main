# Pages
; Each (non-silent) NSIS installer has a set of pages. Each page can be a NSIS
; built-in page or a custom page created by a user's function (see nsDialogs or
; InstallOptions)
; The script controlls the page order, appearance and behavior.
; You can:
;   * skip pages
;   * paint them white
;   * force the user to stay in a page until a certain condition is met
;   * show a readme page
;   * show custom designed pages for input and more

; There are 3 commands regarding pages: Page, UninstPage, PageEx
Page instfiles
UninstPage instfiles

Section
SectionEnd