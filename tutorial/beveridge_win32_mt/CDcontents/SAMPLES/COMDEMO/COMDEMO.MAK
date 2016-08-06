# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=ComDemo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ComDemo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ComDemo - Win32 Release" && "$(CFG)" !=\
 "ComDemo - Win32 Debug" && "$(CFG)" != "ComDemo - Win32 Unicode Release" &&\
 "$(CFG)" != "ComDemo - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComDemo.mak" CFG="ComDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComDemo - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComDemo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComDemo - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComDemo - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "ComDemo - Win32 Unicode Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "ComDemo - Win32 Release"

# PROP BASE Use_MFC 1
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
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ComDemo.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\AutoIncr.obj"
	-@erase "$(INTDIR)\ComDemo.obj"
	-@erase "$(INTDIR)\ComDemo.pch"
	-@erase "$(INTDIR)\ComDemo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\ComDemo.dll"
	-@erase "$(OUTDIR)\ComDemo.exp"
	-@erase "$(OUTDIR)\ComDemo.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\ComDemo.h"
	-@erase ".\ComDemo.tlb"
	-@erase ".\ComDemo_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ComDemo.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ComDemo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ComDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ComDemo.pdb" /machine:I386 /def:".\ComDemo.def"\
 /out:"$(OUTDIR)/ComDemo.dll" /implib:"$(OUTDIR)/ComDemo.lib" 
DEF_FILE= \
	".\ComDemo.def"
LINK32_OBJS= \
	"$(INTDIR)\AutoIncr.obj" \
	"$(INTDIR)\ComDemo.obj" \
	"$(INTDIR)\ComDemo.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ComDemo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\ComDemo.dll
InputPath=.\Release\ComDemo.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ComDemo.dll" "$(OUTDIR)\ComDemo.bsc" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\AutoIncr.obj"
	-@erase "$(INTDIR)\AutoIncr.sbr"
	-@erase "$(INTDIR)\ComDemo.obj"
	-@erase "$(INTDIR)\ComDemo.pch"
	-@erase "$(INTDIR)\ComDemo.res"
	-@erase "$(INTDIR)\ComDemo.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ComDemo.bsc"
	-@erase "$(OUTDIR)\ComDemo.dll"
	-@erase "$(OUTDIR)\ComDemo.exp"
	-@erase "$(OUTDIR)\ComDemo.ilk"
	-@erase "$(OUTDIR)\ComDemo.lib"
	-@erase "$(OUTDIR)\ComDemo.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\ComDemo.h"
	-@erase ".\ComDemo.tlb"
	-@erase ".\ComDemo_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/ComDemo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ComDemo.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ComDemo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AutoIncr.sbr" \
	"$(INTDIR)\ComDemo.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ComDemo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ComDemo.pdb" /debug /machine:I386 /def:".\ComDemo.def"\
 /out:"$(OUTDIR)/ComDemo.dll" /implib:"$(OUTDIR)/ComDemo.lib" 
DEF_FILE= \
	".\ComDemo.def"
LINK32_OBJS= \
	"$(INTDIR)\AutoIncr.obj" \
	"$(INTDIR)\ComDemo.obj" \
	"$(INTDIR)\ComDemo.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ComDemo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\ComDemo.dll
InputPath=.\Debug\ComDemo.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Unicode Release"
# PROP BASE Intermediate_Dir "Unicode Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\ComDemo.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\AutoIncr.obj"
	-@erase "$(INTDIR)\ComDemo.obj"
	-@erase "$(INTDIR)\ComDemo.pch"
	-@erase "$(INTDIR)\ComDemo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\ComDemo.dll"
	-@erase "$(OUTDIR)\ComDemo.exp"
	-@erase "$(OUTDIR)\ComDemo.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\ComDemo.h"
	-@erase ".\ComDemo.tlb"
	-@erase ".\ComDemo_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".." /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I ".." /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/ComDemo.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ComDemo.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ComDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ComDemo.pdb" /machine:I386 /def:".\ComDemo.def"\
 /out:"$(OUTDIR)/ComDemo.dll" /implib:"$(OUTDIR)/ComDemo.lib" 
DEF_FILE= \
	".\ComDemo.def"
LINK32_OBJS= \
	"$(INTDIR)\AutoIncr.obj" \
	"$(INTDIR)\ComDemo.obj" \
	"$(INTDIR)\ComDemo.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ComDemo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\ComDemo.dll
InputPath=.\ReleaseU\ComDemo.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Unicode Debug"
# PROP BASE Intermediate_Dir "Unicode Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\ComDemo.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\AutoIncr.obj"
	-@erase "$(INTDIR)\ComDemo.obj"
	-@erase "$(INTDIR)\ComDemo.pch"
	-@erase "$(INTDIR)\ComDemo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ComDemo.dll"
	-@erase "$(OUTDIR)\ComDemo.exp"
	-@erase "$(OUTDIR)\ComDemo.ilk"
	-@erase "$(OUTDIR)\ComDemo.lib"
	-@erase "$(OUTDIR)\ComDemo.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\ComDemo.h"
	-@erase ".\ComDemo.tlb"
	-@erase ".\ComDemo_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".." /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I ".." /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/ComDemo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ComDemo.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ComDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ComDemo.pdb" /debug /machine:I386 /def:".\ComDemo.def"\
 /out:"$(OUTDIR)/ComDemo.dll" /implib:"$(OUTDIR)/ComDemo.lib" 
DEF_FILE= \
	".\ComDemo.def"
LINK32_OBJS= \
	"$(INTDIR)\AutoIncr.obj" \
	"$(INTDIR)\ComDemo.obj" \
	"$(INTDIR)\ComDemo.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ComDemo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\DebugU
TargetPath=.\DebugU\ComDemo.dll
InputPath=.\DebugU\ComDemo.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

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

# Name "ComDemo - Win32 Release"
# Name "ComDemo - Win32 Debug"
# Name "ComDemo - Win32 Unicode Release"
# Name "ComDemo - Win32 Unicode Debug"

!IF  "$(CFG)" == "ComDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Debug"

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ComDemo - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ComDemo.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ComDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/ComDemo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ComDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /I ".." /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/ComDemo.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ComDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".." /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/ComDemo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ComDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ComDemo.cpp
DEP_CPP_COMDE=\
	".\AutoIncr.h"\
	".\ComDemo.h"\
	".\ComDemo_i.c"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ComDemo - Win32 Release"


"$(INTDIR)\ComDemo.obj" : $(SOURCE) $(DEP_CPP_COMDE) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h" ".\ComDemo_i.c"


!ELSEIF  "$(CFG)" == "ComDemo - Win32 Debug"


"$(INTDIR)\ComDemo.obj" : $(SOURCE) $(DEP_CPP_COMDE) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h" ".\ComDemo_i.c"

"$(INTDIR)\ComDemo.sbr" : $(SOURCE) $(DEP_CPP_COMDE) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h" ".\ComDemo_i.c"


!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Release"


"$(INTDIR)\ComDemo.obj" : $(SOURCE) $(DEP_CPP_COMDE) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h" ".\ComDemo_i.c"


!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Debug"


"$(INTDIR)\ComDemo.obj" : $(SOURCE) $(DEP_CPP_COMDE) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h" ".\ComDemo_i.c"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ComDemo.def

!IF  "$(CFG)" == "ComDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Debug"

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ComDemo.rc
DEP_RSC_COMDEM=\
	".\ComDemo.tlb"\
	

!IF  "$(CFG)" == "ComDemo - Win32 Release"


"$(INTDIR)\ComDemo.res" : $(SOURCE) $(DEP_RSC_COMDEM) "$(INTDIR)"\
 ".\ComDemo.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ComDemo - Win32 Debug"


"$(INTDIR)\ComDemo.res" : $(SOURCE) $(DEP_RSC_COMDEM) "$(INTDIR)"\
 ".\ComDemo.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Release"


"$(INTDIR)\ComDemo.res" : $(SOURCE) $(DEP_RSC_COMDEM) "$(INTDIR)"\
 ".\ComDemo.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Debug"


"$(INTDIR)\ComDemo.res" : $(SOURCE) $(DEP_RSC_COMDEM) "$(INTDIR)"\
 ".\ComDemo.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ComDemo.idl

!IF  "$(CFG)" == "ComDemo - Win32 Release"

# Begin Custom Build
InputPath=.\ComDemo.idl

BuildCmds= \
	midl ComDemo.idl \
	

"ComDemo.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ComDemo.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ComDemo_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Debug"

# Begin Custom Build
InputPath=.\ComDemo.idl

BuildCmds= \
	midl ComDemo.idl \
	

"ComDemo.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ComDemo.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ComDemo_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Release"

# Begin Custom Build
InputPath=.\ComDemo.idl

BuildCmds= \
	midl ComDemo.idl \
	

"ComDemo.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ComDemo.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ComDemo_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Debug"

# Begin Custom Build
InputPath=.\ComDemo.idl

BuildCmds= \
	midl ComDemo.idl \
	

"ComDemo.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ComDemo.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ComDemo_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AutoIncr.cpp
DEP_CPP_AUTOI=\
	".\AutoIncr.h"\
	".\ComDemo.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ComDemo - Win32 Release"


"$(INTDIR)\AutoIncr.obj" : $(SOURCE) $(DEP_CPP_AUTOI) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h"


!ELSEIF  "$(CFG)" == "ComDemo - Win32 Debug"


"$(INTDIR)\AutoIncr.obj" : $(SOURCE) $(DEP_CPP_AUTOI) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h"

"$(INTDIR)\AutoIncr.sbr" : $(SOURCE) $(DEP_CPP_AUTOI) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h"


!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Release"


"$(INTDIR)\AutoIncr.obj" : $(SOURCE) $(DEP_CPP_AUTOI) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h"


!ELSEIF  "$(CFG)" == "ComDemo - Win32 Unicode Debug"


"$(INTDIR)\AutoIncr.obj" : $(SOURCE) $(DEP_CPP_AUTOI) "$(INTDIR)"\
 "$(INTDIR)\ComDemo.pch" ".\ComDemo.h"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
