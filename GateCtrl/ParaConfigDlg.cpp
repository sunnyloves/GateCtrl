// ParaConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GateCtrl.h"
#include "ParaConfigDlg.h"
#include "MainFrm.h"

// CParaConfigDlg dialog

IMPLEMENT_DYNAMIC(CParaConfigDlg, CDialog)

CParaConfigDlg::CParaConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParaConfigDlg::IDD, pParent)
{

}

CParaConfigDlg::~CParaConfigDlg()
{
}

void CParaConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CParaConfigDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CParaConfigDlg::OnBnClickedOk)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)	
END_MESSAGE_MAP()


// CParaConfigDlg message handlers

BOOL CParaConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	
	InitPGCtrl();
	InitColor();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CParaConfigDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	CRect rc;
	GetClientRect(rc);
	CBrush   brush; 
	brush.CreateSolidBrush(RGB(239,246,248));  
	dc.FillRect(&rc,&brush); 



	// Do not call CDialog::OnPaint() for painting messages
}

void CParaConfigDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code herev	
	
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->SaveConfigToFile();

	OnOK();
}


void CParaConfigDlg::InitPGCtrl(void)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();	
	
	CRect rc;
	GetClientRect(rc);
	rc.bottom -= 60;
	rc.left += 10;
	rc.right -= 10;
	
	m_PGCtrl.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,IDC_CMFCPGCTRL);

	m_PGCtrl.EnableHeaderCtrl(true,_T("参数"),_T("值"));
	m_PGCtrl.EnableDescriptionArea();
	m_PGCtrl.SetVSDotNetLook();
	m_PGCtrl.MarkModifiedProperties();

	m_PGCtrl.SetAlphabeticMode(false);

	m_PGCtrl.SetShowDragContext();

	pGroup0  = new CMFCPropertyGridProperty(_T("通讯口"));	

	//串口选择
	EnumSerialPorts(asi,TRUE);// 参数为 TRUE 时枚举当前可以打开的串口， 否则枚举所有串口
	m_nSerialPortNum = 0;
	m_nSerialPortNum = asi.GetSize();
	CString s;
	
	
	CMFCPropertyGridProperty* pProp0 = new CMFCPropertyGridProperty(_T("串口"), pMainFrame->ciConfigInfo.sCom,_T("选择通讯用的串口"));

	for (int i=0; i<asi.GetSize(); i++)
	{
		s = _T("COM") + asi[i].strFriendlyName.Right(2);	//拼出COMx
		pProp0->AddOption(s.Left(4));

	}
	pProp0->AllowEdit(FALSE);
	pGroup0->AddSubItem(pProp0);
	m_PGCtrl.AddProperty(pGroup0);

	//龙目礁水位站
	/*
	-----闸内水位站	
	--------闸内水位零点
	--------闸内水位站号
	-----闸外水位站	
	--------闸外水位零点
	--------闸外水位站号
	*/
	pGroup1  = new CMFCPropertyGridProperty(_T("龙目礁水位站"));
	CMFCPropertyGridProperty* pProp11 = new CMFCPropertyGridProperty(_T("龙目礁闸内水位站"),0,TRUE);


	CMFCPropertyGridProperty* pProp111 = new CMFCPropertyGridProperty(_T("龙目礁闸内水位站零点(cm)"),
		pMainFrame->ciConfigInfo.lsc_1.lsInnerStation.dbLevelZero, _T("设定龙目礁闸内水位站零点(cm)"));
	pProp11->AddSubItem(pProp111);

	CMFCPropertyGridProperty* pProp112 = new CMFCPropertyGridProperty(_T("龙目礁闸内水位站站号"), 
		pMainFrame->ciConfigInfo.lsc_1.lsInnerStation.sStationNO, _T("设定龙目礁闸内水位站通讯站号"));
	pProp112->AddOption(_T("1"));
	pProp112->AddOption(_T("2"));
	pProp112->AllowEdit(FALSE);
	pProp11->AddSubItem(pProp112);

	pProp11->Expand(TRUE);
	pProp11->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp11);


	CMFCPropertyGridProperty* pProp12 = new CMFCPropertyGridProperty(_T("龙目礁闸外水位站"),0,TRUE);

	CMFCPropertyGridProperty* pProp121 = new CMFCPropertyGridProperty(_T("龙目礁闸外水位站零点(cm)"), 
		pMainFrame->ciConfigInfo.lsc_1.lsOuterStation.dbLevelZero, _T("设定龙目礁闸外水位站零点(cm)"));
	pProp12->AddSubItem(pProp121);

	CMFCPropertyGridProperty* pProp122 = new CMFCPropertyGridProperty(_T("龙目礁闸外水位站站号"), 
		pMainFrame->ciConfigInfo.lsc_1.lsOuterStation.sStationNO, _T("设定龙目礁闸外水位站通讯站号"));
	pProp122->AddOption(_T("1"));
	pProp122->AddOption(_T("2"));
	pProp122->AllowEdit(FALSE);
	pProp12->AddSubItem(pProp122);

	pProp12->Expand(TRUE);
	pProp12->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp12);
	m_PGCtrl.AddProperty(pGroup1);

	//上干山水位站
	/*
	-----闸内水位站	
	--------闸内水位零点
	--------闸内水位站号
	-----闸外水位站	
	--------闸外水位零点
	--------闸外水位站号
	*/
	pGroup2  = new CMFCPropertyGridProperty(_T("上干山水位站"));
	CMFCPropertyGridProperty* pProp21 = new CMFCPropertyGridProperty(_T("上干山闸内水位站"),0,TRUE);


	CMFCPropertyGridProperty* pProp211 = new CMFCPropertyGridProperty(_T("上干山闸内水位站零点(cm)"),
		pMainFrame->ciConfigInfo.lsc_2.lsInnerStation.dbLevelZero, _T("设定上干山闸内水位站零点(cm)"));
	pProp21->AddSubItem(pProp211);

	CMFCPropertyGridProperty* pProp212 = new CMFCPropertyGridProperty(_T("上干山闸内水位站站号"), 
		pMainFrame->ciConfigInfo.lsc_2.lsInnerStation.sStationNO, _T("设定上干山闸内水位站通讯站号"));
	pProp212->AddOption(_T("3"));
	pProp212->AddOption(_T("4"));
	pProp212->AllowEdit(FALSE);
	pProp21->AddSubItem(pProp212);

	pProp21->Expand(TRUE);
	pProp21->AllowEdit(FALSE);
	pGroup2->AddSubItem(pProp21);


	CMFCPropertyGridProperty* pProp22 = new CMFCPropertyGridProperty(_T("上干山闸外水位站"),0,TRUE);

	CMFCPropertyGridProperty* pProp221 = new CMFCPropertyGridProperty(_T("上干山闸外水位站零点(cm)"), 
		pMainFrame->ciConfigInfo.lsc_2.lsOuterStation.dbLevelZero, _T("设定上干山闸外水位站零点(cm)"));
	pProp22->AddSubItem(pProp221);

	CMFCPropertyGridProperty* pProp222 = new CMFCPropertyGridProperty(_T("上干山闸外水位站站号"), 
		pMainFrame->ciConfigInfo.lsc_2.lsOuterStation.sStationNO, _T("设定上干山闸外水位站通讯站号"));
	pProp222->AddOption(_T("3"));
	pProp222->AddOption(_T("4"));
	pProp222->AllowEdit(FALSE);
	pProp22->AddSubItem(pProp222);

	pProp22->Expand(TRUE);
	pProp22->AllowEdit(FALSE);

	pGroup2->AddSubItem(pProp22);

	m_PGCtrl.AddProperty(pGroup2);

	//

	pGroup3 = new CMFCPropertyGridProperty(_T("控制水位"));

	CMFCPropertyGridProperty* pProp31 = new CMFCPropertyGridProperty(_T("死区水位(cm)"),
		pMainFrame->ciConfigInfo.clCtrlLevel.dbDeadLevel, _T("设定电站死区水位(cm)"));
	pGroup3->AddSubItem(pProp31);

	CMFCPropertyGridProperty* pProp32 = new CMFCPropertyGridProperty(_T("闸门开启水位差(cm)"),
		pMainFrame->ciConfigInfo.clCtrlLevel.dbLevelError, _T("设定闸门开启水位差(cm)"));

	pGroup3->AddSubItem(pProp32);

	m_PGCtrl.AddProperty(pGroup3);
	

}

void CParaConfigDlg::InitColor(void)
{

	COLORREF clrBackground,clrText,clrGroupBackground,clrGroupText,
		clrDescriptionBackground,clrDescriptionText,clrLine;
	m_PGCtrl.GetCustomColors(clrBackground,clrText,clrGroupBackground,clrGroupText,
		clrDescriptionBackground,clrDescriptionText,clrLine);	
	m_PGCtrl.SetCustomColors(clrBackground,clrText,RGB(239,246,248),clrGroupText,
		RGB(239,246,248),clrDescriptionText,clrLine);
}


LRESULT CParaConfigDlg::OnPropertyChanged (WPARAM,LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam;
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CString sParaName = pProp->GetName();  //被改变的参数名
	COleVariant t = pProp->GetValue(); //改变之后的值
	//
	if (sParaName == _T("串口"))
	{
		pMainFrame->ciConfigInfo.sCom = t.bstrVal;
	} 
	//
	else if (sParaName == _T("龙目礁闸内水位站零点(cm)"))
	{
		pMainFrame->ciConfigInfo.lsc_1.lsInnerStation.dbLevelZero = t.dblVal;
	}
	else if (sParaName == _T("龙目礁闸内水位站站号"))
	{
		pMainFrame->ciConfigInfo.lsc_1.lsInnerStation.sStationNO = t.bstrVal;
	} 

	else if (sParaName == _T("龙目礁闸外水位站零点(cm)"))
	{
		pMainFrame->ciConfigInfo.lsc_1.lsOuterStation.dbLevelZero = t.dblVal;
	} 	
	else if (sParaName == _T("龙目礁闸外水位站站号"))
	{
		pMainFrame->ciConfigInfo.lsc_1.lsOuterStation.sStationNO = t.bstrVal;
	} 
	//
	else if (sParaName == _T("上干山闸内水位站零点(cm)"))
	{
		pMainFrame->ciConfigInfo.lsc_2.lsInnerStation.dbLevelZero = t.dblVal;
	}
	else if (sParaName == _T("上干山闸内水位站站号"))
	{
		pMainFrame->ciConfigInfo.lsc_2.lsInnerStation.sStationNO = t.bstrVal;
	} 

	else if (sParaName == _T("上干山闸外水位站零点(cm)"))
	{
		pMainFrame->ciConfigInfo.lsc_2.lsOuterStation.dbLevelZero = t.dblVal;
	} 	
	else if (sParaName == _T("上干山闸外水位站站号"))
	{
		pMainFrame->ciConfigInfo.lsc_2.lsOuterStation.sStationNO = t.bstrVal;
	} 


	//
	else if (sParaName == _T("死区水位(cm)"))
	{
		pMainFrame->ciConfigInfo.clCtrlLevel.dbDeadLevel = t.dblVal;
	} 
	else if (sParaName == _T("闸门开启水位差(cm)"))
	{
		pMainFrame->ciConfigInfo.clCtrlLevel.dbLevelError = t.dblVal;
	} 
	

	return 0;
}