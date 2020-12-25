; !else  [if | ifdef | ifndef | ifmacrodef | ifmacrondef  [...]]
;
; This command allows to easily insert different code 
; when different defines or macros are set.
; You can create blocks like !ifdef/!else/!endif, !ifdef/!else ifdef/!else/!endif etc.

!ifdef VERSION
    OutFile installer-${VERSION}.exe
!else
    OutFile installer.exe
!endif


; default
Section
SectionEnd