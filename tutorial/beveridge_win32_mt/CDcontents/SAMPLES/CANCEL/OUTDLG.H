/*	@doc
 *
 * @module OutDlg.H - Output Design message modeless dialog box	|
 *
 * The class CProgressDlg tells the user that the design is being output.
 *
 * Author:  Dragana Ilic
 *
 * Copyright (c) 1995 Turning Point Software.  All Rights Reserved.
 *
 * $Header:: /Betsy/Dialogs/OutputDs/OutDlg.H 10    3/12/96 12:34p Shelah    $
 *
 */

#if !defined(_OUTDLG_H_)
#define _OUTDLG_H_

#ifndef __AFXCMN_H__
#include <afxcmn.h>
#endif	// __AFXCMN_H__

//////////////////////////////////////////////////////////////////////////
// INCLUDE FILES

//////////////////////////////////////////////////////////////////////////
// SYMBOLIC CONSTANTS

#define WM_USER_PREPARE_TO_CLOSE (WM_USER + 0x1001)

//////////////////////////////////////////////////////////////////////////
// FORWARD REFERENCES

//////////////////////////////////////////////////////////////////////////
// CLASS DECLARATIONS


/**********************************************************
 *
 *     CProgressDlg
 *
 * The progress dialog is supposed to show an operation
 * in progress in another thread, with a cancel button
 * that sets the m_fIsCancelled member if pushed.
 *
 */ 
class CProgressDlg : public CDialog
{
public:
// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_OUTPUT_MSGDLG };
	//}}AFX_DATA

// Construction, destruction
	CProgressDlg(CWnd* pParent = NULL);   // standard constructor

	~CProgressDlg(); 

	//member set the dialog static message, call this function after Create()
	void SetMessage(LPCTSTR strMsg);

	// Sets the position of the progress bar to the specifc value, and updates %.
	void UpdateProgressPercent( DWORD ulCurrent, DWORD ulMax );
	// Cheks if CANCEL button is pressed
	BOOL IsCancelled() { return m_fIsCancelled; }

	// Initializes variables
	void Initialize();					

	// Create and initialize the dialog and set its text and title
	BOOL	StartDialog();

	// The equivalent of DestroyWindow, but handles multiple threads
	void	CloseDialog();

// Member data

	volatile BOOL m_fIsCancelled;	// Cancel flag

	// Keep track of the thread currently in control of this dialog.
	COutputCancelDlgThread* m_pThread;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

//@access Protected Member Functions 
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT OnPrepareToClose(WPARAM, LPARAM);

private:

friend COutputCancelDlgThread;

	// Part 2 of StartDialog after thread starts
	BOOL Go();

};

#endif // _OUTDLG_H_
