// DialogLineThickness.cpp : implementation file
//

#include "pch.h"
#include "PaintTool.h"
#include "DialogLineThickness.h"
#include "afxdialogex.h"


// CDialogLineThickness dialog

IMPLEMENT_DYNAMIC(CDialogLineThickness, CDialogEx)

CDialogLineThickness::CDialogLineThickness(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_THIDKNESS, pParent)
	, m_thickness(0)
{

}


void CDialogLineThickness::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_thickness);
}


BEGIN_MESSAGE_MAP(CDialogLineThickness, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDialogLineThickness::OnDeltaposSpin1)
END_MESSAGE_MAP()


void CDialogLineThickness::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// 스핀 컨트롤 방향 바꾸기.
	pNMUpDown->iDelta *= -1;

	*pResult = 0;
}
