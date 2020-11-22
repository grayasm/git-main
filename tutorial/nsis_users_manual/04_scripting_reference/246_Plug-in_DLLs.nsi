; 4.11 Plug-in DLLs
; The abilities of the NSIS scripting language can be extended by utilising functionality provided in a DLL file. 
; Probably the best known example of this is the InstallOptions.dll bundled with every NSIS release.

; When the NSIS compiler starts it scans the plug-ins directory for DLLs and makes a list of the plug-ins found
; and their exported functions. During compilation, if a sequence such as fred::flintstone
; is encountered where the compiler expected to find a language keyword the compiler will look through this list.
; If a list entry specifies that fred.dll exports function flintstone NSIS will pack the fred.dll file 
; into the created installer binary.

; During execution of a plug-in command NSIS will unpack the necessary DLL to a temporary folder ($PLUGINSDIR),
; push all of the arguments specified (right-to-left order), and then execute the DLL function.