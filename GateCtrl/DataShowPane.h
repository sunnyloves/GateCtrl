#pragma once


// CDataShowPane

class CDataShowPane : public CDockablePane
{
	DECLARE_DYNAMIC(CDataShowPane)

public:
	CDataShowPane();
	virtual ~CDataShowPane();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg LRESULT OnUpdateView( WPARAM wParam, LPARAM lParam );

	void AdjustLayout(void);
protected:
	DECLARE_MESSAGE_MAP()
public:
	void ShowStaticText(void);


public:
	CMFCListCtrl m_wndInfoListCtrl;



};


