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

// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "ParaConfigDlg.h "
#include "CMakeUp/Markup.h"
#include "CnCom/CnComm.h"
#include "CardDriver/Driver.h"

typedef struct _LevelStation
{
	CString sStationName;
	double dbLevelZero;
	CString sStationNO;
}LevelStation;



typedef struct _ConfigInfo
{
	CString sCom;
	LevelStation lsInnerStation;
	LevelStation lsOuterStation;
	double dbLevelError;
}ConfigInfo;



class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CParaConfigDlg m_wndParaConfigDlg;

	CMarkup m_ConfigXml;
	
	CnComm m_Com;
	
	BOOL m_bConfigBTState;
	BOOL m_bStartBTState;
	BOOL m_bStopBTState;
	char m_ComTemp[10];				//串口缓冲区
	BOOL m_bStationNOFlag;			//站号标识 0为1号站  1为2号站



// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnConfigBT();
	afx_msg void OnUpdateConfigButton(CCmdUI* pCmdUI);

	afx_msg void OnStartCtrl();
	afx_msg void OnUpdateStartButton(CCmdUI* pCmdUI);

	afx_msg void OnStopCtrl();
	afx_msg void OnUpdateStopButton(CCmdUI* pCmdUI);
	afx_msg LRESULT OnComRecv(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

	void InitializeRibbon();

	BOOL CheckConfigFile(void);
	void SetDefaultConfigFile(void);
	BOOL GetConfigFromFile(void);
	
public:
	ConfigInfo ciConfigInfo;
	double m_dbInnerLevel;
	double m_dbOuterLevel;
	double m_dbLevelError;

	LRESULT     m_lrErrCode;
	LONG        m_lDriverHandle;          // driver handle
	BYTE		m_byOutData	;
	PT_DioWritePortByte m_ptDioWritePortByte; // DioWritePortByte table


public:
	void SaveConfigToFile(void);

};


