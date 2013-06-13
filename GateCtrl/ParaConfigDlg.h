#pragma once


#include "CMakeUp/Markup.h"

// CParaConfigDlg dialog

class CParaConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CParaConfigDlg)

public:
	CParaConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CParaConfigDlg();

// Dialog Data
	enum { IDD = IDD_PARADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

protected:
	CMFCPropertyGridCtrl  m_PGCtrl;

	CMFCPropertyGridProperty* pGroup0;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnPropertyChanged(WPARAM,LPARAM);
	void InitPGCtrl(void);
	void InitColor(void);
};
