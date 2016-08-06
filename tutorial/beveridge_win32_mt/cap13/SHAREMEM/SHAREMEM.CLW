; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShareMemDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ShareMem.h"

ClassCount=3
Class1=CShareMemApp
Class2=CShareMemDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SHAREMEM_DIALOG

[CLS:CShareMemApp]
Type=0
HeaderFile=ShareMem.h
ImplementationFile=ShareMem.cpp
Filter=N

[CLS:CShareMemDlg]
Type=0
HeaderFile=ShareDlg.h
ImplementationFile=ShareDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ShareDlg.h
ImplementationFile=ShareDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SHAREMEM_DIALOG]
Type=1
Class=CShareMemDlg
ControlCount=7
Control1=IDC_EDIT,edit,1350635524
Control2=IDC_READ,button,1342242816
Control3=IDC_WRITE,button,1342242816
Control4=IDOK,button,1342242817
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287

