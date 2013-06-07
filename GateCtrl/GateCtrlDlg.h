
// GateCtrlDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CnCom/CnComm.h"


// CGateCtrlDlg dialog
class CGateCtrlDlg : public CDialogEx
{
// Construction
public:
	CGateCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GATECTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedOpencombt();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComCMB;
	CButton m_OpenCloseCOMBT;	
	CnComm m_Comm;
	bool bIsComOpen;



};
