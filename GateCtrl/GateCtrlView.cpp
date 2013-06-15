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
	
	
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CGateCtrlView construction/destruction

CGateCtrlView::CGateCtrlView()
{
	// TODO: add construction code here
	m_bIsInitDone = FALSE;
	m_bIsGateOpen = FALSE;
	m_dbInnerLevel = 0.00;
	m_dbOuterLevel = 0.00;
	m_dbLevelError = 0.00;

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

// CGateCtrlView drawing

void CGateCtrlView::OnDraw(CDC* pDC)
{
	CGateCtrlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_bIsInitDone)
	{
		ShowStaticText();

	}

	// TODO: add draw code for native data here
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

	ShowStaticText();
	m_bIsInitDone = TRUE;
	return(0);

}


void CGateCtrlView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_bIsInitDone)
	{
		ShowStaticText();
	}
	// TODO: Add your message handler code here
}

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
	pDC->TextOut(50,50,_T("闸内站:"));
	sTemp = pMainFrame->ciConfigInfo.lsInnerStation.sStationName;	
	pDC->TextOut(220,50,sTemp);

	pDC->TextOut(350,50,_T("水位:"));
	sTemp.Format(_T("%.2f"), m_dbInnerLevel);
	pDC->TextOut(500,50,sTemp);


	pDC->TextOut(50,100,_T("闸外站:"));
	sTemp = pMainFrame->ciConfigInfo.lsOuterStation.sStationName;	
	pDC->TextOut(220,100,sTemp);

	pDC->TextOut(350,100,_T("水位:"));
	sTemp.Format(_T("%.2f"), m_dbOuterLevel);
	pDC->TextOut(500,100,sTemp);

	pDC->TextOut(50,150,_T("闸内外水位差:"));
	sTemp.Format(_T("%.2f"), m_dbLevelError);
	pDC->TextOut(220,150,sTemp);

	pDC->TextOut(350,150,_T("开启水位差:"));
	sTemp.Format(_T("%.2f"), pMainFrame->ciConfigInfo.dbLevelError);	
	pDC->TextOut(500,150,sTemp);

	//

	
	pDC->TextOut(50,220,_T("闸门状态:"));
	if (m_bIsGateOpen)
	{
		pDC->SetTextColor(RGB(0,255,0));
		pDC->TextOut(220,220,_T("开启"));
	}
	else
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->TextOut(220,220,_T("关闭"));
	}

	pDC->SelectObject(pOldFont);

}
