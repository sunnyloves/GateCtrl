
// GateCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GateCtrl.h"
#include "GateCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGateCtrlDlg dialog




CGateCtrlDlg::CGateCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGateCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGateCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMCMB, m_ComCMB);
	DDX_Control(pDX, IDC_OPENCOMBT, m_OpenCloseCOMBT);
	
}

BEGIN_MESSAGE_MAP(CGateCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENCOMBT, &CGateCtrlDlg::OnBnClickedOpencombt)
END_MESSAGE_MAP()


// CGateCtrlDlg message handlers

BOOL CGateCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	bIsComOpen = false;
	m_ComCMB.AddString(_T("COM1"));
	m_ComCMB.AddString(_T("COM2"));
	m_ComCMB.SetCurSel(0);



	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGateCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGateCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGateCtrlDlg::OnBnClickedOpencombt()
{
	// TODO: Add your control notification handler code here
//没打开
	if (!bIsComOpen)
	{
		CString sComStr;
		int nComCurSel = 0;
		nComCurSel = m_ComCMB.GetCurSel();
		m_Comm.Open(nComCurSel+1);
		if (m_Comm.IsOpen())
		{
			AfxMessageBox(_T("串口打开成功！"));
			m_ComCMB.EnableWindow(FALSE);
			m_OpenCloseCOMBT.SetWindowTextW(_T("关闭"));
			bIsComOpen = true;
		} 
		else
		{
			AfxMessageBox(_T("串口打开失败！"));
		}
	}
//串口已打开
	else
	{
		if (m_Comm.IsOpen())
		{
			m_Comm.Close();
			AfxMessageBox(_T("串口关闭！"));
			m_ComCMB.EnableWindow(TRUE);
			m_OpenCloseCOMBT.SetWindowTextW(_T("打开"));
			bIsComOpen = false;
		} 
		else
		{
		}
		
	}
	
	
	

}
