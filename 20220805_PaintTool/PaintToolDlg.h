
// PaintToolDlg.h : header file
//

#pragma once


// CPaintToolDlg dialog
class CPaintToolDlg : public CDialogEx
{
// Construction
public:
	CPaintToolDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAINTTOOL_DIALOG };
#endif

	// 상단 툴바
	CToolBar m_wndToolBar;

	// 하단 상태바
	CStatusBar m_wndStatusBar;

	// 툴바와 상태바 초기화
	void InitControlBar();

	// 상태바에 글쓰기
	void SetPaneText(UINT ndx, const TCHAR* fmt, ...);

	// 화면에 그리기
	void drawVectorData(CDC* dc);

	bool beDrawing = FALSE;
	CPoint c_point;
	CPen pen;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnToolbarColor();
	afx_msg void OnToolbarLine();
	afx_msg void OnToolbarClear();
	afx_msg void OnToolbarSave();
	afx_msg void OnToolbarUndo();
	afx_msg void OnToolbarRedo();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

inline void CPaintToolDlg::SetPaneText(UINT ndx, const TCHAR* fmt, ...) {
	CString text;
	if (m_wndStatusBar.m_hWnd == NULL || ndx >= 3)
		return;

	TCHAR local_logbuf[1024];
	va_list args;
	va_start(args, fmt);
	_vstprintf_s(local_logbuf, 1024, fmt, args);
	va_end(args);

	m_wndStatusBar.SetPaneText(ndx, local_logbuf, TRUE);
}

inline BOOL CPaintToolDlg::OnEraseBkgnd(CDC* pDC) {
	if (m_wndStatusBar.m_hWnd) {
		CRect rc;
		m_wndStatusBar.GetWindowRect(rc);
		ScreenToClient(rc);
		pDC->ExcludeClipRect(rc);
	}
	return CDialogEx::OnEraseBkgnd(pDC);
}