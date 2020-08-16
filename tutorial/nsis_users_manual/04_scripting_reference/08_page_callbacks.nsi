# Page callbacks
; Each built-in page has 3 callbacks: pre-function, show funtion, leave function.
; The pre-function is called before the page is created.
; The show function is called after it was created by before it is shown.
; The leave function is called after the user has pressed the next button.

Page license skipLicense "" stayInLicense
Page custom customPage "" ": custom page"
Page instfiles

Function skipLicense
    MessageBox MB_YESNO "Do you want to skip the license page?" IDNO no
        Abort
    no:
FunctionEnd

Function stayInLicense
    MessageBox MB_YESNO "Do you want to stay in license page?" IDNO no
        Abort
    no:
FunctionEnd

Function customPage
    GetTempFileName $R0
    File /oname=$R0 08_customPage.ini
    InstallOptions::dialog $R0
    Pop $R1
    StrCmp $R1 "cancel" done
    StrCmp $R1 "back" done
    StrCmp $R1 "success" done
    error: MessageBox MB_OK|MB_ICONSTOP "InstallOptions error:$\r$\n$R1"
    done:
FunctionEnd

Section 1
SectionEnd