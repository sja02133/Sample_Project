
// PaintTool.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPaintToolApp:
// See PaintTool.cpp for the implementation of this class
//

#include <vector>
#include <stack>
#include <list>
#include <queue>

#include <memory>


using namespace std;

class fileSettingData {
public:
	CString fileName;
	CString folrderPath;
	CString fileFilter;
};

class penThickness {
public:
	penThickness() : thickness(1) {
	}
	unsigned int thickness;
};

class penColor {
public:
	penColor() {
		red = 0;
		green = 0;
		blue = 0;
	}
	unsigned int red;
	unsigned int green;
	unsigned int blue;
};

class pointPaint {
public:
	CPoint before_point;
	CPoint last_point;
};

class HugeData {
public:
	//	bool checking_Draw = TRUE;
	penThickness set_thickness;
	penColor set_color;
	vector<pointPaint> point;
};


class CPaintToolApp : public CWinApp
{
public:
	CPaintToolApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	list<HugeData> list_hugeData;
	stack<HugeData> stack_hugeData;

	fileSettingData fileSet;

	DECLARE_MESSAGE_MAP()
};

extern CPaintToolApp theApp;
extern HugeData theData;