# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=Main1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Main1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Main1 - Win32 Release" && "$(CFG)" != "Main1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "main1.mak" CFG="Main1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Main1 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Main1 - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "Main1 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Main1 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "..\TempPR"
OUTDIR=.\Release
INTDIR=.\..\TempPR

ALL : "$(OUTDIR)\main1.exe"

CLEAN : 
	-@erase "$(INTDIR)\Main1.obj"
	-@erase "$(OUTDIR)\main1.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /Fp"..\TempPR/Multithd.pch" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/Multithd.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\..\TempPR/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/main1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 release\smalldll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=release\smalldll.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/main1.pdb" /machine:I386 /out:"$(OUTDIR)/main1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Main1.obj"

"$(OUTDIR)\main1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Main1 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "..\TempPD"
OUTDIR=.\Debug
INTDIR=.\..\TempPD

ALL : "$(OUTDIR)\main1.exe"

CLEAN : 
	-@erase "$(INTDIR)\Main1.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\main1.exe"
	-@erase "$(OUTDIR)\main1.ilk"
	-@erase "$(OUTDIR)\main1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /Fp"..\TempPD/Multithd.pch" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I ".." /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/Multithd.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\..\TempPD/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/main1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 debug\smalldll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=debug\smalldll.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/main1.pdb" /debug /machine:I386 /out:"$(OUTDIR)/main1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Main1.obj"

"$(OUTDIR)\main1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Main1 - Win32 Release"
# Name "Main1 - Win32 Debug"

!IF  "$(CFG)" == "Main1 - Win32 Release"

!ELSEIF  "$(CFG)" == "Main1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Main1.cpp

"$(INTDIR)\Main1.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
