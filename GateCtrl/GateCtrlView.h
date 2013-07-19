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

// GateCtrlView.h : interface of the CGateCtrlView class
//

#include "ChartCtrl/ChartCtrl.h"
#include "ChartCtrl/ChartLineSerie.h"
#pragma once


class CGateCtrlView : public CView
{
protected: // create from serialization only
	CGateCtrlView();
	DECLARE_DYNCREATE(CGateCtrlView)

// Attributes
public:
	CGateCtrlDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:

// Implementation
public:
	virtual ~CGateCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


	int nCnt;									//µã×ÜÊý

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnInitView( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnUpdateView( WPARAM wParam, LPARAM lParam );
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()


protected:
	void AdjustLayout(void);


public:
//	void ShowInitView(void);	
//	void ShowStaticText(void);
//	void ShowDynmicText(void);
	void IO(void);

public:
	CChartCtrl			m_LevelChartCtrl;
	CChartLineSerie*	m_pLevel1inLineSeries;
	CChartLineSerie*	m_pLevel1outLineSeries;
	CChartLineSerie*	m_pLevel2inLineSeries;
	CChartLineSerie*	m_pLevel2outLineSeries;




};

#ifndef _DEBUG  // debug version in GateCtrlView.cpp
inline CGateCtrlDoc* CGateCtrlView::GetDocument() const
   { return reinterpret_cast<CGateCtrlDoc*>(m_pDocument); }
#endif

