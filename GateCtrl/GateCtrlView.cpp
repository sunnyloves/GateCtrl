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

// GateCtrlView.cpp : implementation of the CGateCtrlView class
//

#include "stdafx.h"
#include "GateCtrl.h"
#include "MainFrm.h"
#include "GateCtrlDoc.h"
#include "GateCtrlView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGateCtrlView

IMPLEMENT_DYNCREATE(CGateCtrlView, CView)

BEGIN_MESSAGE_MAP(CGateCtrlView, CView)
	ON_MESSAGE(WM_CONFIGREADYMESSAGE, OnInitView)
	ON_MESSAGE(WM_UPDATELEVEL,OnUpdateView)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CGateCtrlView construction/destruction

CGateCtrlView::CGateCtrlView()
{
	// TODO: add construction code here
	nCnt = 0;

}

CGateCtrlView::~CGateCtrlView()
{
}

BOOL CGateCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


void CGateCtrlView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_LevelChartCtrl.Create(this,CRect(0,0,100,100),IDC_LEVELCHARTCTRL);

	m_LevelChartCtrl.SetEdgeType(0);
	m_LevelChartCtrl.SetBackColor(RGB(239,246,248));
	CChartStandardAxis* pBottomAxis = 
		m_LevelChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->GetGrid()->SetColor(RGB(192,192,192));
	CChartStandardAxis* pLeftAxis =
		m_LevelChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);

	m_pLevel1inLineSeries = m_LevelChartCtrl.CreateLineSerie();
	m_pLevel1outLineSeries = m_LevelChartCtrl.CreateLineSerie();
	m_pLevel2inLineSeries = m_LevelChartCtrl.CreateLineSerie();
	m_pLevel2outLineSeries = m_LevelChartCtrl.CreateLineSerie();
	m_pLevel2outLineSeries->SetColor(RGB(255,128,64));

	m_pLevel2inLineSeries->SetVisible(false) ;
	m_pLevel2outLineSeries->SetVisible(false) ;
	
	pLeftAxis->GetGrid()->SetColor(RGB(192,192,192));
	pLeftAxis->SetMinMax(-4.0,4.0);
	pBottomAxis->SetMinMax(0.0,500.0);	
	pBottomAxis->EnableScrollBar(true);
	pBottomAxis->SetAutoHideScrollBar(true);

	m_pLevel1inLineSeries->SetSmooth(false);
	m_pLevel1outLineSeries->SetSmooth(false);
	m_pLevel2inLineSeries ->SetSmooth(false);
	m_pLevel2outLineSeries->SetSmooth(false);
	
	AdjustLayout();

	EnableWindow(false);//初始状态disable掉窗口

}







// CGateCtrlView drawing

void CGateCtrlView::OnDraw(CDC* pDC)
{
	CGateCtrlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;



	// TODO: add draw code for native data here
}


void CGateCtrlView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
	CRect   rect; 
	GetClientRect(&rect); 
	CBrush   brush; 
	brush.CreateSolidBrush(RGB(239,246,248));  
	dc.FillRect(&rect,&brush); 
}



void CGateCtrlView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGateCtrlView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CGateCtrlView diagnostics

#ifdef _DEBUG

void CGateCtrlView::AssertValid() const
{
	CView::AssertValid();
}

void CGateCtrlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGateCtrlDoc* CGateCtrlView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGateCtrlDoc)));
	return (CGateCtrlDoc*)m_pDocument;
}
#endif //_DEBUG


// CGateCtrlView message handlers

LRESULT CGateCtrlView::OnInitView(WPARAM wParam, LPARAM lParam)
{
	CString sTemp;


	
	this->EnableWindow(TRUE);

	return(0);

}


void CGateCtrlView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here

	if (m_LevelChartCtrl.GetSafeHwnd() != NULL )
	{
		AdjustLayout();
	}
		
	

	
}
/*
void CGateCtrlView::ShowStaticText(void)
{
	CString sTemp;

	CDC* pDC = GetDC();
	ASSERT(pDC);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();	

	CFont *pOldFont,m_font;

	VERIFY(m_font.CreatePointFont(170,_T("宋体"))); 

	
	pOldFont = pDC->SelectObject(&m_font);
//固定文本
	//pDC->SetBkColor(RGB(239,246,248));
	pDC->TextOut(50,10,_T("通讯口:"));
	sTemp = pMainFrame->ciConfigInfo.sCom;
	pDC->TextOut(220,10,sTemp);

		pDC->TextOut(50,50,_T("闸内站:"));
	sTemp = pMainFrame->ciConfigInfo.lsInnerStation.sStationName;	
	pDC->TextOut(220,50,sTemp);

	pDC->TextOut(350,50,_T("水位:"));
	sTemp.Format(_T("%.2f"), pMainFrame->m_dbInnerLevel);
	pDC->TextOut(500,50,sTemp);


	pDC->TextOut(50,100,_T("闸外站:"));
	sTemp = pMainFrame->ciConfigInfo.lsOuterStation.sStationName;	
	pDC->TextOut(220,100,sTemp);

	pDC->TextOut(350,100,_T("水位:"));


	pDC->TextOut(50,150,_T("闸内外水位差:"));


	pDC->TextOut(350,150,_T("开启水位差:"));
	sTemp.Format(_T("%.2f"), pMainFrame->ciConfigInfo.dbLevelError) ;	
	pDC->TextOut(500,150,sTemp);

	//

	
	pDC->TextOut(50,220,_T("闸门状态:"));


	pDC->SelectObject(pOldFont);

}
*/

LRESULT CGateCtrlView::OnUpdateView( WPARAM wParam, LPARAM lParam )
{
	//ShowDynmicText();
	double dbTemp;
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	dbTemp = pMainFrame->m_ldLevelData.dbInnerLevel_1;
	m_pLevel1inLineSeries->AddPoint((double)nCnt,dbTemp);
	dbTemp = pMainFrame->m_ldLevelData.dbOuterLevel_1;
	m_pLevel1outLineSeries->AddPoint((double)nCnt,dbTemp);

	dbTemp = pMainFrame->m_ldLevelData.dbInnerLevel_2;
	m_pLevel2inLineSeries ->AddPoint((double)nCnt,dbTemp);
	dbTemp = pMainFrame->m_ldLevelData.dbOuterLevel_2;
	m_pLevel2outLineSeries->AddPoint((double)nCnt,dbTemp);
	
	pMainFrame->m_LevelDataArray.SetAtGrow(nCnt,pMainFrame->m_ldLevelData);
	nCnt++;

	IO();
	
	
	return(0);
}


void CGateCtrlView::IO(void)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();	
	pMainFrame->m_ptDioWritePortByte.port = 0;
	pMainFrame->m_ptDioWritePortByte.mask  = 0xff;
	
	if ((pMainFrame->m_dbLevelError_1) > (pMainFrame->ciConfigInfo.clCtrlLevel.dbLevelError))
	{//闭合
		BYTE m_byOutData = 0x01;

		pMainFrame->m_ptDioWritePortByte.state = m_byOutData;
		DRV_DioWritePortByte(pMainFrame->m_lDriverHandle,
			(LPT_DioWritePortByte)&(pMainFrame->m_ptDioWritePortByte));

	}
	else
	{//打开
		BYTE m_byOutData = 0x00;

		pMainFrame->m_ptDioWritePortByte.state = m_byOutData;
		DRV_DioWritePortByte(pMainFrame->m_lDriverHandle,
			(LPT_DioWritePortByte)&(pMainFrame->m_ptDioWritePortByte));
	}
}



void CGateCtrlView::AdjustLayout(void)
{
	CRect rcClient,rcChart; 		
	GetClientRect(rcClient);

	rcChart = rcClient;		
	m_LevelChartCtrl.MoveWindow(rcChart);

}