VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "Visual Basic COMDEMO Client"
   ClientHeight    =   3360
   ClientLeft      =   1140
   ClientTop       =   1512
   ClientWidth     =   4716
   Height          =   3684
   Left            =   1092
   LinkTopic       =   "Form1"
   ScaleHeight     =   3360
   ScaleWidth      =   4716
   Top             =   1236
   Width           =   4812
   Begin VB.CommandButton FastCounterCmd 
      Caption         =   "&Fast Counter"
      Height          =   375
      Left            =   480
      TabIndex        =   3
      Top             =   1080
      Width           =   1455
   End
   Begin VB.TextBox FastCounterValue 
      Enabled         =   0   'False
      Height          =   375
      Left            =   2280
      TabIndex        =   2
      Top             =   1080
      Width           =   1815
   End
   Begin VB.TextBox SlowCounterValue 
      Enabled         =   0   'False
      Height          =   375
      Left            =   2280
      TabIndex        =   1
      Top             =   360
      Width           =   1815
   End
   Begin VB.CommandButton SlowCounterCmd 
      Caption         =   "&Slow Counter"
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Top             =   360
      Width           =   1455
   End
   Begin VB.Frame Frame1 
      Caption         =   "Instructions"
      Height          =   1212
      Left            =   360
      TabIndex        =   4
      Top             =   1800
      Width           =   3732
      Begin VB.Label Label1 
         Caption         =   $"ComForm.frx":0000
         Height          =   852
         Left            =   240
         TabIndex        =   5
         Top             =   240
         Width           =   3132
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
    Dim AutoIncr As Object

Private Sub Command1_Click()
End Sub

Private Sub FastCounterCmd_Click()
    FastCounterValue.Text = AutoIncr.FastCounter
End Sub

Private Sub Form_Load()
    Set AutoIncr = CreateObject("ComDemo.AutoIncr.1")
End Sub


Private Sub SlowCounterCmd_Click()
    SlowCounterValue.Text = AutoIncr.SlowCounter
End Sub


