; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCopySendDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CopySend.h"

ClassCount=3
Class1=CCopySendApp
Class2=CCopySendDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_COPYSEND_DIALOG

[CLS:CCopySendApp]
Type=0
HeaderFile=CopySend.h
ImplementationFile=CopySend.cpp
Filter=N

[CLS:CCopySendDlg]
Type=0
HeaderFile=CsDlg.h
ImplementationFile=CsDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CsDlg.h
ImplementationFile=CsDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_COPYSEND_DIALOG]
Type=1
Class=CCopySendDlg
ControlCount=6
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_SENDTEXT,edit,1350631552
Control4=IDOK,button,1342242817
Control5=IDC_CLEAR,button,1342242816
Control6=IDC_EXIT,button,1342242816

