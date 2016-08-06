# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MfcCli - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MfcCli - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MfcCli - Win32 Release" && "$(CFG)" != "MfcCli - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MfcCli.mak" CFG="MfcCli - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MfcCli - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MfcCli - Win32 Debug" (based on "Win32 (x86) Application")
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
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "MfcCli - Win32 Release"

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

ALL : "$(OUTDIR)\MfcCli.exe" "$(OUTDIR)\MfcCli.tlb"

CLEAN : 
	-@erase "$(INTDIR)\MfcCli.obj"
	-@erase "$(INTDIR)\MfcCli.pch"
	-@erase "$(INTDIR)\MfcCli.res"
	-@erase "$(INTDIR)\MfcCli.tlb"
	-@erase "$(INTDIR)\CliDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\MfcCli.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MfcCli.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MfcCli.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MfcCli.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/MfcCli.pdb" /machine:I386 /out:"$(OUTDIR)/MfcCli.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MfcCli.obj" \
	"$(INTDIR)\MfcCli.res" \
	"$(INTDIR)\CliDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MfcCli.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MfcCli - Win32 Debug"

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

ALL : "$(OUTDIR)\MfcCli.exe" "$(OUTDIR)\MfcCli.tlb" "$(OUTDIR)\MfcCli.bsc"

CLEAN : 
	-@erase "$(INTDIR)\MfcCli.obj"
	-@erase "$(INTDIR)\MfcCli.pch"
	-@erase "$(INTDIR)\MfcCli.res"
	-@erase "$(INTDIR)\MfcCli.sbr"
	-@erase "$(INTDIR)\MfcCli.tlb"
	-@erase "$(INTDIR)\CliDlg.obj"
	-@erase "$(INTDIR)\CliDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\MfcCli.bsc"
	-@erase "$(OUTDIR)\MfcCli.exe"
	-@erase "$(OUTDIR)\MfcCli.ilk"
	-@erase "$(OUTDIR)\MfcCli.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/MfcCli.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MfcCli.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MfcCli.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MfcCli.sbr" \
	"$(INTDIR)\CliDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\MfcCli.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/MfcCli.pdb" /debug /machine:I386 /out:"$(OUTDIR)/MfcCli.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MfcCli.obj" \
	"$(INTDIR)\MfcCli.res" \
	"$(INTDIR)\CliDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MfcCli.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MfcCli - Win32 Release"
# Name "MfcCli - Win32 Debug"

!IF  "$(CFG)" == "MfcCli - Win32 Release"

!ELSEIF  "$(CFG)" == "MfcCli - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MfcCli - Win32 Release"

!ELSEIF  "$(CFG)" == "MfcCli - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MfcCli.cpp
DEP_CPP_MFCCL=\
	"..\ComDemo.h"\
	".\MfcCli.h"\
	".\CliDlg.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MfcCli - Win32 Release"


"$(INTDIR)\MfcCli.obj" : $(SOURCE) $(DEP_CPP_MFCCL) "$(INTDIR)"\
 "$(INTDIR)\MfcCli.pch"


!ELSEIF  "$(CFG)" == "MfcCli - Win32 Debug"


"$(INTDIR)\MfcCli.obj" : $(SOURCE) $(DEP_CPP_MFCCL) "$(INTDIR)"\
 "$(INTDIR)\MfcCli.pch"

"$(INTDIR)\MfcCli.sbr" : $(SOURCE) $(DEP_CPP_MFCCL) "$(INTDIR)"\
 "$(INTDIR)\MfcCli.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CliDlg.cpp
DEP_CPP_MFCCLI=\
	"..\ComDemo.h"\
	"..\ComDemo_i.c"\
	".\MfcCli.h"\
	".\CliDlg.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MfcCli - Win32 Release"


"$(INTDIR)\CliDlg.obj" : $(SOURCE) $(DEP_CPP_MFCCLI) "$(INTDIR)"\
 "$(INTDIR)\MfcCli.pch"


!ELSEIF  "$(CFG)" == "MfcCli - Win32 Debug"


"$(INTDIR)\CliDlg.obj" : $(SOURCE) $(DEP_CPP_MFCCLI) "$(INTDIR)"\
 "$(INTDIR)\MfcCli.pch"

"$(INTDIR)\CliDlg.sbr" : $(SOURCE) $(DEP_CPP_MFCCLI) "$(INTDIR)"\
 "$(INTDIR)\MfcCli.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MfcCli.odl

!IF  "$(CFG)" == "MfcCli - Win32 Release"


"$(OUTDIR)\MfcCli.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/MfcCli.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "MfcCli - Win32 Debug"


"$(OUTDIR)\MfcCli.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/MfcCli.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\ComDemo.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MfcCli - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MfcCli.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MfcCli.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MfcCli - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/MfcCli.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MfcCli.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MfcCli.rc
DEP_RSC_MFCCLI_=\
	".\res\MfcCli.ico"\
	".\res\MfcCli.rc2"\
	

!IF  "$(CFG)" == "MfcCli - Win32 Release"


"$(INTDIR)\MfcCli.res" : $(SOURCE) $(DEP_RSC_MFCCLI_) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/MfcCli.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "MfcCli - Win32 Debug"


"$(INTDIR)\MfcCli.res" : $(SOURCE) $(DEP_RSC_MFCCLI_) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/MfcCli.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
