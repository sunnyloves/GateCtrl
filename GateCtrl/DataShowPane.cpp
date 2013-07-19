// DataShowPane.cpp : implementation file
//

#include "stdafx.h"
#include "GateCtrl.h"
#include "DataShowPane.h"
#include "MainFrm.h"

// CDataShowPane

IMPLEMENT_DYNAMIC(CDataShowPane, CDockablePane)

CDataShowPane::CDataShowPane()
{

}

CDataShowPane::~CDataShowPane()
{
}


BEGIN_MESSAGE_MAP(CDataShowPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_UPDATELEVEL,OnUpdateView)
END_MESSAGE_MAP()








int CDataShowPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect   rect; 
	GetClientRect(&rect); 
	m_wndInfoListCtrl.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT, rect, this, IDC_INFOLISTCTRL);
	m_wndInfoListCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES);
	ShowStaticText();

	return 0;

}
// CDataShowPane message handlers
void CDataShowPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_wndInfoListCtrl.GetSafeHwnd() != NULL )
	{
		AdjustLayout();
	}
}



void CDataShowPane::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDockablePane::OnPaint() for painting messages
	CRect   rect; 
	GetClientRect(&rect); 
	CBrush   brush; 
	brush.CreateSolidBrush(RGB(239,246,248));  
	dc.FillRect(&rect,&brush); 
}

void CDataShowPane::AdjustLayout(void)
{
	CRect rcClient; 		
	GetClientRect(rcClient);
	m_wndInfoListCtrl.MoveWindow(rcClient);


}


void CDataShowPane::ShowStaticText(void)
{


	m_wndInfoListCtrl.InsertColumn(0,_T("名称"), LVCFMT_LEFT, 100);
	m_wndInfoListCtrl.InsertColumn(1,_T("值"), LVCFMT_LEFT, 100);
	m_wndInfoListCtrl.InsertColumn(2,_T("其他"), LVCFMT_LEFT, 100);

	m_wndInfoListCtrl.InsertItem(0,_T("通讯口"));
	m_wndInfoListCtrl.SetItemText(0,1,_T("com1"));
	
	m_wndInfoListCtrl.InsertItem(1,_T("龙目礁闸内"));	
	m_wndInfoListCtrl.SetItemText(1,2,_T("红色"));

	m_wndInfoListCtrl.InsertItem(2,_T("龙目礁闸外"));
	m_wndInfoListCtrl.SetItemText(2,2,_T("绿色"));

	m_wndInfoListCtrl.InsertItem(3,_T("上干山闸内"));
	m_wndInfoListCtrl.SetItemText(3,2,_T("蓝色"));

	m_wndInfoListCtrl.InsertItem(4,_T("上干山闸外"));
	m_wndInfoListCtrl.SetItemText(4,2,_T("橙色"));

	m_wndInfoListCtrl.InsertItem(5,_T("闸门状态"));


}


LRESULT CDataShowPane::OnUpdateView( WPARAM wParam, LPARAM lParam )
{
	//ShowDynmicText();
	double dbTemp;
	CString sTemp;
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	
	dbTemp = pMainFrame->m_ldLevelData.dbInnerLevel_1;
	sTemp.Format(_T("%.2f"),dbTemp);
	m_wndInfoListCtrl.SetItemText(1,1,sTemp);

	dbTemp = pMainFrame->m_ldLevelData.dbOuterLevel_1;
	sTemp.Format(_T("%.2f"),dbTemp);
	m_wndInfoListCtrl.SetItemText(2,1,sTemp);

	dbTemp = pMainFrame->m_ldLevelData.dbInnerLevel_2;
	sTemp.Format(_T("%.2f"),dbTemp);
	m_wndInfoListCtrl.SetItemText(3,1,sTemp);

	dbTemp = pMainFrame->m_ldLevelData.dbOuterLevel_2;
	sTemp.Format(_T("%.2f"),dbTemp);
	m_wndInfoListCtrl.SetItemText(4,1,sTemp);

	return(0);
}
