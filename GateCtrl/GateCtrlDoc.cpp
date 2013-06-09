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

// GateCtrlDoc.cpp : implementation of the CGateCtrlDoc class
//

#include "stdafx.h"
#include "GateCtrl.h"

#include "GateCtrlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGateCtrlDoc

IMPLEMENT_DYNCREATE(CGateCtrlDoc, CDocument)

BEGIN_MESSAGE_MAP(CGateCtrlDoc, CDocument)
END_MESSAGE_MAP()


// CGateCtrlDoc construction/destruction

CGateCtrlDoc::CGateCtrlDoc()
{
	// TODO: add one-time construction code here

}

CGateCtrlDoc::~CGateCtrlDoc()
{
}

BOOL CGateCtrlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CGateCtrlDoc serialization

void CGateCtrlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CGateCtrlDoc diagnostics

#ifdef _DEBUG
void CGateCtrlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGateCtrlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGateCtrlDoc commands
