; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCancelView
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Cancel.h"
LastPage=0

ClassCount=7
Class1=CCancelApp
Class2=CCancelDoc
Class3=CCancelView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDR_CANCELTYPE
Resource3=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CChildFrame
Class7=COutputCancelDlgThread
Resource4=IDD_OUTPUT_MSGDLG

[CLS:CCancelApp]
Type=0
HeaderFile=Cancel.h
ImplementationFile=Cancel.cpp
Filter=N

[CLS:CCancelDoc]
Type=0
HeaderFile=CancelDoc.h
ImplementationFile=CancelDoc.cpp
Filter=N

[CLS:CCancelView]
Type=0
HeaderFile=CancelView.h
ImplementationFile=CancelView.cpp
Filter=C
LastObject=ID_VIEW_NOPARENT
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=Cancel.cpp
ImplementationFile=Cancel.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDOK,button,1342373889
Control3=IDC_STATIC,static,1342308353
Control4=IDC_STATIC,static,1342308353
Control5=IDC_STATIC,static,1342308353

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_CANCELTYPE]
Type=1
Class=CCancelView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_VIEW_TIGHT_LOOP
Command15=ID_LAUNCH
Command16=ID_BOOM
Command17=ID_LAUNCH_WIN32
Command18=ID_VIEW_NOPARENT
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_APP_ABOUT
CommandCount=23

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:COutputCancelDlgThread]
Type=0
HeaderFile=OutpThrd.h
ImplementationFile=OutpThrd..cpp
BaseClass=CWinThread
Filter=N
LastObject=COutputCancelDlgThread

[DLG:IDD_OUTPUT_MSGDLG]
Type=1
Class=?
ControlCount=3
Control1=IDC_PROMPT_STATIC,static,1342177281
Control2=IDCANCEL,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242817

