# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Dining - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dining - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dining - Win32 Release" && "$(CFG)" != "Dining - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dining.mak" CFG="Dining - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dining - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Dining - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Dining - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "Dining - Win32 Release"

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

ALL : "$(OUTDIR)\Dining.exe"

CLEAN : 
	-@erase "$(INTDIR)\Dining.obj"
	-@erase "$(INTDIR)\Dining.res"
	-@erase "$(INTDIR)\Mutex.obj"
	-@erase "$(OUTDIR)\Dining.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"windows.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Dining.pch" /YX"windows.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dining.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dining.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Dining.pdb" /machine:I386\
 /out:"$(OUTDIR)/Dining.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Dining.obj" \
	"$(INTDIR)\Dining.res" \
	"$(INTDIR)\Mutex.obj"

"$(OUTDIR)\Dining.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dining - Win32 Debug"

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

ALL : "$(OUTDIR)\Dining.exe"

CLEAN : 
	-@erase "$(INTDIR)\Dining.obj"
	-@erase "$(INTDIR)\Dining.res"
	-@erase "$(INTDIR)\Mutex.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Dining.exe"
	-@erase "$(OUTDIR)\Dining.ilk"
	-@erase "$(OUTDIR)\Dining.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /ML /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX"windows.h" /c
CPP_PROJ=/nologo /ML /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/Dining.pch" /YX"windows.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dining.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dining.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /debug /machine:I386 /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /incremental:yes /pdb:"$(OUTDIR)/Dining.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Dining.exe" /subsystem:windows,4.0 
LINK32_OBJS= \
	"$(INTDIR)\Dining.obj" \
	"$(INTDIR)\Dining.res" \
	"$(INTDIR)\Mutex.obj"

"$(OUTDIR)\Dining.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Dining - Win32 Release"
# Name "Dining - Win32 Debug"

!IF  "$(CFG)" == "Dining - Win32 Release"

!ELSEIF  "$(CFG)" == "Dining - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dining.C
DEP_CPP_DININ=\
	".\Dining.H"\
	

"$(INTDIR)\Dining.obj" : $(SOURCE) $(DEP_CPP_DININ) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mutex.c
DEP_CPP_MUTEX=\
	"..\MtVerify.h"\
	".\Dining.H"\
	

"$(INTDIR)\Mutex.obj" : $(SOURCE) $(DEP_CPP_MUTEX) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dining.RC

"$(INTDIR)\Dining.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
