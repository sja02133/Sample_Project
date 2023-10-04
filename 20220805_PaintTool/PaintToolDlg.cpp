
// PaintToolDlg.cpp : implementation file
//

#include "pch.h"
#include "PaintTool.h"
#include "PaintToolDlg.h"
#include "afxdialogex.h"
#include "DialogLineThickness.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPaintToolDlg::CPaintToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAINTTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 레지스트리에 저장된 값을 읽어온다.
	theData.set_thickness.thickness = AfxGetApp()->GetProfileInt(_T("Setup"), _T("Thickness"), 1);
	COLORREF rgb = AfxGetApp()->GetProfileInt(_T("Setup"), _T("Color"), RGB(0,0,0));
	theData.set_color.red = GetRValue(rgb);
	theData.set_color.green = GetGValue(rgb);
	theData.set_color.blue = GetBValue(rgb);
}

void CPaintToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPaintToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_COMMAND(ID_BUTTON_COLOR, &CPaintToolDlg::OnToolbarColor)
	ON_COMMAND(ID_BUTTON_LINE, &CPaintToolDlg::OnToolbarLine)
	ON_COMMAND(ID_BUTTON_CLEAR, &CPaintToolDlg::OnToolbarClear)
	ON_COMMAND(ID_BUTTON_SAVE, &CPaintToolDlg::OnToolbarSave)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPaintToolDlg message handlers
static UINT BASED_CODE indicators[] = {
	ID_INDICATOR_COLOR,
	ID_INDICATOR_LINE,
	ID_INDICATOR_MOUSE
};

#define TIMER_MOUSE	1

BOOL CPaintToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// 툴바와 상태바를 초기화 한다.
	InitControlBar();

	// 상태바에 필요한 항목을 써준다.
	SetPaneText(0, _T("색상 (R:%d, G:%d, B:%d)"), theData.set_color.red, theData.set_color.green, theData.set_color.blue);
	SetPaneText(1, _T("두께 (%d)"), theData.set_thickness.thickness);

	// 마우스 좌표를 상태바에 뿌려주는 타이머
	SetTimer(TIMER_MOUSE, 25, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaintToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (theApp.list_hugeData.size() > 0) {
			// 데이터가 있으면 그려주고
			CPaintDC dc(this);
			drawVectorData(&dc);
		}
		else {
			// 없으면 기본값
			CDialogEx::OnPaint();
		}
	}
}

void CPaintToolDlg::OnToolbarColor()
{
	// 툴바에서 컬러 버튼을 누르면 색상을 설정한다.
	CColorDialog dlg(RGB(theData.set_color.red, theData.set_color.green, theData.set_color.blue), CC_FULLOPEN);
	if (dlg.DoModal() != IDOK)
		return;

	theData.set_color.red = GetRValue(dlg.GetColor());
	theData.set_color.green = GetGValue(dlg.GetColor());
	theData.set_color.blue = GetBValue(dlg.GetColor());

	SetPaneText(0, _T("색상 (R:%d, G:%d, B:%d)"), theData.set_color.red, theData.set_color.green, theData.set_color.blue);
}

void CPaintToolDlg::OnToolbarLine()
{
	// 툴바에서 선 두께 버튼을 누르면 두께를 설정한다.
	CDialogLineThickness dlg;
	dlg.m_thickness = theData.set_thickness.thickness;
	if (dlg.DoModal() != IDOK)
		return;
	theData.set_thickness.thickness = dlg.m_thickness;
	SetPaneText(1, _T("두께 (%d)"), theData.set_thickness.thickness);
}

void CPaintToolDlg::OnToolbarClear()
{
	// 툴바에서 지우개 버튼을 눌렀다.
	if (::MessageBox(m_hWnd, _T("그린 항목을 전부 삭제합니다."), _T("확인"), MB_OKCANCEL | MB_ICONQUESTION) != IDOK)
		return;

	theApp.list_hugeData.clear();
	while (!theApp.stack_hugeData.empty()) theApp.stack_hugeData.pop();

	Invalidate();
}

void CPaintToolDlg::OnToolbarSave()
{
	// 툴바에서 저장 버튼을 눌렀다.
	CString file = L"";
	CString fileFilter = _T("All Files(*.*)| *.*; ||");
	CFileDialog file_Dlg(FALSE, L"bmp", L"", 0, fileFilter, this, 0, 1);
	if (file_Dlg.DoModal() != IDOK)
		return;

	file = file_Dlg.GetPathName();
	
	int name_pos = file.GetLength() - (file.ReverseFind(L'\\') + 1);
	int folder_pos = file.GetLength() - name_pos;
	theApp.fileSet.fileName = file.Right(name_pos);
	theApp.fileSet.folrderPath = file.Left(folder_pos);
	theApp.fileSet.fileFilter = theApp.fileSet.fileName;

	HDC hdc = ::GetDC(m_hWnd);

	CRect rtClient, rc1, rc2;
	this->GetClientRect(&rtClient);
	m_wndToolBar.GetWindowRect(rc1);
	m_wndStatusBar.GetWindowRect(rc2);
	rtClient.top += rc1.Height();
	rtClient.bottom -= rc2.Height();

	int width = rtClient.Width();
	int height = rtClient.Height();

	BITMAPINFO dib_define;
	dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	dib_define.bmiHeader.biWidth = width;
	dib_define.bmiHeader.biHeight = height;
	dib_define.bmiHeader.biPlanes = 1;
	dib_define.bmiHeader.biBitCount = 24;
	dib_define.bmiHeader.biCompression = BI_RGB;
	dib_define.bmiHeader.biSizeImage = (((width * 24 + 31) & ~31) >> 3) * height;
	dib_define.bmiHeader.biXPelsPerMeter = 0;
	dib_define.bmiHeader.biYPelsPerMeter = 0;
	dib_define.bmiHeader.biClrImportant = 0;
	dib_define.bmiHeader.biClrUsed = 0;

	BYTE* p_image_data = NULL;

	HBITMAP h_bitmap = ::CreateDIBSection(hdc, &dib_define, DIB_RGB_COLORS, (void**)&p_image_data, 0, 0);

	HDC h_memory_dc = ::CreateCompatibleDC(hdc);

	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);

	::BitBlt(h_memory_dc, 0, 0, width, height, hdc, 0, rtClient.top, SRCCOPY);

	::SelectObject(h_memory_dc, h_old_bitmap);

	DeleteDC(h_memory_dc);

	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	CString directory;
	char* savePath;

	USES_CONVERSION;
	savePath = W2A((theApp.fileSet.folrderPath).GetString());
	FILE* p_file;
	fopen_s(&p_file, W2A((theApp.fileSet.fileName).GetString()), "wb");
	if (p_file != NULL) {
		fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
		fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
		fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
		fclose(p_file);
	}

	if (NULL != h_bitmap) DeleteObject(h_bitmap);
	if (NULL != hdc) ::ReleaseDC(NULL, hdc);
}

void CPaintToolDlg::OnToolbarUndo()
{
	// 툴바에 버튼을 만들지는 않고, 그냥 함수 이름을 이렇게 했다.
	// 나중에 툴바에 버튼 넣으면 연결하기 편하라고
	// Ctrl + Z 언두 기능
	if (theApp.list_hugeData.empty() != TRUE) {
		theApp.stack_hugeData.push(theApp.list_hugeData.back());
		theApp.list_hugeData.pop_back();
		Invalidate(TRUE);
	}
}

void CPaintToolDlg::OnToolbarRedo()
{
	// 툴바에 버튼을 만들지는 않고, 그냥 함수 이름을 이렇게 했다.
	// 나중에 툴바에 버튼 넣으면 연결하기 편하라고
	// Ctrl + Y 리두 기능
	if (theApp.stack_hugeData.empty() != TRUE) {
		theApp.list_hugeData.push_back(theApp.stack_hugeData.top());
		theApp.stack_hugeData.pop();
		Invalidate(TRUE);
	}
}


void CPaintToolDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	beDrawing = TRUE;
	c_point.x = point.x;
	c_point.y = point.y;
	SetCapture();

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPaintToolDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (beDrawing == TRUE) {
		theApp.list_hugeData.push_back(theData);
		theData.point.clear();
		if (theApp.stack_hugeData.size() > 0) {
			while (theApp.stack_hugeData.empty() == FALSE)
				theApp.stack_hugeData.pop();
		}
	}
	beDrawing = FALSE;
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CPaintToolDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	CPen tempPen;

	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, theData.set_thickness.thickness, RGB(theData.set_color.red, theData.set_color.green, theData.set_color.blue));
	dc.SelectObject(&pen);
	pointPaint set_point;

	if (beDrawing == TRUE) {
		//마우스 좌클릭 도중
		set_point.before_point.x = c_point.x;
		set_point.before_point.y = c_point.y;
		//MoveToEx(hdc, c_point.x, c_point.y, NULL);
		dc.MoveTo(c_point.x, c_point.y);
		c_point.x = point.x;
		c_point.y = point.y;
		set_point.last_point.x = c_point.x;
		set_point.last_point.y = c_point.y;
		dc.LineTo(c_point.x, c_point.y);
		theData.point.push_back(set_point);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CPaintToolDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_MOUSE)
	{
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		SetPaneText(2, _T("마우스 (X: %d, Y: %d)"), pt.x, pt.y);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CPaintToolDlg::InitControlBar()
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_BORDER_ANY;
	if (m_wndToolBar.CreateEx(this, TBSTYLE_TOOLTIPS, dwStyle) && m_wndToolBar.LoadToolBar(IDR_TOOLBAR))
	{
		CRect rcClientStart;
		CRect rcClientNow;
		GetClientRect(rcClientStart);
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNow);

		CPoint ptOffset(rcClientNow.left - rcClientStart.left, rcClientNow.top - rcClientStart.top);
		CRect rcChild;
		CWnd* pwndChild = GetWindow(GW_CHILD);
		while (pwndChild) {
			pwndChild->GetWindowRect(rcChild);
			ScreenToClient(rcChild);
			rcChild.OffsetRect(ptOffset);
			pwndChild->MoveWindow(rcChild, FALSE);
			pwndChild = pwndChild->GetNextWindow();
		}	
		CRect rcWindow;	
		GetWindowRect(rcWindow);

		rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
		rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
		MoveWindow(rcWindow, FALSE);
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	}

	dwStyle = WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | CBRS_BOTTOM | CBRS_SIZE_FIXED;
	if (m_wndStatusBar.CreateEx(this, SBT_TOOLTIPS, dwStyle)) {                 // We create the status bar
		m_wndStatusBar.SetIndicators(indicators, 3); // Set the number of panes

		CRect rect;
		GetClientRect(&rect);

		// Size the two panes
		m_wndStatusBar.SetPaneInfo(0, ID_INDICATOR_COLOR, SBPS_NORMAL, rect.Width() / 3);
		m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_LINE, SBPS_STRETCH, rect.Width() / 3);
		m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_MOUSE, SBPS_STRETCH, rect.Width() / 3);

		// This is where we actually draw it on the screen
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	}
}


void CPaintToolDlg::drawVectorData(CDC* dc) {
	//다시 그린다. 어디까지? -> theApp.vector_hugeData.checkingDraw가 FALSE 전까지

	int i = 0, j = 0;
	HWND hWnd = ::GetActiveWindow();
	CString temp_thickness = L"", temp_rgb = L"";
	vector<pointPaint>::iterator point_iter;
	queue<int> m_int;

	for (auto hugeData_iter = theApp.list_hugeData.begin(); hugeData_iter != theApp.list_hugeData.end(); hugeData_iter++) {
		HugeData& data = *hugeData_iter;

		CPen temp_pen(PS_SOLID, data.set_thickness.thickness,
			RGB(data.set_color.red, data.set_color.green, data.set_color.blue));

		CPen* old_pen = dc->SelectObject(&temp_pen);
		for (point_iter = data.point.begin(); point_iter != data.point.end(); point_iter++) {
			dc->MoveTo(point_iter->before_point.x, point_iter->before_point.y);
			dc->LineTo(point_iter->last_point.x, point_iter->last_point.y);
		}
		dc->SelectObject(old_pen);
	}
}

void CPaintToolDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 프로그램 종료할 때, 선두께와 색상을 저장한다.
	AfxGetApp()->WriteProfileInt(_T("Setup"), _T("Thickness"), theData.set_thickness.thickness);
	AfxGetApp()->WriteProfileInt(_T("Setup"), _T("Color"), RGB(theData.set_color.red, theData.set_color.green, theData.set_color.blue));
}


BOOL CPaintToolDlg::PreTranslateMessage(MSG* pMsg)
{

	if (pMsg->message == WM_KEYDOWN) {
		if (::GetKeyState(VK_CONTROL) < 0 && pMsg->wParam == _T('Z') /* 'Z' key */) {
			OnToolbarUndo();
			return TRUE;
		}
		else if (::GetKeyState(VK_CONTROL) < 0 && pMsg->wParam == _T('Y') /* 'Y' key */) {
			OnToolbarRedo();
			return TRUE;
		}
		else if (::GetKeyState(VK_CONTROL) < 0 && pMsg->wParam == _T('S') /* 'S' key */) {
			OnToolbarSave();
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
