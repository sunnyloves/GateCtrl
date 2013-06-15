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

	m_PGCtrl.EnableHeaderCtrl(true,_T("����"),_T("ֵ"));
	m_PGCtrl.EnableDescriptionArea();
	m_PGCtrl.SetVSDotNetLook();
	m_PGCtrl.MarkModifiedProperties();

	m_PGCtrl.SetAlphabeticMode(false);

	m_PGCtrl.SetShowDragContext();

	pGroup0  = new CMFCPropertyGridProperty(_T("ͨѶ��"));	

	//����ѡ��
	CMFCPropertyGridProperty* pProp0 = new CMFCPropertyGridProperty(_T("����"), pMainFrame->ciConfigInfo.sCom,_T("ѡ��ͨѶ�õĴ���"));
	pProp0->AddOption(_T("COM1"));
	pProp0->AddOption(_T("COM2"));
	pProp0->AddOption(_T("COM3"));
	pProp0->AddOption(_T("COM4"));
	pProp0->AllowEdit(FALSE);
	pGroup0->AddSubItem(pProp0);
	m_PGCtrl.AddProperty(pGroup0);

	//ˮλվ
	/*
	-----բ��ˮλվ
	--------բ��ˮλվ����
	--------բ��ˮλ���
	-----բ��ˮλվ
	--------բ��ˮλվ����
	--------բ��ˮλ���

	*/
	pGroup1  = new CMFCPropertyGridProperty(_T("ˮλվ"));
	CMFCPropertyGridProperty* pProp10 = new CMFCPropertyGridProperty(_T("բ��ˮλվ"),0,TRUE);

	CMFCPropertyGridProperty* pProp101 = new CMFCPropertyGridProperty(_T("բ��ˮλվ����"),
		pMainFrame->ciConfigInfo.lsInnerStation.sStationName, _T("�趨բ��ˮλվ����"));
	pProp10->AddSubItem(pProp101);

	CMFCPropertyGridProperty* pProp102 = new CMFCPropertyGridProperty(_T("բ��ˮλվ���(cm)"),
		pMainFrame->ciConfigInfo.lsInnerStation.dbLevelZero, _T("�趨բ��ˮλվ���(cm)"));
	pProp10->AddSubItem(pProp102);

	CMFCPropertyGridProperty* pProp103 = new CMFCPropertyGridProperty(_T("բ��ˮλվվ��"), 
		pMainFrame->ciConfigInfo.lsInnerStation.sStationNO, _T("�趨բ��ˮλվͨѶվ��"));
	pProp103->AddOption(_T("1"));
	pProp103->AddOption(_T("2"));
	pProp103->AllowEdit(FALSE);
	pProp10->AddSubItem(pProp103);

	pProp10->Expand(TRUE);
	pProp10->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp10);


	CMFCPropertyGridProperty* pProp20 = new CMFCPropertyGridProperty(_T("բ��ˮλվ"),0,TRUE);

	CMFCPropertyGridProperty* pProp201 = new CMFCPropertyGridProperty(_T("բ��ˮλվ����"),
		pMainFrame->ciConfigInfo.lsOuterStation.sStationName, _T("�趨բ��ˮλվ����"));
	pProp20->AddSubItem(pProp201);

	CMFCPropertyGridProperty* pProp202 = new CMFCPropertyGridProperty(_T("բ��ˮλվ���(cm)"), 
		pMainFrame->ciConfigInfo.lsOuterStation.dbLevelZero, _T("�趨բ��ˮλվ���(cm)"));
	pProp20->AddSubItem(pProp202);

	CMFCPropertyGridProperty* pProp203 = new CMFCPropertyGridProperty(_T("բ��ˮλվվ��"), 
		pMainFrame->ciConfigInfo.lsOuterStation.sStationNO, _T("�趨բ��ˮλվͨѶվ��"));
	pProp203->AddOption(_T("1"));
	pProp203->AddOption(_T("2"));
	pProp203->AllowEdit(FALSE);
	pProp20->AddSubItem(pProp203);

	pProp20->Expand(TRUE);
	pProp20->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp20);

	m_PGCtrl.AddProperty(pGroup1);

	pGroup3 = new CMFCPropertyGridProperty(_T("բ�ſ���ˮλ��"));
	CMFCPropertyGridProperty* pProp3 = new CMFCPropertyGridProperty(_T("բ�ſ���ˮλ��(cm)"),
		pMainFrame->ciConfigInfo.dbLevelError, _T("բ�ſ���ˮλ��(cm)"));

	pGroup3->AddSubItem(pProp3);
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

	CString sParaName = pProp->GetName();  //���ı�Ĳ�����
	COleVariant t = pProp->GetValue(); //�ı�֮���ֵ
	if (sParaName == _T("����"))
	{
		pMainFrame->ciConfigInfo.sCom = t.bstrVal;
	} 
	else if (sParaName == _T("բ��ˮλվ����"))
	{
		pMainFrame->ciConfigInfo.lsInnerStation.sStationName = t.bstrVal;
	} 
	else if (sParaName == _T("բ��ˮλվ���(cm)"))
	{
		pMainFrame->ciConfigInfo.lsInnerStation.dbLevelZero = t.dblVal;
	}
	else if (sParaName == _T("բ��ˮλվվ��"))
	{
		pMainFrame->ciConfigInfo.lsInnerStation.sStationNO = t.bstrVal;
	} 
	else if (sParaName == _T("բ��ˮλվ����"))
	{
		pMainFrame->ciConfigInfo.lsOuterStation.sStationName = t.bstrVal;
	}
	else if (sParaName == _T("բ��ˮλվ���(cm)"))
	{
		pMainFrame->ciConfigInfo.lsOuterStation.dbLevelZero = t.dblVal;
	} 	
	else if (sParaName == _T("բ��ˮλվվ��"))
	{
		pMainFrame->ciConfigInfo.lsOuterStation.sStationName = t.bstrVal;
	} 
	else if (sParaName == _T("բ�ſ���ˮλ��(cm)"))
	{
		pMainFrame->ciConfigInfo.dbLevelError = t.dblVal;
	} 
	

	return 0;
}