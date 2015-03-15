# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=numbers - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to numbers - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "numbers - Win32 Release" && "$(CFG)" !=\
 "numbers - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "numbers.mak" CFG="numbers - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "numbers - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "numbers - Win32 Debug" (based on "Win32 (x86) Console Application")
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
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "numbers - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\numbers.exe"

CLEAN : 
	-@erase "$(INTDIR)\numbers.obj"
	-@erase "$(OUTDIR)\numbers.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/numbers.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/numbers.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/numbers.pdb" /machine:I386 /out:"$(OUTDIR)/numbers.exe" 
LINK32_OBJS= \
	"$(INTDIR)\numbers.obj"

"$(OUTDIR)\numbers.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "numbers - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\numbers.exe"

CLEAN : 
	-@erase "$(INTDIR)\numbers.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\numbers.exe"
	-@erase "$(OUTDIR)\numbers.ilk"
	-@erase "$(OUTDIR)\numbers.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/numbers.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/numbers.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/numbers.pdb" /debug /machine:I386 /out:"$(OUTDIR)/numbers.exe" 
LINK32_OBJS= \
	"$(INTDIR)\numbers.obj"

"$(OUTDIR)\numbers.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "numbers - Win32 Release"
# Name "numbers - Win32 Debug"

!IF  "$(CFG)" == "numbers - Win32 Release"

!ELSEIF  "$(CFG)" == "numbers - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\numbers.cpp

"$(INTDIR)\numbers.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
