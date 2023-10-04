#pragma once


// CDialogLineThickness dialog

class CDialogLineThickness : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLineThickness)

public:
	CDialogLineThickness(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogLineThickness() {}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_THIDKNESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_thickness;
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
};
