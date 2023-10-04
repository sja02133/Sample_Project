
// GraphicMFC_KDYView.h : interface of the CGraphicMFCKDYView class
//

#pragma once

#include <vector>
#include <stdio.h>
#include <conio.h>

#define HORIZ_DIR 0
#define VERT_DIR 900

const double PI = 3.1415926;


struct POLY_STRUCT {
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
	int x4;
	int y4;
};

enum color_book
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE,
	LIGHTCYAN
};

enum color_mfc
{
	MFC_BLACK = RGB(0, 0, 0),
	MFC_BLUE = RGB(0, 0, 255),
	MFC_GREEN = RGB(0, 255, 0),
	MFC_CYAN = RGB(0, 254, 255),
	MFC_RED = RGB(255, 0, 0),
	MFC_MAGENTA = RGB(255, 0, 255),
	MFC_BROWN = RGB(165, 42, 42),
	MFC_LIGHTGRAY = RGB(211, 211, 211),
	MFC_DARKGRAY = RGB(169, 169, 169),
	MFC_LIGHTBLUE = RGB(173, 216, 230),
	MFC_LIGHTGREEN = RGB(144, 238, 144),
	MFC_LIGHTRED = RGB(255, 204, 203),
	MFC_LIGHTMAGENTA = RGB(255, 128, 255),
	MFC_YELLOW = RGB(255, 255, 0),
	MFC_WHITE = RGB(255, 255, 255),
	MFC_LIGHTCYAN = RGB(224,255,255)
};

enum brush_color
{
	 BOOK_WHITE_BRUSH,
	 BOOK_LTGRAY_BRUSH,
	 BOOK_GRAY_BRUSH,
	 BOOK_DKGRAY_BRUSH,
	 BOOK_BLACK_BRUSH,
	 BOOK_NULL_BRUSH,
	 BOOK_HOLLOW_BRUSH = BOOK_NULL_BRUSH,
	 BOOK_WHITE_PEN,
	 BOOK_BLACK_PEN,
	 BOOK_NULL_PEN,
	 BOOK_OEM_FIXED_FONT,
	 BOOK_ANSI_FIXED_FONT,
	 BOOK_ANSI_VAR_FONT,
	 BOOK_SYSTEM_FONT,
	 BOOK_DEVICE_DEFAULT_FONT,
	 BOOK_DEFAULT_PALETTE,
	 BOOK_SYSTEM_FIXED_FONT,
};

enum book_brush_style
{
	SOLID_LINE,		//실선
	DOTTED_LINE,	//점선
	CENTER_LINE,	//일점쇄선
	DASHED_LINE,	//파선
	USERBIT_LINE	//사용자 정의 스타일
};

enum book_brush_size
{
	NORM_WIDTH = 1,	//보통 굵기(1도트 폭)
	THICK_WIDTH = 3	//굵은 선(3도트 폭)
};

struct PENDATA {
	int style;
	int nwidth;
	COLORREF color;
	unsigned upattern;
	BOOL checkUse;
};

struct BKDATA {
	COLORREF color;
	BOOL checkUse;
};

enum book_text_align_horiz {
	LEFT_TEXT = TA_LEFT,
	CENTER_TEXT = TA_CENTER,
	RIGHT_TEXT = TA_RIGHT	
};

enum book_text_align_vertical {
	BOTTOM_TEXT = TA_BOTTOM,
	TOP_TEXT = TA_TOP
};


enum fill_pattern {
	EMPTY_FILL,
	SOLID_FILL,
	LINE_FILL,
	LTSLASH_FILL,
	SLASH_FILL,
	BKSLASH_FILL,
	LTBKSLASH_FILL,
	HATCH_FILL,
	XHATCH_FILL,
	INTERLEAVE_FILL,
	WIDE_DOT_FILL,
	CLOSE_DOT_FILL,
	USER_FILL
};

enum fill_pattern_MFC {
	MFC_EMPTY_FILL = -2,
	MFC_SOLID_FILL = -1,
	MFC_LINE_FILL = HS_HORIZONTAL,
	MFC_LTSLASH_FILL = HS_BDIAGONAL,
	MFC_SLASH_FILL = HS_DIAGCROSS,
	MFC_BKSLASH_FILL = HS_FDIAGONAL,
	MFC_LTBKSLASH_FILL = HS_FDIAGONAL,
	MFC_HATCH_FILL = HS_CROSS,
	MFC_XHATCH_FILL = HS_DIAGCROSS,
	MFC_INTERLEAVE_FILL = 0,
	MFC_WIDE_DOT_FILL = 0,
	MFC_CLOSE_DOT_FILL = 0,
	MFC_USER_FILL = 0
};

struct FILL_PATTERN
{
	int pattern;
	BOOL checkUse;
	COLORREF color;
};

struct FILL_POINT
{
	int leftTopX;
	int leftTopY;
	int rightBottomX;
	int rightBottomY;
};

struct textsetting {
	
	int font;		//텍스트 폰트(0 ~ 4)
	int direction;	//텍스트 표시 방향(0,1)
	int charsize;	//문자 크기(0 ~ 10)
	int horiz;		//수평 방향의 위치 기준(0 ~ 2)
	int vert;		//수식 방향의 위치 기준(0 ~ 2)
};

enum TURBOCPLUSPLUS_FONT {
	DEFAULT_FONT,
	TRIPLEX_FONT,
	SMALL_FONT,
	SANS_SERIF_FONT,
	GOTHIC_FONT,
	SCRIPT_FONT,
	SIMPLEX_FONT,
	TRIPLEX_SCR_FONT,
	COMPLEX_FONT,
	EUROPEAN_FONT,
	BOLD_FONT
};
/*
struct arccoordstype {
	int x, y;
	int xstart, ystart, xend, yend;
};
*/
#define TRIPLEX_FONT 9 //맑은 고딕

struct BITMAP_DATA {
	int width;
	int height;
	//보류
};

struct FONT_DATA {
	int nHeight; int nWidth;//글자높이  글자너비	  
	int nEscapement;		//출력 각도
	int nOrientation;		//기준 선에서의 각도
	int nWeight;			//글자 굵기
	BYTE bItalic;			//Italic 적용 여부
	BYTE bUnderline;		//밑줄 적용 여부
	BYTE cStrikeOut;		//취소선 적용 여부
	BYTE nCharSet;			//문자셋 종류
	BYTE nOutPrecision;		//출력정밀도
	BYTE nClipPrecision;	//클리핑정밀도
	BYTE nQuality;			//출력문자품질
	BYTE nPitchAndFamily;	//글꼴Pitch
	LPCTSTR lpszFacename;	//글꼴
	int loadCount;			//호출 횟수
};

struct USE_PenFillFont {
	COLORREF pen_color;
	int pen_style;
	int pen_nWidth;
	BOOL usePenCheck;
	
	BOOL useFillCheck;
	COLORREF fill_color;
	int pattern;

	BOOL useFontCheck;
	int font;
	int direction;
	int font_size;
	int upattern;
	CString fontStr;
};

struct arccoordstype {
	//eclipse, arc, circle, pie, sector,

	// center point of arc
	int x, y;

	// start position                
	int xstart, ystart;

	// end position        
	int xend, yend;
};

enum putimage_op {
	COPY_CUT,	//Copy
	XOR_PUT,	//Exclusive or
	OR_PUT,		//Inclusive or
	AND_PUT,	//And
	NOT_PUT		//Copy the inverse of source
};


class CGraphicMFCKDYView : public CView
{
protected: // create from serialization only
	CGraphicMFCKDYView() noexcept;
	DECLARE_DYNCREATE(CGraphicMFCKDYView)

// Attributes
public:
	CGraphicMFCKDYDoc* GetDocument() const;

	BOOL checkingExistColorSetting();
	void settingFontData(int font, int direction, int font_size);
	void initialized_font();
	void initialized_usePFF();

	void test(CDC* pDC);

	void example01(CDC* pDC);
	void example02(CDC* pDC);
	void example03(CDC* pDC);
	void example04(CDC* pDC);
	void example05(CDC* pDC);
	void example06(CDC* pDC);
	void example07(CDC* pDC);
	void example08(CDC* pDC);
	void example09(CDC* pDC);
	void example10(CDC* pDC);
	void example11(CDC* pDC);
	void example12(CDC* pDC);
	void example13(CDC* pDC);
	void example14(CDC* pDC);
	void example15(CDC* pDC);
	void example16(CDC* pDC);
	void example17(CDC* pDC);
	void example18(CDC* pDC);
	void example19(CDC* pDC);
	void example20(CDC* pDC);
	void example21(CDC* pDC);
	void example22(CDC* pDC);
	void example23(CDC* pDC);
	void example24(CDC* pDC);
	void example25(CDC* pDC);
	void example26(CDC* pDC);
	void example27(CDC* pDC);
	void example28(CDC* pDC);
	void example29(CDC* pDC);
	void example30(CDC* pDC);
	void example31(CDC* pDC);
	void example32(CDC* pDC);
	void example33(CDC* pDC);
	void example34(CDC* pDC);
	void example35(CDC* pDC);
	void example36(CDC* pDC);
	void example37(CDC* pDC);
	void example38(CDC* pDC);
	void example39(CDC* pDC);
	void example40(CDC* pDC);
	void example41(CDC* pDC);
	void example42(CDC* pDC);
	void example43(CDC* pDC);
	void example44(CDC* pDC);
	void example45(CDC* pDC);
	void example46(CDC* pDC);
	void example47(CDC* pDC);
	void example48(CDC* pDC);
	void example49(CDC* pDC);
	void example50(CDC* pDC);
	void example51(CDC* pDC);
	void example52(CDC* pDC);
	void example53(CDC* pDC);
	void example54(CDC* pDC);
	void example55(CDC* pDC);
	void example56(CDC* pDC);
	void example57(CDC* pDC);
	void example58(CDC* pDC);
	void example59(CDC* pDC);
	void example60(CDC* pDC);
	void example61(CDC* pDC);
	void example62(CDC* pDC);
	void example63(CDC* pDC);
	void example64(CDC* pDC);
	void example65(CDC* pDC);
	void example66(CDC* pDC);
	void example67(CDC* pDC);
	void example68(CDC* pDC);
	void example69(CDC* pDC);
	void example70(CDC* pDC);
	void example71(CDC* pDC);
	void example72(CDC* pDC);
	void example73(CDC* pDC);
	void example74(CDC* pDC);
	void example75(CDC* pDC);
	void example76(CDC* pDC);
	void example77(CDC* pDC);
	void example78(CDC* pDC);
	void example79(CDC* pDC);
	void example80(CDC* pDC);
	void example81(CDC* pDC);
	void example82(CDC* pDC);
	void example83(CDC* pDC);
	void example84(CDC* pDC);
	void example85(CDC* pDC);
	void example86(CDC* pDC);
	void example87(CDC* pDC);
	void example88(CDC* pDC);
	void example89(CDC* pDC);
	void example90(CDC* pDC);

//	void settingPolyData(POLY_STRUCT& poly,
//		int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	void circle(CDC* pDC,int x, int y, int radius);
	void line(CDC* pDC,int startX, int startY, int endX, int endY);
	void lineto(CDC* pDC, int endX, int endY);
	
	void rectangle(CDC* pDC, int leftTopX, int leftTopY, int rightBottomX, int rightBottomY);
	void arcCircle_book(CDC* pDC, int x, int y, int startAngle, int endAngle, int radius);
	void ellipse(CDC* pDC, int x, int y, int startAngle, int endAngle, int xradius, int yradius);
	void drawPloy(CDC* pDC, int number, int* polypoints);
	void bar(CDC* pDC, int leftTopX, int leftTopY, int rightBottomX, int rightBottomY);
	void bar3d(CDC* pDC, int leftTopX,int leftTopY,
		int rightBottomX, int rightBottomY,int depth,int topFlag);
	void sector(CDC* pDC, int x, int y, int startAngle, int endAngle, int xradius, int yradius);
	void pieslice(CDC* pDC, int x, int y, int startAngle, int endAngle, int radius);
	void fillellipse(CDC* pDC, int x, int y, int xradius, int yradius);
	void fillPoly(CDC* pDC, int number, int* polypoints);
	void putpixel(CDC* pDC, int x, int y, int color);
	void lissajous(CDC* pDC, int x0, int y0,
		int fx, int fy, int radius, int delta, COLORREF color);
	void my_circle(CDC* pDC, int x, int y, int radius);
	void my_circle_c(CDC* pDC, int x, int y, int radius,int color);
	void my_arc(CDC* pDC, int x, int y, int radius, int color, int startAngle,int endAngle);
	void frame(CDC* pDC, int c);
	void frame(CDC* pDC);
	void my_text(CDC* pDC);
	void round_rec(CDC* pDC, int x, int y, int w, int h, int r, int dc);
	void gwindow(CDC* pDC, int x1, int y1, int x2, int y2, int color, char str[]);
	void initialize_fill_pattern();
	std::vector<FILL_POINT> setting_pattern(int leftTopX, int leftTopY, int rightBottomX, int rightBottomY);
	void figure(CDC* pDC);
	void title_example45(CDC* pDC);
	void star1(CDC* pDC, int x0, int y0, int r, double a, int c);
	void star2(CDC* pDC, int x0, int y0, int r, double a, int c);
	void star2_example48(CDC* pDC, int x0, int y0, int r, double a, int c);
	void star2_example49(CDC* pDC, int x0, int y0, int r, double a, int c);

	
	void gwindow_example48(CDC* pDC, int x1, int y1, int x2, int y2, int color, char str[]);
	
	void setcolor(CDC* pDC,int color);
//	CPen* gettingCPenObject(COLORREF color);
	void settextstyle(CDC* pDC,int font,int direction,int font_size);
	void outtextxy(CDC* pDC, int x, int y, CString text);
	void setbkcolor(CDC* pDC, int color);
	void setpallette(CDC* pDC, int prev_color, int next_color);
	void setlinestyle(CDC* pDC, int line_style, int color , int line_size);
	void settextjustify(CDC* pDC, int horiz, int vertical);
	void lineout(CDC* pDC, int y, unsigned m, CString str);
	void title(CDC* pDC);
	void fillstyledemo(CDC* pDC);
	void setfillstyle(CDC* pDC, int pattern, int color);
	int getcolor();
	void colordemo(CDC* pDC);
	void clearDevice(CDC* pDC);
	void setfillpattern(CDC* pDC, char* upattern, int color);
	void cframe(CDC* pDC, int x, int y, int x_d, int y_d, int d, int bc, int fc, int sc);
	void special_day(CDC* pDC, int date, int color);
	void gettextsetting(CDC* pDC, struct textsetting* text);
	void registerbgifont(CDC* pDC, void (*font)(CDC* pDC));
	void triplex_font(CDC* pDC);
	void small_font(CDC* pDC);
	void sansserif_font(CDC* pDC);
	void gothic_font(CDC* pDC);
	void setusercharsize(CDC* pDC,int multx, int divx, int multy, int divy);
	void char_in_box1(CDC* pDC, int left, int top, int right, int bottom, CString str);
	void char_in_box2(CDC* pDC, int left, int top, int right, int bottom, CString str);
	void char_in_box3(CDC* pDC, int left, int top, int right, int bottom, CString str);
	void char_in_box4(CDC* pDC, int left, int top, int right, int bottom, CString str);
	void char_in_box5(CDC* pDC, int left, int top,int font, int color, int size, CString str);

	void bold_char1(CDC* pDC, int x, int y, int font, int color, CString str);
	void bold_char2(CDC* pDC, int x, int y, int font, int color, CString str);
	void bold_char3(CDC* pDC, int x, int y, int font, int color, CString str);
	void bold_char(CDC* pDC, int x, int y, int font,
		int color, CString str,int xd,int yd);
	void line_char(CDC* pDC, int x, int y, int font,
		int size, int color, CString str);
	void line_char_example64(CDC* pDC, int x, int y, int font,
		int size, int color, CString str);
	void line_char_example65(CDC* pDC, int x, int y, int font,
		int size, int color, CString str);
	void reverse_char(CDC* pDC, int left, int top, int color, CString str);
	void shadow_char(CDC* pDC, int x, int y, int sc, int fc, int font, int size, CString str, int d);
	void shadow_char1(CDC* pDC, int x, int y, int sc, int fc, int font, int size, CString str, int d);
	void shadow_char2(CDC* pDC, int x, int y, int fc, int font, int size, CString str, int d);
	void change_palette_g(CDC* pDC);
	void getpallette(CDC* pDC, CPalette* c_pal);
	void setrgbpalette(CDC* pDC, int palette_num, int r, int g, int b);
	void change_palette(CDC* pDC);
	void shadow_char3(CDC* pDC, int x, int y, int fc, int font, int size, CString str, int d);
	void hollow_char1(CDC* pDC, int x, int y, int dc, int fc, int font, int size, CString str);
	void hollow_char0(CDC* pDC, int x, int y,int font,int color, CString str,int xd,int yd);
	void char1(CDC* pDC, int x, int y, int dc, int fc, int font, int size, CString str);
	void char2(CDC* pDC, int x, int y, int dc,int bc, int fc, int font, int size, CString str);
	void char3(CDC* pDC, int x, int y, int sc, int bc, int fc, int font, int size, CString str);
	void char4(CDC* pDC, int x, int y, int sc, int bc, int fc, int font, int size, CString str);
	void char5(CDC* pDC, int x, int y, int sc, int bc, int fc, int font, int size, CString str);
	void c_bar3d(CDC* pDC, int x1, int y1, int x2, int y2, int d, int c, int ct, int cs);
	void s_bar(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void h_char(CDC* pDC, int x, int y, int c, CString str);
	void c_line(CDC* pDC, int data[], int c);
	void change_palette_g1(CDC* pDC);
	void s_bar_example75(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void h_char_example75(CDC* pDC, int x, int y, int c, CString str);
	void c_line_example75(CDC* pDC, int data[], int num, int c);
	void relief_char(CDC* pDC, int x, int y, int sc, int bc, int fc, int font, int dire, int size, CString str);
	void relief_line(CDC* pDC, int x0, int y0, int x1, int y1, int sc, int bc, int fc);
	void s_bar_example76(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void mac_frame2(CDC* pDC, int x, int y, int x_d, int y_d, int d, int fc);
	void bold_line(CDC* pDC, float data[], int num, int c);
	void change_palette_r(CDC* pDC);
	void s_bar_example77(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void g_bar1(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void c_bar1(CDC* pDC, int data[], int num, int full_scale);
	void h_char1(CDC* pDC, int x, int y, int c, CString str);
	void s_bar_example78(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void g_bar1_example78(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void h_char1_example78(CDC* pDC, int x, int y, int c, CString str);
	void cframe_example78(CDC* pDC, int x, int y, int x_d, int y_d, int d, int bc, int fc, int sc);
	void s_bar_example79(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void h_jchar(CDC* pDC, int x, int y, int c, CString str);
	void cframe_example79(CDC* pDC, int x, int y, int x_d, int y_d, int d, int bc, int fc, int sc);
	void change_palette_g_example80(CDC* pDC);
	void s_bar_example80(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void h_char_example80(CDC* pDC, int x, int y, int c, CString str);
	void change_palette_b2(CDC* pDC);
	void s_bar_example81(CDC* pDC, int x1, int y1, int x2, int y2, int c);
	void h_char2(CDC* pDC, int x, int y, int c, CString str);
	void fc_circle(CDC* pDC, int x0, int y0, int r, int c);
	void relief_char_example81(CDC* pDC, int x, int y, int sc, int bc, int fc, int font,
		int dire, int size, CString str);
	void radar1(CDC* pDC, int n, int x0, int y0, int r, int c, char *s[]);
	void radar_data(CDC* pDC, int n, int x0, int y0, int c, int d[]);
	void rotate3d(CDC* pDC,double xr, double yr, double zr,
		double* px, double* py, double* pz);
	void gwindow_example82(CDC* pDC, int x1, int y1, int x2, int y2, int color, CString str);
	double sync(double x, double y);
	void graph(CDC* pDC, double y, double z, int* plotted);
	void star2_example89(CDC* pDC, int x0, int y0, int r, double a, int c);
	void getimage(CDC* pDC, int left, int top, int right, int bottom, void* bitmap);
	void putimage(CDC* pDC, int left, int top, void* bitmap, int op);


	int getmaxx();
	int getmaxy();
	void delay(int msec);
	void initialized_arccoordstype(struct arccoordstype* arcc);
	void getarccoords(struct arccoordstype* arcc);
	void setarccoords(int x1, int y1, int x2,int y2);
	void setarccoords(int x, int y, int radius);
	void setarccoords(int x, int y, int startAngle,int endAngle,int xradius,int yradius);
	void textcolor(CDC* pDC, int color);
	void setwritemode(CDC* pDC, int mode);
	
	//Country
	void vietnam(CDC* pDC);
	void cuba(CDC* pDC);
	void iraq(CDC* pDC);
	void chile(CDC* pDC);
	void panama(CDC* pDC);
	void china(CDC* pDC);
	void yugo(CDC* pDC);
	void turkey(CDC* pDC);
	void usa(CDC* pDC);

	PENDATA penData;
	FILL_PATTERN fill_PatternData;
	BKDATA bkData;
	FONT_DATA fontData;
	USE_PenFillFont usePFF;
	struct arccoordstype main_arccoordstyle;

public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGraphicMFCKDYView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC,int color);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor, int color);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};

#ifndef _DEBUG  // debug version in GraphicMFC_KDYView.cpp
inline CGraphicMFCKDYDoc* CGraphicMFCKDYView::GetDocument() const
   { return reinterpret_cast<CGraphicMFCKDYDoc*>(m_pDocument); }
#endif

