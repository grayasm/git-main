# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Cancel - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Cancel - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Cancel - Win32 Release" && "$(CFG)" != "Cancel - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Cancel.mak" CFG="Cancel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Cancel - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Cancel - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Cancel - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "Cancel - Win32 Release"

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

ALL : "$(OUTDIR)\Cancel.exe"

CLEAN : 
	-@erase "$(INTDIR)\CancDoc.obj"
	-@erase "$(INTDIR)\Cancel.obj"
	-@erase "$(INTDIR)\Cancel.pch"
	-@erase "$(INTDIR)\Cancel.res"
	-@erase "$(INTDIR)\CancView.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\OutDlg.obj"
	-@erase "$(INTDIR)\OutpThrd.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Cancel.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Od /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Od /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Cancel.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Cancel.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Cancel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Cancel.pdb" /machine:I386 /out:"$(OUTDIR)/Cancel.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CancDoc.obj" \
	"$(INTDIR)\Cancel.obj" \
	"$(INTDIR)\Cancel.res" \
	"$(INTDIR)\CancView.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\OutDlg.obj" \
	"$(INTDIR)\OutpThrd.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Cancel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"

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

ALL : "$(OUTDIR)\Cancel.exe" "$(OUTDIR)\Cancel.bsc"

CLEAN : 
	-@erase "$(INTDIR)\CancDoc.obj"
	-@erase "$(INTDIR)\CancDoc.sbr"
	-@erase "$(INTDIR)\Cancel.obj"
	-@erase "$(INTDIR)\Cancel.pch"
	-@erase "$(INTDIR)\Cancel.res"
	-@erase "$(INTDIR)\Cancel.sbr"
	-@erase "$(INTDIR)\CancView.obj"
	-@erase "$(INTDIR)\CancView.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\OutDlg.obj"
	-@erase "$(INTDIR)\OutDlg.sbr"
	-@erase "$(INTDIR)\OutpThrd.obj"
	-@erase "$(INTDIR)\OutpThrd.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Cancel.bsc"
	-@erase "$(OUTDIR)\Cancel.exe"
	-@erase "$(OUTDIR)\Cancel.ilk"
	-@erase "$(OUTDIR)\Cancel.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Cancel.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Cancel.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Cancel.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CancDoc.sbr" \
	"$(INTDIR)\Cancel.sbr" \
	"$(INTDIR)\CancView.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\OutDlg.sbr" \
	"$(INTDIR)\OutpThrd.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Cancel.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Cancel.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Cancel.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CancDoc.obj" \
	"$(INTDIR)\Cancel.obj" \
	"$(INTDIR)\Cancel.res" \
	"$(INTDIR)\CancView.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\OutDlg.obj" \
	"$(INTDIR)\OutpThrd.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Cancel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Cancel - Win32 Release"
# Name "Cancel - Win32 Debug"

!IF  "$(CFG)" == "Cancel - Win32 Release"

!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Cancel - Win32 Release"

!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cancel.cpp
DEP_CPP_CANCE=\
	".\CancDoc.h"\
	".\Cancel.h"\
	".\CancView.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Cancel - Win32 Release"


"$(INTDIR)\Cancel.obj" : $(SOURCE) $(DEP_CPP_CANCE) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"


"$(INTDIR)\Cancel.obj" : $(SOURCE) $(DEP_CPP_CANCE) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"

"$(INTDIR)\Cancel.sbr" : $(SOURCE) $(DEP_CPP_CANCE) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Cancel - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /Od /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Cancel.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Cancel.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Cancel.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Cancel.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\Cancel.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Cancel - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\Cancel.h"\
	".\ChildFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Cancel - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cancel.rc
DEP_RSC_CANCEL=\
	".\res\CancDoc.ico"\
	".\res\Cancel.ico"\
	".\res\Cancel.rc2"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Cancel.res" : $(SOURCE) $(DEP_RSC_CANCEL) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\OutDlg.CPP
DEP_CPP_OUTDL=\
	".\Cancel.h"\
	".\MainFrm.h"\
	".\OutDlg.h"\
	".\OutpThrd.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Cancel - Win32 Release"


"$(INTDIR)\OutDlg.obj" : $(SOURCE) $(DEP_CPP_OUTDL) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"


"$(INTDIR)\OutDlg.obj" : $(SOURCE) $(DEP_CPP_OUTDL) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"

"$(INTDIR)\OutDlg.sbr" : $(SOURCE) $(DEP_CPP_OUTDL) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OutpThrd.cpp
DEP_CPP_OUTPT=\
	".\Cancel.h"\
	".\OutDlg.h"\
	".\OutpThrd.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Cancel - Win32 Release"


"$(INTDIR)\OutpThrd.obj" : $(SOURCE) $(DEP_CPP_OUTPT) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"


"$(INTDIR)\OutpThrd.obj" : $(SOURCE) $(DEP_CPP_OUTPT) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"

"$(INTDIR)\OutpThrd.sbr" : $(SOURCE) $(DEP_CPP_OUTPT) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CancDoc.cpp
DEP_CPP_CANCD=\
	".\CancDoc.h"\
	".\Cancel.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Cancel - Win32 Release"


"$(INTDIR)\CancDoc.obj" : $(SOURCE) $(DEP_CPP_CANCD) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"


"$(INTDIR)\CancDoc.obj" : $(SOURCE) $(DEP_CPP_CANCD) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"

"$(INTDIR)\CancDoc.sbr" : $(SOURCE) $(DEP_CPP_CANCD) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CancView.cpp
DEP_CPP_CANCV=\
	".\CancDoc.h"\
	".\Cancel.h"\
	".\CancView.h"\
	".\OutDlg.h"\
	".\OutpThrd.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Cancel - Win32 Release"


"$(INTDIR)\CancView.obj" : $(SOURCE) $(DEP_CPP_CANCV) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ELSEIF  "$(CFG)" == "Cancel - Win32 Debug"


"$(INTDIR)\CancView.obj" : $(SOURCE) $(DEP_CPP_CANCV) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"

"$(INTDIR)\CancView.sbr" : $(SOURCE) $(DEP_CPP_CANCV) "$(INTDIR)"\
 "$(INTDIR)\Cancel.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
