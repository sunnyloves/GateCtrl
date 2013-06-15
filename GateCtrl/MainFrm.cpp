// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GateCtrl.h"
#include "GateCtrlDoc.h"
#include "GateCtrlView.h"
#include "MainFrm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()

	ON_COMMAND(ID_RIBBON_CONFIG_BT,OnConfigBT)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_CONFIG_BT, &CMainFrame::OnUpdateConfigButton)
	
	ON_COMMAND(IDS_RIBBON_START,OnStartCtrl)
	ON_UPDATE_COMMAND_UI(IDS_RIBBON_START, &CMainFrame::OnUpdateStartButton)

	ON_COMMAND(IDS_RIBBON_START,OnStopCtrl)
	ON_UPDATE_COMMAND_UI(IDS_RIBBON_START, &CMainFrame::OnUpdateStopButton)

	ON_WM_TIMER()
	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

//	BOOL bNameValid;

	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));

	m_wndRibbonBar.Create(this);
	InitializeRibbon();
	CheckConfigFile();



	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME;
	return TRUE;
}

void CMainFrame::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// Load panel images:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// Init main button:
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_CONFIG);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_RIBBON_CONFIG_BT, strTemp, 4, 4));
	/*	bNameValid = strTemp.LoadString(IDS_RIBBON_NEW);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, strTemp, 0, 0));
	bNameValid = strTemp.LoadString(IDS_RIBBON_OPEN);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, strTemp, 1, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, strTemp, 2, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVEAS);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, strTemp, 3, 3));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPrint = new CMFCRibbonButton(ID_FILE_PRINT, strTemp, 6, 6);
	pBtnPrint->SetKeys(_T("p"), _T("w"));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_LABEL);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonLabel(strTemp));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_QUICK);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_DIRECT, strTemp, 7, 7, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_PREVIEW);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, strTemp, 8, 8, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_SETUP);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, strTemp, 11, 11, TRUE));
	pMainPanel->Add(pBtnPrint);
	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CLOSE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, strTemp, 9, 9));

	bNameValid = strTemp.LoadString(IDS_RIBBON_RECENT_DOCS);
	ASSERT(bNameValid);
	pMainPanel->AddRecentFilesList(strTemp);
*/
	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));

	// Add "配置" category with "Clipboard" panel:
	bNameValid = strTemp.LoadString(IDS_RIBBON_CONFIG);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	// Create "参数" panel:
	strTemp.Format(_T("参数设置"));	
	CMFCRibbonPanel* pPanelConfig = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CONFIG);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnConfig = new CMFCRibbonButton(ID_RIBBON_CONFIG_BT, strTemp, 4, 4);
	pPanelConfig->Add(pBtnConfig);

	// Create and add a "闸门控制" panel:
	
	bNameValid = strTemp.LoadString(IDS_RIBBON_RUNSTATE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelRunState = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));
	
	strTemp.Format(_T("开始"));	
	CMFCRibbonButton* pBtnStart = new CMFCRibbonButton(IDS_RIBBON_START, strTemp, 7, 7);
	pPanelRunState->Add(pBtnStart);
	strTemp.Format(_T("停止"));	
	CMFCRibbonButton* pBtnStop = new CMFCRibbonButton(IDS_RIBBON_STOP, strTemp, 6, 6);
	pPanelRunState->Add(pBtnStop);

/*	bNameValid = strTemp.LoadString(IDS_RIBBON_STATUSBAR);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnStatusBar = new CMFCRibbonCheckBox(ID_VIEW_STATUS_BAR, strTemp);
	pPanelView->Add(pBtnStatusBar);
*/
	// Add quick access toolbar commands:
/*	CList<UINT, UINT> lstQATCmds;

	lstQATCmds.AddTail(ID_FILE_NEW);
	lstQATCmds.AddTail(ID_FILE_OPEN);
	lstQATCmds.AddTail(ID_FILE_SAVE);
	lstQATCmds.AddTail(ID_FILE_PRINT_DIRECT);

	m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);
*/
	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::OnConfigBT()
{
	if (IDOK == m_wndParaConfigDlg.DoModal())
	{
		CheckConfigFile();
		CGateCtrlView* pView = (CGateCtrlView*)GetActiveView();
		ASSERT(pView);
		pView->PostMessage(WM_CONFIGREADYMESSAGE,NULL,NULL);
	}
	
}

void CMainFrame::OnUpdateConfigButton(CCmdUI* pCmdUI)
{
	
}

BOOL CMainFrame::CheckConfigFile(void)
{
	CFileFind m_ConfigFileFinder;
	if (!m_ConfigFileFinder.FindFile(_T("config.xml")))
	{
		SetDefaultConfigFile();
		GetConfigFromFile();
	} 
	else
	{
		
		GetConfigFromFile();
	}
	return (TRUE);
	
}

void CMainFrame::SetDefaultConfigFile(void)
{
	//根
	m_ConfigXml.AddElem(_T("root"));
	//一级
	m_ConfigXml.AddChildElem(_T("通讯口"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("串口"),_T("com1"));
	m_ConfigXml.OutOfElem();
	//一级
	m_ConfigXml.AddChildElem(_T("水位站"));
	m_ConfigXml.IntoElem();
	//二级
	m_ConfigXml.AddChildElem(_T("闸内水位站"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("闸内水位站名称"),_T("闸内站 "));
	m_ConfigXml.AddChildElem(_T("闸内水位站零点(cm)"),_T("0.0"));
	m_ConfigXml.AddChildElem(_T("闸内水位站站号"),_T("1"));
	m_ConfigXml.OutOfElem();
	
	//二级
	m_ConfigXml.AddChildElem(_T("闸外水位站"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("闸外水位站名称"),_T("闸外站"));
	m_ConfigXml.AddChildElem(_T("闸外水位站零点(cm)"),_T("0.0"));
	m_ConfigXml.AddChildElem(_T("闸外水位站站号"),_T("2"));
	m_ConfigXml.OutOfElem();

	m_ConfigXml.OutOfElem();
	//一级
	m_ConfigXml.AddChildElem(_T("水位差"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("闸门开启水位差(cm)"),_T("0.0"));
	m_ConfigXml.OutOfElem();

	m_ConfigXml.Save(_T("config.xml"));
}

BOOL CMainFrame::GetConfigFromFile(void)
{
	BOOL b = FALSE;
	m_ConfigXml.Load(_T("config.xml"));
	m_ConfigXml.FindElem();
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindChildElem(_T("通讯口"));
	m_ConfigXml.IntoElem();	
	m_ConfigXml.FindElem(_T("串口"));
	ciConfigInfo.sCom = m_ConfigXml.GetData();
	m_ConfigXml.OutOfElem();

	//root结点
	m_ConfigXml.FindElem(_T("水位站"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("闸内水位站"));
	m_ConfigXml.IntoElem();
	b = m_ConfigXml.FindElem(_T("闸内水位站名称"));
	ciConfigInfo.lsInnerStation.sStationName = m_ConfigXml.GetData();
	m_ConfigXml.FindElem(_T("闸内水位站零点(cm)"));
	ciConfigInfo.lsInnerStation.dbLevelZero = _wtof(m_ConfigXml.GetData());
	m_ConfigXml.FindElem(_T("闸内水位站站号"));
	ciConfigInfo.lsInnerStation.sStationNO = m_ConfigXml.GetData();
	
	m_ConfigXml.ResetPos();	
	m_ConfigXml.FindElem();
	m_ConfigXml.IntoElem();

	m_ConfigXml.FindElem(_T("水位站"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("闸外水位站"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("闸外水位站名称"));	
	ciConfigInfo.lsOuterStation.sStationName = m_ConfigXml.GetData();
	m_ConfigXml.FindElem(_T("闸外水位站零点(cm)"));
	ciConfigInfo.lsOuterStation.dbLevelZero = _wtof(m_ConfigXml.GetData());
	m_ConfigXml.FindElem(_T("闸外水位站站号"));
	ciConfigInfo.lsOuterStation.sStationNO = m_ConfigXml.GetData();

	//root结点
	m_ConfigXml.ResetPos();	
	m_ConfigXml.FindElem();
	m_ConfigXml.IntoElem();

	m_ConfigXml.FindElem(_T("水位差"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("闸门开启水位差(cm)"));
	ciConfigInfo.dbLevelError = _wtof(m_ConfigXml.GetData());

	
	return 0;
}


void CMainFrame::SaveConfigToFile(void)
{
	CString sTemp;
	//清空已有配置
	m_ConfigXml.Load(_T("config.xml"));
	m_ConfigXml.FindElem();
	m_ConfigXml.RemoveElem();
	
	//根
	m_ConfigXml.AddElem(_T("root"));
	//一级
	m_ConfigXml.AddChildElem(_T("通讯口"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("串口"),ciConfigInfo.sCom);
	m_ConfigXml.OutOfElem();
	//一级
	m_ConfigXml.AddChildElem(_T("水位站"));
	m_ConfigXml.IntoElem();
	//二级
	m_ConfigXml.AddChildElem(_T("闸内水位站"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("闸内水位站名称"),ciConfigInfo.lsInnerStation.sStationName);
	sTemp.Format(_T("%.2f"),ciConfigInfo.lsInnerStation.dbLevelZero);
	m_ConfigXml.AddChildElem(_T("闸内水位站零点(cm)"),sTemp);
	m_ConfigXml.AddChildElem(_T("闸内水位站站号"),ciConfigInfo.lsInnerStation.sStationNO);
	m_ConfigXml.OutOfElem();

	//二级
	m_ConfigXml.AddChildElem(_T("闸外水位站"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("闸外水位站名称"),ciConfigInfo.lsOuterStation.sStationName);
	sTemp.Format(_T("%.2f"),ciConfigInfo.lsOuterStation.dbLevelZero);
	m_ConfigXml.AddChildElem(_T("闸外水位站零点(cm)"),sTemp);
	m_ConfigXml.AddChildElem(_T("闸外水位站站号"),ciConfigInfo.lsOuterStation.sStationNO);
	m_ConfigXml.OutOfElem();

	m_ConfigXml.OutOfElem();
	//一级
	m_ConfigXml.AddChildElem(_T("水位差"));
	m_ConfigXml.IntoElem();
	sTemp.Format(_T("%.2f"),ciConfigInfo.dbLevelError);
	m_ConfigXml.AddChildElem(_T("闸门开启水位差(cm)"),sTemp);
	m_ConfigXml.OutOfElem();

	m_ConfigXml.Save(_T("config.xml"));
}

void CMainFrame::OnStartCtrl()
{
	int i;
	i = _wtoi(ciConfigInfo.sCom.Right(1));
	m_Com.Open(i);
	if (m_Com.IsOpen())
	{
		AfxMessageBox(_T("打开成功!"));
		m_Com.SetWnd(AfxGetMainWnd()->m_hWnd); //设置消息处理窗口 很重要 一定要有

		//m_Com.Write(_T("已经打开了并且发送sdfef数据"));
	}


}

void CMainFrame::OnUpdateStartButton(CCmdUI* pCmdUI)
{

}


void CMainFrame::OnStopCtrl()
{

}


void CMainFrame::OnUpdateStopButton(CCmdUI* pCmdUI)
{

}
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	



	CFrameWndEx::OnTimer(nIDEvent);
}


LPARAM CMainFrame::OnComRecv(WPARAM wParam, LPARAM lParam)
{
	CString str;
	TCHAR buffer[100];
	m_Com.ReadString(buffer,20);
	str.Format(_T("%s"),buffer);

	AfxMessageBox(str);

	return(true);
}