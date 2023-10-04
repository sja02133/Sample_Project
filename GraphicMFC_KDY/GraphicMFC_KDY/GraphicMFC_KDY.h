
// GraphicMFC_KDY.h : main header file for the GraphicMFC_KDY application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGraphicMFCKDYApp:
// See GraphicMFC_KDY.cpp for the implementation of this class
//

class CGraphicMFCKDYApp : public CWinApp
{
public:
	CGraphicMFCKDYApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphicMFCKDYApp theApp;
