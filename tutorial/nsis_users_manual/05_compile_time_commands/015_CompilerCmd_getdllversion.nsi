; !getdllversion  [/noerrors]  [/packed]  localfilename  define_basename
;
; This is similar to GetDLLVersionLocal, only it stores the version number 
; in defines and can therefore be used anywhere, 
; not just inside functions and sections. 
; /packed returns the information in two DWORDs.

!getdllversion "$%WINDIR%\Explorer.exe" Expv_
!echo "Explorer.exe version is ${Expv_1}.${Expv_2}.${Expv_3}.${Expv_4}"


; default
Section
SectionEnd


; compiler output:

;!getdllversion: C:\WINDOWS\Explorer.exe (6.2.19041.662)->(Expv_<1..4>)
;Explorer.exe version is 6.2.19041.662