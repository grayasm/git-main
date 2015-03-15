# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=DbServer - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DbServer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DbServer - Win32 Release" && "$(CFG)" !=\
 "DbServer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DbServer.mak" CFG="DbServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DbServer - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "DbServer - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "DbServer - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DbServer - Win32 Release"

# PROP BASE Use_MFC 0
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

ALL : "$(OUTDIR)\DbServer.exe"

CLEAN : 
	-@erase "$(INTDIR)\BookSet.obj"
	-@erase "$(INTDIR)\DbServer.obj"
	-@erase "$(INTDIR)\DbServer.pch"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(OUTDIR)\DbServer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\.." /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\.." /D "NDEBUG" /D "WIN32" /D\
 "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DbServer.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DbServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386
# SUBTRACT LINK32 /map /nodefaultlib
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/DbServer.pdb" /machine:I386 /out:"$(OUTDIR)/DbServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BookSet.obj" \
	"$(INTDIR)\DbServer.obj" \
	"$(INTDIR)\STDAFX.OBJ"

"$(OUTDIR)\DbServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DbServer - Win32 Debug"

# PROP BASE Use_MFC 0
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

ALL : "$(OUTDIR)\DbServer.exe" "$(OUTDIR)\DbServer.bsc"

CLEAN : 
	-@erase "$(INTDIR)\BookSet.obj"
	-@erase "$(INTDIR)\BookSet.sbr"
	-@erase "$(INTDIR)\DbServer.obj"
	-@erase "$(INTDIR)\DbServer.pch"
	-@erase "$(INTDIR)\DbServer.sbr"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STDAFX.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\DbServer.bsc"
	-@erase "$(OUTDIR)\DbServer.exe"
	-@erase "$(OUTDIR)\DbServer.ilk"
	-@erase "$(OUTDIR)\DbServer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\.." /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\.." /D "_DEBUG" /D "WIN32" /D\
 "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/DbServer.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DbServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BookSet.sbr" \
	"$(INTDIR)\DbServer.sbr" \
	"$(INTDIR)\STDAFX.SBR"

"$(OUTDIR)\DbServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386
# SUBTRACT LINK32 /map /nodefaultlib
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/DbServer.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/DbServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BookSet.obj" \
	"$(INTDIR)\DbServer.obj" \
	"$(INTDIR)\STDAFX.OBJ"

"$(OUTDIR)\DbServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DbServer - Win32 Release"
# Name "DbServer - Win32 Debug"

!IF  "$(CFG)" == "DbServer - Win32 Release"

!ELSEIF  "$(CFG)" == "DbServer - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DbServer.cpp
DEP_CPP_DBSER=\
	"..\..\MtVerify.h"\
	"..\Request.h"\
	".\BookSet.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "DbServer - Win32 Release"


"$(INTDIR)\DbServer.obj" : $(SOURCE) $(DEP_CPP_DBSER) "$(INTDIR)"\
 "$(INTDIR)\DbServer.pch"


!ELSEIF  "$(CFG)" == "DbServer - Win32 Debug"


"$(INTDIR)\DbServer.obj" : $(SOURCE) $(DEP_CPP_DBSER) "$(INTDIR)"\
 "$(INTDIR)\DbServer.pch"

"$(INTDIR)\DbServer.sbr" : $(SOURCE) $(DEP_CPP_DBSER) "$(INTDIR)"\
 "$(INTDIR)\DbServer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "DbServer - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\.." /D "NDEBUG" /D "WIN32" /D "_CONSOLE"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DbServer.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DbServer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "DbServer - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\.." /D "_DEBUG" /D "WIN32" /D\
 "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/DbServer.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\STDAFX.SBR" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DbServer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BookSet.cpp
DEP_CPP_BOOKS=\
	".\BookSet.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "DbServer - Win32 Release"


"$(INTDIR)\BookSet.obj" : $(SOURCE) $(DEP_CPP_BOOKS) "$(INTDIR)"\
 "$(INTDIR)\DbServer.pch"


!ELSEIF  "$(CFG)" == "DbServer - Win32 Debug"


"$(INTDIR)\BookSet.obj" : $(SOURCE) $(DEP_CPP_BOOKS) "$(INTDIR)"\
 "$(INTDIR)\DbServer.pch"

"$(INTDIR)\BookSet.sbr" : $(SOURCE) $(DEP_CPP_BOOKS) "$(INTDIR)"\
 "$(INTDIR)\DbServer.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
