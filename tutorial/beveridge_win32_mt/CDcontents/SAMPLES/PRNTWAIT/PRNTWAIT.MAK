# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=PrntWait - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to PrntWait - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PrntWait - Win32 Release" && "$(CFG)" !=\
 "PrntWait - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "PrntWait.mak" CFG="PrntWait - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PrntWait - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PrntWait - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "PrntWait - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "PrntWait - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "..\TempCR"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\..\TempCR

ALL : "$(OUTDIR)\PrntWait.exe"

CLEAN : 
	-@erase "$(INTDIR)\PrntWait.obj"
	-@erase "$(INTDIR)\PrntWait.res"
	-@erase "$(OUTDIR)\PrntWait.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"..\TempCR/Multithd.pch" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Multithd.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\..\TempCR/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/PrntWait.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PrntWait.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/PrntWait.pdb" /machine:I386\
 /out:"$(OUTDIR)/PrntWait.exe" 
LINK32_OBJS= \
	"$(INTDIR)\PrntWait.obj" \
	"$(INTDIR)\PrntWait.res"

"$(OUTDIR)\PrntWait.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PrntWait - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "..\TempCD"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\..\TempCD

ALL : "$(OUTDIR)\PrntWait.exe" "$(OUTDIR)\PrntWait.bsc"

CLEAN : 
	-@erase "$(INTDIR)\PrntWait.obj"
	-@erase "$(INTDIR)\PrntWait.res"
	-@erase "$(INTDIR)\PrntWait.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\PrntWait.bsc"
	-@erase "$(OUTDIR)\PrntWait.exe"
	-@erase "$(OUTDIR)\PrntWait.ilk"
	-@erase "$(OUTDIR)\PrntWait.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Fp"..\TempCD/Multithd.pch" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Multithd.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\..\TempCD/
CPP_SBRS=.\..\TempCD/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/PrntWait.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PrntWait.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\PrntWait.sbr"

"$(OUTDIR)\PrntWait.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/PrntWait.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/PrntWait.exe" 
LINK32_OBJS= \
	"$(INTDIR)\PrntWait.obj" \
	"$(INTDIR)\PrntWait.res"

"$(OUTDIR)\PrntWait.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "PrntWait - Win32 Release"
# Name "PrntWait - Win32 Debug"

!IF  "$(CFG)" == "PrntWait - Win32 Release"

!ELSEIF  "$(CFG)" == "PrntWait - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\PrntWait.c
DEP_CPP_PRNTW=\
	"..\MtVerify.h"\
	

!IF  "$(CFG)" == "PrntWait - Win32 Release"


"$(INTDIR)\PrntWait.obj" : $(SOURCE) $(DEP_CPP_PRNTW) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PrntWait - Win32 Debug"


"$(INTDIR)\PrntWait.obj" : $(SOURCE) $(DEP_CPP_PRNTW) "$(INTDIR)"

"$(INTDIR)\PrntWait.sbr" : $(SOURCE) $(DEP_CPP_PRNTW) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PrntWait.rc
DEP_RSC_PRNTWA=\
	".\PrntWait.ico"\
	

"$(INTDIR)\PrntWait.res" : $(SOURCE) $(DEP_RSC_PRNTWA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
