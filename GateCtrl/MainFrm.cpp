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
#include "DataShowPane.h"


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

	ON_COMMAND(IDS_RIBBON_STOP,OnStopCtrl)
	ON_UPDATE_COMMAND_UI(IDS_RIBBON_STOP, &CMainFrame::OnUpdateStopButton)

	ON_COMMAND(IDS_RIBBON_NEXTCHART_BT,OnNextChartClick)
	ON_UPDATE_COMMAND_UI(IDS_RIBBON_NEXTCHART_BT, &CMainFrame::OnUpdateNextChartButton)
	

	ON_WM_TIMER()
	
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bConfigBTState = TRUE;
	m_bStartBTState = FALSE;
	m_bStopBTState = FALSE;
	m_bNextChartBTState = FALSE;

	m_ldLevelData.dbInnerLevel_1 = 0.0;
	m_ldLevelData.dbOuterLevel_1 = 0.0;
	m_ldLevelData.dbInnerLevel_2 = 0.0;
	m_ldLevelData.dbOuterLevel_2 = 0.0;
	m_dbLevelError_1 = 0.0;
	m_dbLevelError_2 = 0.0;
	m_bNextLevelCombo = FALSE;


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

	m_wndDataShowPane.Create(_T("ˮλ��Ϣ"),this,CSize(100,100),TRUE,ID_PANE_DATA);
	m_wndDataShowPane.ShowPane(false,false,true);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	m_wndDataShowPane.EnableDocking(CBRS_ALIGN_BOTTOM);
	


	DockPane(&m_wndDataShowPane);

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

	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));

	// Add "����" category with "Clipboard" panel:
	bNameValid = strTemp.LoadString(IDS_RIBBON_CONFIG);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	// Create "����" panel:
	strTemp.Format(_T("��������"));	
	CMFCRibbonPanel* pPanelConfig = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CONFIG);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnConfig = new CMFCRibbonButton(ID_RIBBON_CONFIG_BT, strTemp, 4, 4);
	pPanelConfig->Add(pBtnConfig);

	// Create and add a "բ�ſ���" panel:
	
	bNameValid = strTemp.LoadString(IDS_RIBBON_RUNSTATE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelRunState = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));
	
	strTemp.Format(_T("��ʼ"));	
	CMFCRibbonButton* pBtnStart = new CMFCRibbonButton(IDS_RIBBON_START, strTemp, 7, 7);
	pPanelRunState->Add(pBtnStart);
	strTemp.Format(_T("ֹͣ"));	
	CMFCRibbonButton* pBtnStop = new CMFCRibbonButton(IDS_RIBBON_STOP, strTemp, 6, 6);
	pPanelRunState->Add(pBtnStop);


	// Add "��ͼ" category :
	bNameValid = strTemp.LoadString(IDS_RIBBON_VIEW);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryView = m_wndRibbonBar.AddCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_CHARTVIEW);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelChartViewPanel = pCategoryView->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));
	
	// ����һ���༭��ؼ� 
	CMFCRibbonEdit * pEdit = new CMFCRibbonEdit(IDS_RIBBON_NEXTCHART_EDIT,70);
	// ����Ĭ���ı� 
	pEdit->SetEditText(_T( "������" ));
	pEdit->OnEnable(FALSE);
	pPanelChartViewPanel->Add(pEdit);

	strTemp.Format(_T("��һ��"));	
	CMFCRibbonButton* pBtnNextChartBT = new CMFCRibbonButton(IDS_RIBBON_NEXTCHART_BT, strTemp, 5, 5);
	pPanelChartViewPanel->Add(pBtnNextChartBT);
	


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
		m_bConfigBTState = FALSE;
		m_bStartBTState = TRUE;
		
	}
	
}

void CMainFrame::OnUpdateConfigButton(CCmdUI* pCmdUI)
{	
	pCmdUI->Enable(m_bConfigBTState);
	
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
	//��
	m_ConfigXml.AddElem(_T("root"));
	//һ��
	m_ConfigXml.AddChildElem(_T("ͨѶ��"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("����"),_T("com1"));
	m_ConfigXml.OutOfElem();

	//һ��
	m_ConfigXml.AddChildElem(_T("��Ŀ��ˮλվ"));
	m_ConfigXml.IntoElem();
	//����
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվ���(cm)"),_T("0.0"));
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվվ��"),_T("1"));
	m_ConfigXml.OutOfElem();
	
	//����
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվ���(cm)"),_T("0.0"));
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվվ��"),_T("2"));
	m_ConfigXml.OutOfElem();

	m_ConfigXml.OutOfElem();
	//
	//һ��
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽˮλվ"));
	m_ConfigXml.IntoElem();
	//����
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվ���(cm)"),_T("0.0"));
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվվ��"),_T("3"));
	m_ConfigXml.OutOfElem();

	//����
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվ���(cm)"),_T("0.0"));
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվվ��"),_T("4"));
	m_ConfigXml.OutOfElem();

	m_ConfigXml.OutOfElem();




	//һ��
	m_ConfigXml.AddChildElem(_T("����ˮλ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("����ˮλ(cm)"),_T("0.0"));
	m_ConfigXml.AddChildElem(_T("բ�ſ���ˮλ��(cm)"),_T("0.0"));
	m_ConfigXml.OutOfElem();

	m_ConfigXml.Save(_T("config.xml"));
}

BOOL CMainFrame::GetConfigFromFile(void)
{
	BOOL b = FALSE;
	m_ConfigXml.Load(_T("config.xml"));
	m_ConfigXml.FindElem();
	m_ConfigXml.IntoElem();

	m_ConfigXml.FindElem(_T("ͨѶ��"));
	m_ConfigXml.IntoElem();	
	m_ConfigXml.FindElem(_T("����"));
	ciConfigInfo.sCom = m_ConfigXml.GetData();

	m_ConfigXml.ResetPos();	
	//root���
	m_ConfigXml.FindElem();
	m_ConfigXml.IntoElem();

	
	m_ConfigXml.FindElem(_T("��Ŀ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("��Ŀ��բ��ˮλվ"));
	m_ConfigXml.IntoElem();

	m_ConfigXml.FindElem(_T("��Ŀ��բ��ˮλվ���(cm)"));
	ciConfigInfo.lsc_1.lsInnerStation.dbLevelZero = _wtof(m_ConfigXml.GetData());
	m_ConfigXml.FindElem(_T("��Ŀ��բ��ˮλվվ��"));
	ciConfigInfo.lsc_1.lsInnerStation.sStationNO = m_ConfigXml.GetData();
	
	m_ConfigXml.ResetPos();	
	m_ConfigXml.FindElem();
	m_ConfigXml.IntoElem();

	b = m_ConfigXml.FindElem(_T("��Ŀ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("��Ŀ��բ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("��Ŀ��բ��ˮλվ���(cm)"));
	ciConfigInfo.lsc_1.lsOuterStation.dbLevelZero = _wtof(m_ConfigXml.GetData());
	m_ConfigXml.FindElem(_T("��Ŀ��բ��ˮλվվ��"));
	ciConfigInfo.lsc_1.lsOuterStation.sStationNO = m_ConfigXml.GetData();

	//root���
	m_ConfigXml.ResetPos();	
	m_ConfigXml.FindElem();
	m_ConfigXml.IntoElem();

	//
	m_ConfigXml.FindElem(_T("�ϸ�ɽˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("�ϸ�ɽբ��ˮλվ"));
	m_ConfigXml.IntoElem();

	m_ConfigXml.FindElem(_T("�ϸ�ɽբ��ˮλվ���(cm)"));
	ciConfigInfo.lsc_2.lsInnerStation.dbLevelZero = _wtof(m_ConfigXml.GetData());
	m_ConfigXml.FindElem(_T("�ϸ�ɽբ��ˮλվվ��"));
	ciConfigInfo.lsc_2.lsInnerStation.sStationNO = m_ConfigXml.GetData();

	m_ConfigXml.ResetPos();	
	m_ConfigXml.FindElem();
	m_ConfigXml.IntoElem();

	m_ConfigXml.FindElem(_T("�ϸ�ɽˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("�ϸ�ɽբ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("�ϸ�ɽբ��ˮλվ���(cm)"));
	ciConfigInfo.lsc_2.lsOuterStation.dbLevelZero = _wtof(m_ConfigXml.GetData());
	m_ConfigXml.FindElem(_T("�ϸ�ɽբ��ˮλվվ��"));
	ciConfigInfo.lsc_2.lsOuterStation.sStationNO = m_ConfigXml.GetData();




	//root���
	m_ConfigXml.ResetPos();	
	m_ConfigXml.FindElem();
	m_ConfigXml.IntoElem();

	m_ConfigXml.FindElem(_T("����ˮλ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.FindElem(_T("����ˮλ(cm)"));
	ciConfigInfo.clCtrlLevel.dbDeadLevel = _wtof(m_ConfigXml.GetData());
	m_ConfigXml.FindElem(_T("բ�ſ���ˮλ��(cm)"));
	ciConfigInfo.clCtrlLevel.dbLevelError = _wtof(m_ConfigXml.GetData());

	
	return 0;
}


void CMainFrame::SaveConfigToFile(void)
{
	CString sTemp;
	//�����������
	m_ConfigXml.Load(_T("config.xml"));
	m_ConfigXml.FindElem();
	m_ConfigXml.RemoveElem();
	
	//��
	m_ConfigXml.AddElem(_T("root"));
	//һ��
	m_ConfigXml.AddChildElem(_T("ͨѶ��"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("����"),ciConfigInfo.sCom);
	m_ConfigXml.OutOfElem();
	//һ��
	m_ConfigXml.AddChildElem(_T("��Ŀ��ˮλվ"));
	m_ConfigXml.IntoElem();
	//����
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվ"));
	m_ConfigXml.IntoElem();
	sTemp.Format(_T("%.2f"),ciConfigInfo.lsc_1.lsInnerStation.dbLevelZero);
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվ���(cm)"),sTemp);
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվվ��"),ciConfigInfo.lsc_1.lsInnerStation.sStationNO);
	m_ConfigXml.OutOfElem();

	//����
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվ"));
	m_ConfigXml.IntoElem();

	sTemp.Format(_T("%.2f"),ciConfigInfo.lsc_1.lsOuterStation.dbLevelZero);
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվ���(cm)"),sTemp);
	m_ConfigXml.AddChildElem(_T("��Ŀ��բ��ˮλվվ��"),ciConfigInfo.lsc_1.lsOuterStation.sStationNO);
	m_ConfigXml.OutOfElem();

	m_ConfigXml.OutOfElem();

	//
	//һ��
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽˮλվ"));
	m_ConfigXml.IntoElem();
	//����
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվ"));
	m_ConfigXml.IntoElem();
	sTemp.Format(_T("%.2f"),ciConfigInfo.lsc_2.lsInnerStation.dbLevelZero);
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվ���(cm)"),sTemp);
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվվ��"),ciConfigInfo.lsc_2.lsInnerStation.sStationNO);
	m_ConfigXml.OutOfElem();

	//����
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվ"));
	m_ConfigXml.IntoElem();

	sTemp.Format(_T("%.2f"),ciConfigInfo.lsc_2.lsOuterStation.dbLevelZero);
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվ���(cm)"),sTemp);
	m_ConfigXml.AddChildElem(_T("�ϸ�ɽբ��ˮλվվ��"),ciConfigInfo.lsc_2.lsOuterStation.sStationNO);
	m_ConfigXml.OutOfElem();

	m_ConfigXml.OutOfElem();



	//һ��
	m_ConfigXml.AddChildElem(_T("����ˮλ"));
	m_ConfigXml.IntoElem();
	sTemp.Format(_T("%.2f"),ciConfigInfo.clCtrlLevel.dbDeadLevel);
	m_ConfigXml.AddChildElem(_T("����ˮλ(cm)"),sTemp);
	sTemp.Format(_T("%.2f"),ciConfigInfo.clCtrlLevel.dbLevelError);
	m_ConfigXml.AddChildElem(_T("բ�ſ���ˮλ��(cm)"),sTemp);
	m_ConfigXml.OutOfElem();

	m_ConfigXml.Save(_T("config.xml"));
}

void CMainFrame::OnStartCtrl()
{
	m_wndDataShowPane.ShowPane(true,false,true);
	
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString sFileName;
	//����ʱ��Ϊ�ļ���
	sFileName.Format(_T("Data%04d%02d%02d%02d%02d%02d.txt"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	
	m_LevelFile.Open(sFileName,CFile::modeCreate | CFile::modeWrite);


	//m_LevelDataArray.SetSize(1000,500);	
	
	//����
	int i;
	i = _wtoi(ciConfigInfo.sCom.Right(1));
	m_Com.Open(i);
	if (m_Com.IsOpen())
	{
		//AfxMessageBox(_T("�򿪳ɹ�!"));
		m_Com.SetWnd(m_hWnd); //������Ϣ������ ����Ҫ һ��Ҫ��
		m_bConfigBTState = FALSE;
		m_bStartBTState = FALSE;
		m_bStopBTState = TRUE;
		m_bNextChartBTState = TRUE;
		
		SetTimer(1,1000,NULL);
		
	}
	//725��
	//DRV_DeviceOpen(dwDeviceNum,(LONG far*)&DriverHandle)����˵����dwDeviceNum
	//���豸�ţ��ú������л��ṩ��Device Manger�п��Բ鿴�����豸ǰ���000 001

	m_lrErrCode = DRV_DeviceOpen(0,(LONG far *)&m_lDriverHandle);
	if (m_lrErrCode != SUCCESS)
	{
		AfxMessageBox(_T("Device open error !"));

		return;
	}






}

void CMainFrame::OnUpdateStartButton(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bStartBTState);
}


void CMainFrame::OnStopCtrl()
{	
	KillTimer(1);

	m_Com.Close();

	DRV_DeviceClose((LONG far *)&m_lDriverHandle);
	WriteLevelToFile();
	

	m_bConfigBTState = TRUE;
	m_bStartBTState = FALSE;
	m_bStopBTState = FALSE;
	m_bNextChartBTState = FALSE;





}


void CMainFrame::OnUpdateStopButton(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bStopBTState);
}

void CMainFrame::OnNextChartClick()
{
	
	CGateCtrlView* pView = (CGateCtrlView*)GetActiveView();
	ASSERT_VALID(pView);
	CMFCRibbonBar *pRibbonBar = GetRibbonBar();
	ASSERT_VALID(pRibbonBar);
	//��ȡRibbonComboBox�ؼ�ָ��
	CMFCRibbonEdit * pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbonBar->FindByID(IDS_RIBBON_NEXTCHART_EDIT));
	pEdit->OnEnable(TRUE);
	
	if (m_bNextLevelCombo)
	{
		
		pEdit->SetEditText(_T( "��Ŀ��" ));
		
		pView->m_pLevel1inLineSeries->SetVisible(true);
		pView->m_pLevel1outLineSeries->SetVisible(true);
		pView->m_pLevel2inLineSeries->SetVisible(false);
		pView->m_pLevel2outLineSeries->SetVisible(false);
		m_bNextLevelCombo = FALSE;
	}
	else
	{
		pEdit->SetEditText(_T( "�ϸ�ɽ" ));
		pView->m_pLevel1inLineSeries->SetVisible(false);
		pView->m_pLevel1outLineSeries->SetVisible(false);
		pView->m_pLevel2inLineSeries->SetVisible(true);
		pView->m_pLevel2outLineSeries->SetVisible(true);
		m_bNextLevelCombo = TRUE;
	}
	
}


void CMainFrame::OnUpdateNextChartButton(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bNextChartBTState);
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	
	if (nIDEvent == 1)
	{
		
		//һ�����ͽ��չ���125ms
		m_Com.Write("A01");	
		m_Com.ReadString(m_ComTemp,10);
		m_ldLevelData.dbInnerLevel_1 = atof(m_ComTemp)/100000.0;
		m_ldLevelData.dbInnerLevel_1 += ciConfigInfo.lsc_1.lsInnerStation.dbLevelZero;

		m_Com.Write("A02");	
		m_Com.ReadString(m_ComTemp,10);
		m_ldLevelData.dbOuterLevel_1 = atof(m_ComTemp)/100000.0;
		m_ldLevelData.dbOuterLevel_1 += ciConfigInfo.lsc_1.lsOuterStation.dbLevelZero;

		m_dbLevelError_1 = m_ldLevelData.dbInnerLevel_1 - m_ldLevelData.dbOuterLevel_1;
		
		//
		m_Com.Write("A03");
		m_Com.ReadString(m_ComTemp,10);
		m_ldLevelData.dbInnerLevel_2 = atof(m_ComTemp)/100000.0;
		m_ldLevelData.dbInnerLevel_2 += ciConfigInfo.lsc_2.lsInnerStation.dbLevelZero;

		m_Com.Write("A04");
		m_Com.ReadString(m_ComTemp,10);
		m_ldLevelData.dbOuterLevel_2 = atof(m_ComTemp)/100000.0;
		m_ldLevelData.dbOuterLevel_2 += ciConfigInfo.lsc_2.lsOuterStation.dbLevelZero;

		m_dbLevelError_2 = m_ldLevelData.dbInnerLevel_2 - m_ldLevelData.dbOuterLevel_2;

		CGateCtrlView* pView = (CGateCtrlView*)GetActiveView();
		ASSERT(pView);
		pView->PostMessage(WM_UPDATELEVEL,NULL,NULL);

		m_wndDataShowPane.PostMessage(WM_UPDATELEVEL,NULL,NULL);


	}



	CFrameWndEx::OnTimer(nIDEvent);
}








void CMainFrame::WriteLevelToFile(void)
{
	//�ļ���һ��
	//\tab  LMJin\tab LMJout\tab SGSin\tab SGSout
	//1\tab 0.x\tab  0.x 
	//2\tab
	m_LevelFile.WriteString(_T("\tLMJin\tLMJout\tSGSin\tSGSout\n"));

	m_LevelDataArray.FreeExtra();
	int n = m_LevelDataArray.GetSize();

	double dbTemp1,dbTemp2,dbTemp3,dbTemp4;
	CString sTemp;
	for (int i=0;i<n;i++)
	{
		dbTemp1 = m_LevelDataArray.GetAt(i).dbInnerLevel_1;
		dbTemp2 = m_LevelDataArray.GetAt(i).dbOuterLevel_1;
		dbTemp3 = m_LevelDataArray.GetAt(i).dbInnerLevel_2;
		dbTemp4 = m_LevelDataArray.GetAt(i).dbOuterLevel_2;
		sTemp.Format(_T("%d\t%.2f\t%.2f\t%.2f\t%.2f\n"),i,dbTemp1,dbTemp2,dbTemp3,dbTemp4);
		m_LevelFile.WriteString(sTemp);
	}

	m_LevelFile.Close();




}