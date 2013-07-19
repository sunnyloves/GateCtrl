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
#include "DataShowPane.h"




typedef struct _LevelStation
{	
	double dbLevelZero;				//零点
	CString sStationNO;				//站号

}LevelStation;

typedef struct _LevelStationCombo
{
	LevelStation lsInnerStation;	//内站
	LevelStation lsOuterStation;	//外站

}LevelStationCombo;

typedef struct _CtrlLevel
{
	double dbDeadLevel;				//死区水位
	double dbLevelError;			//开启水位差

}CtrlLevel;

typedef struct _ConfigInfo
{
	CString sCom;
	LevelStationCombo lsc_1;
	LevelStationCombo lsc_2;
	CtrlLevel clCtrlLevel;

}ConfigInfo;


typedef struct _LevelData
{
	double dbInnerLevel_1;
	double dbOuterLevel_1;
	double dbInnerLevel_2;
	double dbOuterLevel_2;

}LevelData;







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
	CDataShowPane m_wndDataShowPane;

	CMarkup m_ConfigXml;
	
	CnComm m_Com;
	
	BOOL m_bConfigBTState;
	BOOL m_bStartBTState;
	BOOL m_bStopBTState;
	BOOL m_bNextChartBTState;
	BOOL m_bNextLevelCombo;				//交替显示2组水位标志位
	CStdioFile m_LevelFile;


// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnConfigBT();
	afx_msg void OnUpdateConfigButton(CCmdUI* pCmdUI);

	afx_msg void OnStartCtrl();
	afx_msg void OnUpdateStartButton(CCmdUI* pCmdUI);

	afx_msg void OnStopCtrl();
	afx_msg void OnUpdateStopButton(CCmdUI* pCmdUI);

	afx_msg void OnNextChartClick();
	afx_msg void OnUpdateNextChartButton(CCmdUI* pCmdUI);


	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

	void InitializeRibbon();

	BOOL CheckConfigFile(void);
	void SetDefaultConfigFile(void);
	BOOL GetConfigFromFile(void);
	void WriteLevelToFile(void);
public:
	ConfigInfo ciConfigInfo;

	char m_ComTemp[10];

	double m_dbLevelError_1;		//实时误差1#站
	double m_dbLevelError_2;		//实时误差2#站

	LevelData m_ldLevelData;
	CArray<LevelData,LevelData&> m_LevelDataArray;
	//725
	LRESULT     m_lrErrCode;
	LONG        m_lDriverHandle;          // driver handle
	BYTE		m_byOutData	;
	PT_DioWritePortByte m_ptDioWritePortByte; // DioWritePortByte table


public:
	void SaveConfigToFile(void);

};


