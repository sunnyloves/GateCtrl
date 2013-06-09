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

#include "GateCtrlDoc.h"
#include "GateCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGateCtrlView

IMPLEMENT_DYNCREATE(CGateCtrlView, CView)

BEGIN_MESSAGE_MAP(CGateCtrlView, CView)
END_MESSAGE_MAP()

// CGateCtrlView construction/destruction

CGateCtrlView::CGateCtrlView()
{
	// TODO: add construction code here

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

void CGateCtrlView::OnDraw(CDC* /*pDC*/)
{
	CGateCtrlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

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
