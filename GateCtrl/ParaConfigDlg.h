#pragma once


#include "CMakeUp/Markup.h"
#include "EnumSerial/EnumSerial.h"

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
	CMFCPropertyGridProperty* pGroup3;
	

	int m_nSerialPortNum;		// 串口计数
	CString  m_sSerialList[12];		// 字符串组
	CArray<SSerInfo,SSerInfo&> asi;	//枚举串口

public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnPropertyChanged(WPARAM,LPARAM);
	void InitPGCtrl(void);
	void InitColor(void);
};
