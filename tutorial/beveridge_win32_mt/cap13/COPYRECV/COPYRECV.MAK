# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=CopyRecv - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to CopyRecv - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CopyRecv - Win32 Release" && "$(CFG)" !=\
 "CopyRecv - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "CopyRecv.mak" CFG="CopyRecv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CopyRecv - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CopyRecv - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "CopyRecv - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "CopyRecv - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\CopyRecv.exe"

CLEAN : 
	-@erase "$(INTDIR)\CdDoc.obj"
	-@erase "$(INTDIR)\CdView.obj"
	-@erase "$(INTDIR)\CopyData.obj"
	-@erase "$(INTDIR)\CopyRecv.pch"
	-@erase "$(INTDIR)\CopyRecv.res"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\CopyRecv.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../.." /I "..\.." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../.." /I "..\.." /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CopyRecv.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CopyRecv.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CopyRecv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/CopyRecv.pdb" /machine:I386 /out:"$(OUTDIR)/CopyRecv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CdDoc.obj" \
	"$(INTDIR)\CdView.obj" \
	"$(INTDIR)\CopyData.obj" \
	"$(INTDIR)\CopyRecv.res" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CopyRecv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CopyRecv - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\CopyRecv.exe"

CLEAN : 
	-@erase "$(INTDIR)\CdDoc.obj"
	-@erase "$(INTDIR)\CdView.obj"
	-@erase "$(INTDIR)\CopyData.obj"
	-@erase "$(INTDIR)\CopyRecv.pch"
	-@erase "$(INTDIR)\CopyRecv.res"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\CopyRecv.exe"
	-@erase "$(OUTDIR)\CopyRecv.ilk"
	-@erase "$(OUTDIR)\CopyRecv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CopyRecv.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CopyRecv.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CopyRecv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/CopyRecv.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/CopyRecv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CdDoc.obj" \
	"$(INTDIR)\CdView.obj" \
	"$(INTDIR)\CopyData.obj" \
	"$(INTDIR)\CopyRecv.res" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CopyRecv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "CopyRecv - Win32 Release"
# Name "CopyRecv - Win32 Debug"

!IF  "$(CFG)" == "CopyRecv - Win32 Release"

!ELSEIF  "$(CFG)" == "CopyRecv - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\CopyRecv\stdafx.h"\
	

!IF  "$(CFG)" == "CopyRecv - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "../.." /I "..\.." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CopyRecv.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CopyRecv.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CopyRecv - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CopyRecv.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CopyRecv.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CdView.cpp
DEP_CPP_CDVIE=\
	"..\CopyRecv\CdDoc.h"\
	"..\CopyRecv\CdView.h"\
	"..\CopyRecv\CopyData.h"\
	"..\CopyRecv\stdafx.h"\
	

"$(INTDIR)\CdView.obj" : $(SOURCE) $(DEP_CPP_CDVIE) "$(INTDIR)"\
 "$(INTDIR)\CopyRecv.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CopyData.cpp
DEP_CPP_COPYD=\
	"..\CopyRecv\CdDoc.h"\
	"..\CopyRecv\CdView.h"\
	"..\CopyRecv\CopyData.h"\
	"..\CopyRecv\MainFrm.h"\
	"..\CopyRecv\stdafx.h"\
	

"$(INTDIR)\CopyData.obj" : $(SOURCE) $(DEP_CPP_COPYD) "$(INTDIR)"\
 "$(INTDIR)\CopyRecv.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\CopyRecv\CopyData.h"\
	"..\CopyRecv\MainFrm.h"\
	"..\CopyRecv\stdafx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\CopyRecv.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CdDoc.cpp
DEP_CPP_CDDOC=\
	"..\CopyRecv\CdDoc.h"\
	"..\CopyRecv\CopyData.h"\
	"..\CopyRecv\stdafx.h"\
	

"$(INTDIR)\CdDoc.obj" : $(SOURCE) $(DEP_CPP_CDDOC) "$(INTDIR)"\
 "$(INTDIR)\CopyRecv.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CopyRecv.rc
DEP_RSC_COPYR=\
	"..\CopyRecv\res\CdDoc.ico"\
	"..\CopyRecv\res\CopyRecv.ico"\
	"..\CopyRecv\res\CopyRecv.rc2"\
	

"$(INTDIR)\CopyRecv.res" : $(SOURCE) $(DEP_RSC_COPYR) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
