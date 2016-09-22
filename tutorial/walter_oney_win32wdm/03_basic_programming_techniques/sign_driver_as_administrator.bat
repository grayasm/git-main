
set DRIVE=D:
set DRIVER_PATH="%DRIVE%/workdir/GitHub/git-main/tutorial/walter_oney_win32wdm/03_basic_programming_techniques-b/install-generic"
set INF2CAT="C:/Program Files (x86)/Windows Kits/10/bin/x86/Inf2Cat.exe"


cd %DRIVER_PATH%
%DRIVE%
cd

@rem	Create the .cat with signatures for all files in the driver package (.sys, .dll, .inf, etc).
call %INF2CAT% /driver:. /os:10_x64

@rem	Start the VS cmd tool, sign the catalog and show dialog info for confirmation.
call "D:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/vcvarsall.bat" x86_amd64

signtool sign /s ModuleWorksCertStore /n "ModuleWorks - for test use only"  /t http://timestamp.verisign.com/scripts/timestamp.dll  genericamd64.cat 

start genericamd64.cat

pause