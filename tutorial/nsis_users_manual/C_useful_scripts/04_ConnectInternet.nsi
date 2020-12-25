; ConnectInternet (uses Dialer plug-in) - Written by Joost Verburg 
 ;
 ; This function attempts to make a connection to the internet if there is no
 ; connection available. If you are not sure that a system using the installer
 ; has an active internet connection, call this function before downloading
 ; files with NSISdl.
 ; 
 ; The function requires Internet Explorer 3, but asks to connect manually if
 ; IE3 is not installed.
 
 Function ConnectInternet
 
   Push $R0
     
     ClearErrors
     Dialer::AttemptConnect
     IfErrors noie3
     
     Pop $R0
     StrCmp $R0 "online" connected
       MessageBox MB_OK|MB_ICONSTOP "Cannot connect to the internet."
       Quit ; This will quit the installer. You might want to add your own error handling.
     
     noie3:
   
     ; IE3 not installed
     MessageBox MB_OK|MB_ICONINFORMATION "Please connect to the internet now."
     
     connected:
   
   Pop $R0
   
 FunctionEnd
 
 
 Section
    Call ConnectInternet
 SectionEnd