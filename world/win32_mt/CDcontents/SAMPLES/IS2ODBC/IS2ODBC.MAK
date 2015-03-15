# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Is2Odbc - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Is2Odbc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Is2Odbc - Win32 Release" && "$(CFG)" !=\
 "Is2Odbc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Is2Odbc.mak" CFG="Is2Odbc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Is2Odbc - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Is2Odbc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Is2Odbc - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Is2Odbc - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Is2Odbc.dll"

CLEAN : 
	-@erase "$(INTDIR)\IS2ODBC.OBJ"
	-@erase "$(INTDIR)\Is2Odbc.pch"
	-@erase "$(INTDIR)\IS2ODBC.res"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(OUTDIR)\Is2Odbc.dll"
	-@erase "$(OUTDIR)\Is2Odbc.exp"
	-@erase "$(OUTDIR)\Is2Odbc.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Is2Odbc.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/IS2ODBC.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Is2Odbc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Is2Odbc.pdb" /machine:I386 /def:".\IS2ODBC.DEF"\
 /out:"$(OUTDIR)/Is2Odbc.dll" /implib:"$(OUTDIR)/Is2Odbc.lib" 
DEF_FILE= \
	".\IS2ODBC.DEF"
LINK32_OBJS= \
	"$(INTDIR)\IS2ODBC.OBJ" \
	"$(INTDIR)\IS2ODBC.res" \
	"$(INTDIR)\STDAFX.OBJ"

"$(OUTDIR)\Is2Odbc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Is2Odbc - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Is2Odbc.dll" "$(OUTDIR)\Is2Odbc.bsc"

CLEAN : 
	-@erase "$(INTDIR)\IS2ODBC.OBJ"
	-@erase "$(INTDIR)\Is2Odbc.pch"
	-@erase "$(INTDIR)\IS2ODBC.res"
	-@erase "$(INTDIR)\IS2ODBC.SBR"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STDAFX.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Is2Odbc.bsc"
	-@erase "$(OUTDIR)\Is2Odbc.dll"
	-@erase "$(OUTDIR)\Is2Odbc.exp"
	-@erase "$(OUTDIR)\Is2Odbc.ilk"
	-@erase "$(OUTDIR)\Is2Odbc.lib"
	-@erase "$(OUTDIR)\Is2Odbc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Is2Odbc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/IS2ODBC.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Is2Odbc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\IS2ODBC.SBR" \
	"$(INTDIR)\STDAFX.SBR"

"$(OUTDIR)\Is2Odbc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Is2Odbc.pdb" /debug /machine:I386 /def:".\IS2ODBC.DEF"\
 /out:"$(OUTDIR)/Is2Odbc.dll" /implib:"$(OUTDIR)/Is2Odbc.lib" 
DEF_FILE= \
	".\IS2ODBC.DEF"
LINK32_OBJS= \
	"$(INTDIR)\IS2ODBC.OBJ" \
	"$(INTDIR)\IS2ODBC.res" \
	"$(INTDIR)\STDAFX.OBJ"

"$(OUTDIR)\Is2Odbc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Is2Odbc - Win32 Release"
# Name "Is2Odbc - Win32 Debug"

!IF  "$(CFG)" == "Is2Odbc - Win32 Release"

!ELSEIF  "$(CFG)" == "Is2Odbc - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\IS2ODBC.DEF

!IF  "$(CFG)" == "Is2Odbc - Win32 Release"

!ELSEIF  "$(CFG)" == "Is2Odbc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IS2ODBC.CPP
DEP_CPP_IS2OD=\
	".\IS2ODBC.H"\
	"..\MtVerify.h"\
	".\Request.h"\
	".\STDAFX.H"\
	{$(INCLUDE)}"\afxisapi.h"\
	{$(INCLUDE)}"\afxisapi.inl"\
	{$(INCLUDE)}"\httpext.h"\
	{$(INCLUDE)}"\httpfilt.h"\
	

!IF  "$(CFG)" == "Is2Odbc - Win32 Release"


"$(INTDIR)\IS2ODBC.OBJ" : $(SOURCE) $(DEP_CPP_IS2OD) "$(INTDIR)"\
 "$(INTDIR)\Is2Odbc.pch"


!ELSEIF  "$(CFG)" == "Is2Odbc - Win32 Debug"


"$(INTDIR)\IS2ODBC.OBJ" : $(SOURCE) $(DEP_CPP_IS2OD) "$(INTDIR)"\
 "$(INTDIR)\Is2Odbc.pch"

"$(INTDIR)\IS2ODBC.SBR" : $(SOURCE) $(DEP_CPP_IS2OD) "$(INTDIR)"\
 "$(INTDIR)\Is2Odbc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IS2ODBC.RC

"$(INTDIR)\IS2ODBC.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_CPP_STDAF=\
	".\STDAFX.H"\
	{$(INCLUDE)}"\afxisapi.h"\
	{$(INCLUDE)}"\afxisapi.inl"\
	{$(INCLUDE)}"\httpext.h"\
	{$(INCLUDE)}"\httpfilt.h"\
	

!IF  "$(CFG)" == "Is2Odbc - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Is2Odbc.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Is2Odbc.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Is2Odbc - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Is2Odbc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\STDAFX.SBR" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Is2Odbc.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
