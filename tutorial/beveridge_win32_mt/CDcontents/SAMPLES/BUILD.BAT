@echo off
if not "%INCLUDE%" == "" goto okay
echo.
echo Your environment is not configured to run the Visual C++
echo command line compiler.  To set up the environment, run
echo \MSDEV\BIN\VCVARS32.BAT
echo 
goto done
:okay

echo ---- BackPrnt
cd BackPrnt
nmake -nologo -f BackPrnt.mak CFG="BackPrnt - Win32 Release" %1
REM -- This file is not supposed to compile correctly.
REM echo ---- BadClass
REM cd ..\BadClass
REM nmake -nologo -f BadClass.mak CFG="BadClass - Win32 Release" %1
echo ---- Banner
cd ..\Banner
nmake -nologo -f Banner.mak CFG="Banner - Win32 Release" %1
echo ---- Busy2
cd ..\Busy2
nmake -nologo -f Busy2.mak CFG="Busy2 - Win32 Release" %1
echo ---- Busy3
cd ..\Busy3
nmake -nologo -f Busy3.mak CFG="Busy3 - Win32 Release" %1
echo ---- BusyPrio
cd ..\BusyPrio
nmake -nologo -f BusyPrio.mak CFG="BusyPrio - Win32 Release" %1
echo ---- BusyWait
cd ..\BusyWait
nmake -nologo -f BusyWait.mak CFG="BusyWait - Win32 Release" %1
echo ---- Cancel
cd ..\Cancel
nmake -nologo -f Cancel.mak CFG="Cancel - Win32 Release" %1
echo ---- ComDemo
cd ..\ComDemo
nmake -nologo -f ComDemo.mak CFG="ComDemo - Win32 Release" %1
echo ---- ComDemo\MfcCli
cd MfcCli
nmake -nologo -f MfcCli.mak CFG="MfcCli - Win32 Release" %1
cd ..\..
echo ---- CppSkel
cd CppSkel
nmake -nologo -f CppSkel.mak CFG="CppSkel - Win32 Release" %1
echo ---- Dining
cd ..\Dining
nmake -nologo -f Dining.mak CFG="Dining - Win32 Release" %1
echo ---- Error
cd ..\Error
nmake -nologo -f Error.mak CFG="Error - Win32 Release" %1
echo ---- EventTst
cd ..\EventTst
nmake -nologo -f EventTst.mak CFG="EventTst - Win32 Release" %1
echo ---- ExitCode
cd ..\ExitCode
nmake -nologo -f ExitCode.mak CFG="ExitCode - Win32 Release" %1
echo ---- ExitThrd
cd ..\ExitThrd
nmake -nologo -f ExitThrd.mak CFG="ExitThrd - Win32 Release" %1
echo ---- IoByAPC
cd ..\IoByAPC
nmake -nologo -f IoByAPC.mak CFG="IoByAPC - Win32 Release" %1
echo ---- IoByEvnt
cd ..\IoByEvnt
nmake -nologo -f IoByEvnt.mak CFG="IoByEvnt - Win32 Release" %1
echo ---- IoByFile
cd ..\IoByFile
nmake -nologo -f IoByFile.mak CFG="IoByFile - Win32 Release" %1
echo ---- Is2odbc
cd ..\Is2odbc
nmake -nologo -f Is2Odbc.mak CFG="Is2Odbc - Win32 Release" %1
echo ---- Member
cd ..\Member
nmake -nologo -f Member.mak CFG="Member - Win32 Release" %1
nmake -nologo -f Member2.mak CFG="Member2 - Win32 Release" %1
echo ---- NumClass
cd ..\NumClass
nmake -nologo -f NumClass.mak CFG="NumClass - Win32 Release" %1
echo ---- Numbers
cd ..\Numbers
nmake -nologo -f Numbers.mak CFG="Numbers - Win32 Release" %1
echo ---- Numbers
cd ..\NumbersP
nmake -nologo -f numbers.mak CFG="numbers - Win32 Release" %1
echo ---- Numbers2
cd ..\Numbers2
nmake -nologo -f Numbers2.mak CFG="Numbers2 - Win32 Release" %1
echo ---- PrntWait
cd ..\PrntWait
nmake -nologo -f PrntWait.mak CFG="PrntWait - Win32 Release" %1
echo ---- ReadWrit
cd ..\ReadWrit
nmake -nologo -f ReadWrit.mak CFG="ReadWrit - Win32 Release" %1
echo ---- ShareMem
cd ..\ShareMem
nmake -nologo -f ShareMem.mak CFG="ShareMem - Win32 Release" %1
echo ---- SmallDll
cd ..\SmallDll
nmake -nologo -f SmallDll.mak CFG="SmallDll - Win32 Release" %1
nmake -nologo -f main1.mak CFG="Main1 - Win32 Release" %1
nmake -nologo -f main2.mak CFG="Main2 - Win32 Release" %1
nmake -nologo -f Main3.mak CFG="Main3 - Win32 Release" %1
echo ---- SrchCrt
cd ..\SrchCrt
nmake -nologo -f SrchCrt.mak CFG="SrchCrt - Win32 Release" %1
echo ---- SrchWin
cd ..\SrchWin
nmake -nologo -f SrchWin.mak CFG="SrchWin - Win32 Release" %1
echo ---- TaskQueM
cd ..\TaskQueM
nmake -nologo -f TaskQueM.mak CFG="TaskQueM - Win32 Release" %1
echo ---- TaskQueS
cd ..\TaskQueS
nmake -nologo -f TaskQueS.mak CFG="TaskQueS - Win32 Release" %1
echo ---- ThrdTerm
cd ..\ThrdTerm
nmake -nologo -f ThrdTerm.mak CFG="ThrdTerm - Win32 Release" %1
echo ---- Worker
cd ..\Worker
nmake -nologo -f worker.mak CFG="Worker - Win32 Release" %1
echo ---- CopyData\CopyRecv
cd ..\CopyData\CopyRecv
nmake -nologo -f CopyRecv.mak CFG="CopyRecv - Win32 Release" %1
echo ---- CopyData\CopySend
cd ..\CopySend
nmake -nologo -f CopySend.mak CFG="CopySend - Win32 Release" %1
echo ---- Echo\EchoCli
cd ..\..\Echo\EchoCli
nmake -nologo -f EchoCli.mak CFG="EchoCli - Win32 Release" %1
echo ---- Echo\EchoSrv
cd ..\EchoSrv
nmake -nologo -f EchoSrv.mak CFG="EchoSrv - Win32 Release" %1
cd ..\..
echo ---- Is2odbc\DbServer
cd Is2odbc\DbServer
nmake -nologo -f DbServer.mak CFG="DbServer - Win32 Release" %1
cd ..\..

:done
