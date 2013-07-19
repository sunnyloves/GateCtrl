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
	EnumSerialPorts(asi,TRUE);// ����Ϊ TRUE ʱö�ٵ�ǰ���Դ򿪵Ĵ��ڣ� ����ö�����д���
	m_nSerialPortNum = 0;
	m_nSerialPortNum = asi.GetSize();
	CString s;
	
	
	CMFCPropertyGridProperty* pProp0 = new CMFCPropertyGridProperty(_T("����"), pMainFrame->ciConfigInfo.sCom,_T("ѡ��ͨѶ�õĴ���"));

	for (int i=0; i<asi.GetSize(); i++)
	{
		s = _T("COM") + asi[i].strFriendlyName.Right(2);	//ƴ��COMx
		pProp0->AddOption(s.Left(4));

	}
	pProp0->AllowEdit(FALSE);
	pGroup0->AddSubItem(pProp0);
	m_PGCtrl.AddProperty(pGroup0);

	//��Ŀ��ˮλվ
	/*
	-----բ��ˮλվ	
	--------բ��ˮλ���
	--------բ��ˮλվ��
	-----բ��ˮλվ	
	--------բ��ˮλ���
	--------բ��ˮλվ��
	*/
	pGroup1  = new CMFCPropertyGridProperty(_T("��Ŀ��ˮλվ"));
	CMFCPropertyGridProperty* pProp11 = new CMFCPropertyGridProperty(_T("��Ŀ��բ��ˮλվ"),0,TRUE);


	CMFCPropertyGridProperty* pProp111 = new CMFCPropertyGridProperty(_T("��Ŀ��բ��ˮλվ���(cm)"),
		pMainFrame->ciConfigInfo.lsc_1.lsInnerStation.dbLevelZero, _T("�趨��Ŀ��բ��ˮλվ���(cm)"));
	pProp11->AddSubItem(pProp111);

	CMFCPropertyGridProperty* pProp112 = new CMFCPropertyGridProperty(_T("��Ŀ��բ��ˮλվվ��"), 
		pMainFrame->ciConfigInfo.lsc_1.lsInnerStation.sStationNO, _T("�趨��Ŀ��բ��ˮλվͨѶվ��"));
	pProp112->AddOption(_T("1"));
	pProp112->AddOption(_T("2"));
	pProp112->AllowEdit(FALSE);
	pProp11->AddSubItem(pProp112);

	pProp11->Expand(TRUE);
	pProp11->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp11);


	CMFCPropertyGridProperty* pProp12 = new CMFCPropertyGridProperty(_T("��Ŀ��բ��ˮλվ"),0,TRUE);

	CMFCPropertyGridProperty* pProp121 = new CMFCPropertyGridProperty(_T("��Ŀ��բ��ˮλվ���(cm)"), 
		pMainFrame->ciConfigInfo.lsc_1.lsOuterStation.dbLevelZero, _T("�趨��Ŀ��բ��ˮλվ���(cm)"));
	pProp12->AddSubItem(pProp121);

	CMFCPropertyGridProperty* pProp122 = new CMFCPropertyGridProperty(_T("��Ŀ��բ��ˮλվվ��"), 
		pMainFrame->ciConfigInfo.lsc_1.lsOuterStation.sStationNO, _T("�趨��Ŀ��բ��ˮλվͨѶվ��"));
	pProp122->AddOption(_T("1"));
	pProp122->AddOption(_T("2"));
	pProp122->AllowEdit(FALSE);
	pProp12->AddSubItem(pProp122);

	pProp12->Expand(TRUE);
	pProp12->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp12);
	m_PGCtrl.AddProperty(pGroup1);

	//�ϸ�ɽˮλվ
	/*
	-----բ��ˮλվ	
	--------բ��ˮλ���
	--------բ��ˮλվ��
	-----բ��ˮλվ	
	--------բ��ˮλ���
	--------բ��ˮλվ��
	*/
	pGroup2  = new CMFCPropertyGridProperty(_T("�ϸ�ɽˮλվ"));
	CMFCPropertyGridProperty* pProp21 = new CMFCPropertyGridProperty(_T("�ϸ�ɽբ��ˮλվ"),0,TRUE);


	CMFCPropertyGridProperty* pProp211 = new CMFCPropertyGridProperty(_T("�ϸ�ɽբ��ˮλվ���(cm)"),
		pMainFrame->ciConfigInfo.lsc_2.lsInnerStation.dbLevelZero, _T("�趨�ϸ�ɽբ��ˮλվ���(cm)"));
	pProp21->AddSubItem(pProp211);

	CMFCPropertyGridProperty* pProp212 = new CMFCPropertyGridProperty(_T("�ϸ�ɽբ��ˮλվվ��"), 
		pMainFrame->ciConfigInfo.lsc_2.lsInnerStation.sStationNO, _T("�趨�ϸ�ɽբ��ˮλվͨѶվ��"));
	pProp212->AddOption(_T("3"));
	pProp212->AddOption(_T("4"));
	pProp212->AllowEdit(FALSE);
	pProp21->AddSubItem(pProp212);

	pProp21->Expand(TRUE);
	pProp21->AllowEdit(FALSE);
	pGroup2->AddSubItem(pProp21);


	CMFCPropertyGridProperty* pProp22 = new CMFCPropertyGridProperty(_T("�ϸ�ɽբ��ˮλվ"),0,TRUE);

	CMFCPropertyGridProperty* pProp221 = new CMFCPropertyGridProperty(_T("�ϸ�ɽբ��ˮλվ���(cm)"), 
		pMainFrame->ciConfigInfo.lsc_2.lsOuterStation.dbLevelZero, _T("�趨�ϸ�ɽբ��ˮλվ���(cm)"));
	pProp22->AddSubItem(pProp221);

	CMFCPropertyGridProperty* pProp222 = new CMFCPropertyGridProperty(_T("�ϸ�ɽբ��ˮλվվ��"), 
		pMainFrame->ciConfigInfo.lsc_2.lsOuterStation.sStationNO, _T("�趨�ϸ�ɽբ��ˮλվͨѶվ��"));
	pProp222->AddOption(_T("3"));
	pProp222->AddOption(_T("4"));
	pProp222->AllowEdit(FALSE);
	pProp22->AddSubItem(pProp222);

	pProp22->Expand(TRUE);
	pProp22->AllowEdit(FALSE);

	pGroup2->AddSubItem(pProp22);

	m_PGCtrl.AddProperty(pGroup2);

	//

	pGroup3 = new CMFCPropertyGridProperty(_T("����ˮλ"));

	CMFCPropertyGridProperty* pProp31 = new CMFCPropertyGridProperty(_T("����ˮλ(cm)"),
		pMainFrame->ciConfigInfo.clCtrlLevel.dbDeadLevel, _T("�趨��վ����ˮλ(cm)"));
	pGroup3->AddSubItem(pProp31);

	CMFCPropertyGridProperty* pProp32 = new CMFCPropertyGridProperty(_T("բ�ſ���ˮλ��(cm)"),
		pMainFrame->ciConfigInfo.clCtrlLevel.dbLevelError, _T("�趨բ�ſ���ˮλ��(cm)"));

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

	CString sParaName = pProp->GetName();  //���ı�Ĳ�����
	COleVariant t = pProp->GetValue(); //�ı�֮���ֵ
	//
	if (sParaName == _T("����"))
	{
		pMainFrame->ciConfigInfo.sCom = t.bstrVal;
	} 
	//
	else if (sParaName == _T("��Ŀ��բ��ˮλվ���(cm)"))
	{
		pMainFrame->ciConfigInfo.lsc_1.lsInnerStation.dbLevelZero = t.dblVal;
	}
	else if (sParaName == _T("��Ŀ��բ��ˮλվվ��"))
	{
		pMainFrame->ciConfigInfo.lsc_1.lsInnerStation.sStationNO = t.bstrVal;
	} 

	else if (sParaName == _T("��Ŀ��բ��ˮλվ���(cm)"))
	{
		pMainFrame->ciConfigInfo.lsc_1.lsOuterStation.dbLevelZero = t.dblVal;
	} 	
	else if (sParaName == _T("��Ŀ��բ��ˮλվվ��"))
	{
		pMainFrame->ciConfigInfo.lsc_1.lsOuterStation.sStationNO = t.bstrVal;
	} 
	//
	else if (sParaName == _T("�ϸ�ɽբ��ˮλվ���(cm)"))
	{
		pMainFrame->ciConfigInfo.lsc_2.lsInnerStation.dbLevelZero = t.dblVal;
	}
	else if (sParaName == _T("�ϸ�ɽբ��ˮλվվ��"))
	{
		pMainFrame->ciConfigInfo.lsc_2.lsInnerStation.sStationNO = t.bstrVal;
	} 

	else if (sParaName == _T("�ϸ�ɽբ��ˮλվ���(cm)"))
	{
		pMainFrame->ciConfigInfo.lsc_2.lsOuterStation.dbLevelZero = t.dblVal;
	} 	
	else if (sParaName == _T("�ϸ�ɽբ��ˮλվվ��"))
	{
		pMainFrame->ciConfigInfo.lsc_2.lsOuterStation.sStationNO = t.bstrVal;
	} 


	//
	else if (sParaName == _T("����ˮλ(cm)"))
	{
		pMainFrame->ciConfigInfo.clCtrlLevel.dbDeadLevel = t.dblVal;
	} 
	else if (sParaName == _T("բ�ſ���ˮλ��(cm)"))
	{
		pMainFrame->ciConfigInfo.clCtrlLevel.dbLevelError = t.dblVal;
	} 
	

	return 0;
}