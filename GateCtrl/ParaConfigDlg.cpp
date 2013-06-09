// ParaConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GateCtrl.h"
#include "ParaConfigDlg.h"


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
END_MESSAGE_MAP()


// CParaConfigDlg message handlers

BOOL CParaConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
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
	pGroup1 = new CMFCPropertyGridProperty(_T("ˮλվ"));
	pGroup2 = new CMFCPropertyGridProperty(_T("բ�ſ���ˮλ��"));
	//pGroup2 = new CMFCPropertyGridProperty(_T(""));
	//pGroup3 = new CMFCPropertyGridProperty(_T(""));
	
	//����ѡ��
	CMFCPropertyGridProperty* pProp0 = new CMFCPropertyGridProperty(_T("����"), _T("COM1"),_T("ѡ��ͨѶ�õĴ���"));
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
	CMFCPropertyGridProperty* pProp10 = new CMFCPropertyGridProperty(_T("բ��ˮλվ"),0,TRUE);
	
	CMFCPropertyGridProperty* pProp101 = new CMFCPropertyGridProperty(_T("բ��ˮλվ����"), _T(""), _T("�趨բ��ˮλվ����"));
	pProp10->AddSubItem(pProp101);

	CMFCPropertyGridProperty* pProp102 = new CMFCPropertyGridProperty(_T("բ��ˮλվ���(cm)"), (_variant_t)0.0, _T("�趨բ��ˮλվ���(cm)"));
	pProp10->AddSubItem(pProp102);

	CMFCPropertyGridProperty* pProp103 = new CMFCPropertyGridProperty(_T("բ��ˮλվվ��"), _T("1"), _T("�趨բ��ˮλվͨѶվ��"));
	pProp103->AddOption(_T("1"));
	pProp103->AddOption(_T("2"));
	pProp103->AllowEdit(FALSE);
	pProp10->AddSubItem(pProp103);

	pProp10->Expand(TRUE);
	pProp10->AllowEdit(FALSE);
	pGroup1->AddSubItem(pProp10);
	

	CMFCPropertyGridProperty* pProp20 = new CMFCPropertyGridProperty(_T("բ��ˮλվ"),0,TRUE);

	CMFCPropertyGridProperty* pProp201 = new CMFCPropertyGridProperty(_T("բ��ˮλվ����"), _T(""), _T("�趨բ��ˮλվ����"));
	pProp20->AddSubItem(pProp201);

	CMFCPropertyGridProperty* pProp202 = new CMFCPropertyGridProperty(_T("բ��ˮλվ���(cm)"), (_variant_t)0.0, _T("�趨բ��ˮλվ���(cm)"));
	pProp20->AddSubItem(pProp202);

	CMFCPropertyGridProperty* pProp203 = new CMFCPropertyGridProperty(_T("բ��ˮλվվ��"), _T("1"), _T("�趨բ��ˮλվͨѶվ��"));
	pProp203->AddOption(_T("1"));
	pProp203->AddOption(_T("2"));
	pProp203->AllowEdit(FALSE);
	pProp20->AddSubItem(pProp203);

	pProp20->Expand(TRUE);
	pProp20->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp20);

	CMFCPropertyGridProperty* pProp3 = new CMFCPropertyGridProperty(_T("բ�ſ���ˮλ��(cm)"), (_variant_t)0.0, _T("բ�ſ���ˮλ��(cm)"));
	
	pGroup1->AddSubItem(pProp3);
	
	
	m_PGCtrl.AddProperty(pGroup1);






	COLORREF clrBackground,clrText,clrGroupBackground,clrGroupText,
		clrDescriptionBackground,clrDescriptionText,clrLine;
	m_PGCtrl.GetCustomColors(clrBackground,clrText,clrGroupBackground,clrGroupText,
		clrDescriptionBackground,clrDescriptionText,clrLine);	
	m_PGCtrl.SetCustomColors(clrBackground,clrText,RGB(239,246,248),clrGroupText,
		RGB(239,246,248),clrDescriptionText,clrLine);


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
	// TODO: Add your control notification handler code here
	m_ConfigXml.AddElem(_T("����"));
	m_ConfigXml.AddChildElem(_T("com1"));

	m_ConfigXml.AddElem(_T("ˮλվ"));
	m_ConfigXml.AddChildElem(_T("բ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("բ��ˮλվ����"),_T(" "));
	m_ConfigXml.AddChildElem(_T("բ��ˮλվ���(cm)"),_T("0.0"));
	m_ConfigXml.AddChildElem(_T("բ��ˮλվվ��"),_T("1"));

	m_ConfigXml.OutOfElem();
	m_ConfigXml.AddChildElem(_T("բ��ˮλվ"));
	m_ConfigXml.IntoElem();
	m_ConfigXml.AddChildElem(_T("բ��ˮλվ����"),_T(" "));
	m_ConfigXml.AddChildElem(_T("բ��ˮλվ���(cm)"),_T("0.0"));
	m_ConfigXml.AddChildElem(_T("բ��ˮλվվ��"),_T("2"));


	m_ConfigXml.OutOfElem();
	m_ConfigXml.AddElem(_T("բ�ſ���ˮλ��(cm)"),_T("0.0"));
	

	m_ConfigXml.Save(_T("config.xml"));
	
	
	
	AfxMessageBox(_T("sdf"));





	OnOK();
}
