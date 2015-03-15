# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=ReadWrit - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ReadWrit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ReadWrit - Win32 Release" && "$(CFG)" !=\
 "ReadWrit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ReadWrit.mak" CFG="ReadWrit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ReadWrit - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "ReadWrit - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "ReadWrit - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ReadWrit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "..\TempCR"
OUTDIR=.\Release
INTDIR=.\..\TempCR

ALL : "$(OUTDIR)\ReadWrit.exe"

CLEAN : 
	-@erase "$(INTDIR)\List.obj"
	-@erase "$(INTDIR)\ReadWrit.obj"
	-@erase "$(OUTDIR)\ReadWrit.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /Fp"..\TempCR/Multithd.pch" /YX"windows.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Multithd.pch" /YX"windows.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\..\TempCR/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ReadWrit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/ReadWrit.pdb" /machine:I386 /out:"$(OUTDIR)/ReadWrit.exe" 
LINK32_OBJS= \
	"$(INTDIR)\List.obj" \
	"$(INTDIR)\ReadWrit.obj"

"$(OUTDIR)\ReadWrit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ReadWrit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "..\TempCD"
OUTDIR=.\Debug
INTDIR=.\..\TempCD

ALL : "$(OUTDIR)\ReadWrit.exe"

CLEAN : 
	-@erase "$(INTDIR)\List.obj"
	-@erase "$(INTDIR)\ReadWrit.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ReadWrit.exe"
	-@erase "$(OUTDIR)\ReadWrit.ilk"
	-@erase "$(OUTDIR)\ReadWrit.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /Fp"..\TempCD/Multithd.pch" /YX"windows.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/Multithd.pch" /YX"windows.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\..\TempCD/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ReadWrit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/ReadWrit.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/ReadWrit.exe" 
LINK32_OBJS= \
	"$(INTDIR)\List.obj" \
	"$(INTDIR)\ReadWrit.obj"

"$(OUTDIR)\ReadWrit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "ReadWrit - Win32 Release"
# Name "ReadWrit - Win32 Debug"

!IF  "$(CFG)" == "ReadWrit - Win32 Release"

!ELSEIF  "$(CFG)" == "ReadWrit - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadWrit.c
DEP_CPP_READW=\
	".\ReadWrit.h"\
	

"$(INTDIR)\ReadWrit.obj" : $(SOURCE) $(DEP_CPP_READW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\List.c
DEP_CPP_LIST_=\
	".\ReadWrit.h"\
	

"$(INTDIR)\List.obj" : $(SOURCE) $(DEP_CPP_LIST_) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
