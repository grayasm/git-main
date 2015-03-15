# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=BackPrnt - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to BackPrnt - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "BackPrnt - Win32 Release" && "$(CFG)" !=\
 "BackPrnt - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "BackPrnt.mak" CFG="BackPrnt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BackPrnt - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BackPrnt - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "BackPrnt - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "BackPrnt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\BackPrnt.exe"

CLEAN : 
	-@erase "$(INTDIR)\BackPrnt.obj"
	-@erase "$(INTDIR)\BackPrnt.res"
	-@erase "$(OUTDIR)\BackPrnt.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/BackPrnt.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/BackPrnt.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BackPrnt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/BackPrnt.pdb" /machine:I386\
 /out:"$(OUTDIR)/BackPrnt.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BackPrnt.obj" \
	"$(INTDIR)\BackPrnt.res"

"$(OUTDIR)\BackPrnt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "BackPrnt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\BackPrnt.exe" "$(OUTDIR)\BackPrnt.bsc"

CLEAN : 
	-@erase "$(INTDIR)\BackPrnt.obj"
	-@erase "$(INTDIR)\BackPrnt.res"
	-@erase "$(INTDIR)\BackPrnt.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\BackPrnt.bsc"
	-@erase "$(OUTDIR)\BackPrnt.exe"
	-@erase "$(OUTDIR)\BackPrnt.ilk"
	-@erase "$(OUTDIR)\BackPrnt.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/BackPrnt.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/BackPrnt.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BackPrnt.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BackPrnt.sbr"

"$(OUTDIR)\BackPrnt.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=vfw32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/BackPrnt.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/BackPrnt.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BackPrnt.obj" \
	"$(INTDIR)\BackPrnt.res"

"$(OUTDIR)\BackPrnt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "BackPrnt - Win32 Release"
# Name "BackPrnt - Win32 Debug"

!IF  "$(CFG)" == "BackPrnt - Win32 Release"

!ELSEIF  "$(CFG)" == "BackPrnt - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\BackPrnt.rc
DEP_RSC_BACKP=\
	".\BackPrnt.ico"\
	

"$(INTDIR)\BackPrnt.res" : $(SOURCE) $(DEP_RSC_BACKP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BackPrnt.c
DEP_CPP_BACKPR=\
	"..\MtVerify.h"\
	

!IF  "$(CFG)" == "BackPrnt - Win32 Release"


"$(INTDIR)\BackPrnt.obj" : $(SOURCE) $(DEP_CPP_BACKPR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "BackPrnt - Win32 Debug"


"$(INTDIR)\BackPrnt.obj" : $(SOURCE) $(DEP_CPP_BACKPR) "$(INTDIR)"

"$(INTDIR)\BackPrnt.sbr" : $(SOURCE) $(DEP_CPP_BACKPR) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
