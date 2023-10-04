
// GraphicMFC_KDYView.cpp : implementation of the CGraphicMFCKDYView class
//


#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GraphicMFC_KDY.h"
#endif

#include "GraphicMFC_KDYDoc.h"
#include "GraphicMFC_KDYView.h"

#include <math.h>
#include <list>

#include <random>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double getRadian(int num);
int changeBookColorToMFCColor(int colorNum);
int changeBookPatternToMFCPattern(int pattern);
int brush_changeBookColorToMFCColor(int colorNum);
int changeMFCColorToBookColor(COLORREF colorNum);
int textwidth(char s[]);
// BOOL return_checkFillStyle(int i, int j, int pattern, int maxCount);
int gettingCharSize(LONG height, LONG width);
int getFont_number_of_name(CDC* pDC, WCHAR* lfFaceName);
int textwidth_example49(CString str);
int textheight(CString str);
int imagesize(int left, int top, int right, int bottom);
// CGraphicMFCKDYView

IMPLEMENT_DYNCREATE(CGraphicMFCKDYView, CView)

BEGIN_MESSAGE_MAP(CGraphicMFCKDYView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CGraphicMFCKDYView construction/destruction

CGraphicMFCKDYView::CGraphicMFCKDYView() noexcept
{
	// TODO: add construction code here

}

CGraphicMFCKDYView::~CGraphicMFCKDYView()
{
}

BOOL CGraphicMFCKDYView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGraphicMFCKDYView drawing

void CGraphicMFCKDYView::OnDraw(CDC* pDC)
{
	CGraphicMFCKDYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	RECT rect;
	::GetClientRect(this->m_hWnd, &rect);
	CMemDC memDc(*pDC,this);
	
	CDC& dc = memDc.GetDC();
	dc.FillSolidRect(&rect,RGB(255,255,255));
	initialized_usePFF();
	initialized_arccoordstype(&main_arccoordstyle);
	example01(&dc);
}

// 폰트 데이터를 얻어오는 임시 구조
typedef struct _FontCount {
	std::list<LOGFONT> raster, truetype, unknown;
} FontCount;

void CGraphicMFCKDYView::example01(CDC* pDC) {
	circle(pDC,300, 150, 80);
}

void CGraphicMFCKDYView::example02(CDC* pDC) {
	// 현재 책에 나오는 예제를 구현하기 어려움이 따름
	// 2022.09.14
//		pDC->SetViewportOrg(300, 300);
	pDC->SetWindowExt(100, 100);
	pDC->SetViewportExt(300, 300);
	circle(pDC, 100, 50, 80);
}

void CGraphicMFCKDYView::example03(CDC* pDC) {
	putpixel(pDC, 320, 200, GREEN);
}

void CGraphicMFCKDYView::example04(CDC* pDC) {
	line(pDC,50, 50, 150, 150);
	rectangle(pDC, 180, 50, 320, 150);
	circle(pDC, 400, 100, 50);
	arcCircle_book(pDC,550,100,45,235,50);
	ellipse(pDC, 100, 300, 0, 360, 80, 50);
	ellipse(pDC, 300, 300, 30, 250, 80, 50);

	int points[] = { 580,220,450,350,550,300,580,220 };
	drawPloy(pDC, 4, points);

}

void CGraphicMFCKDYView::example05(CDC* pDC)
{
	setcolor(pDC, BLACK);
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC,50, 50, 100, 150);
	bar3d(pDC, 200, 50, 250, 150, 20, 1);
	sector(pDC, 400, 100, 0, 360, 50, 50);
	pieslice(pDC, 550, 100, 30, 80, 50);
	fillellipse(pDC, 100, 300, 80, 50);
	sector(pDC, 300, 300, 30, 250, 80, 50);
	int points[] = { 580,220,450,350,550,300,580,220 };
	fillPoly(pDC, 4, points);
}

void CGraphicMFCKDYView::example06(CDC* pDC)
{
	setcolor(pDC, MAGENTA);
	settextstyle(pDC, 9, HORIZ_DIR, 5);
	outtextxy(pDC, 0, 110, L"Turbo C++");
	outtextxy(pDC, 80, 220, L"Graphics");
}

void CGraphicMFCKDYView::example07(CDC* pDC)
{
	CString str = L"Turbo C++ Graphics";
	for (int i = 1; i <= 6; i++) {
		setcolor(pDC,i);
		settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, (i-1));	//fontsize i -> (i-1)로 대체
		outtextxy(pDC, 0, i * i * 10, str);
	}
}

void CGraphicMFCKDYView::example08(CDC* pDC)
{
	CString str[] = { L"DEFAULT font",L"TRIPLEX font",L"SMALL font",L"SANS SERIF font",
		L"GOTHIC font",L"SCRIPT font",L"SIMPLEX font",L"TRIPLEX SCRIPT font",L"COMPLEX font",
		L"EUROPEAN font",L"BOLD font" };

	int style, y, size = 4;
	int count = _countof(str);

	//변경
	for (style = 0, y = 0; style <= count-1; style++, y += 40) {
		settextstyle(pDC, style, HORIZ_DIR, size-3);	//font_size size -> size-3으로 대체
		outtextxy(pDC, 0, y, str[style]);
	}
}

void CGraphicMFCKDYView::example09(CDC* pDC)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10000; i++) {
		putpixel(pDC, rand()%639, rand()%479, (rand()%14)+1);
	}
}

void CGraphicMFCKDYView::example10(CDC* pDC)
{
	for (int i = 1; i < 7; i++) 
		for(int j = 40;j<=600;j++)
			putpixel(pDC, j,50*i-25,i);

	for (int i = 1; i < 7; i++)
		for (int j = 40; j <= 600; j+=3)
			putpixel(pDC, j, 50 * i, i);
}

void CGraphicMFCKDYView::example11(CDC* pDC)
{
	for (int i = 100; i <= 300; i += 3)
		for (int j = 0; j <= 639; j++)
			putpixel(pDC, j,
				i + (int)(50 * cos((j + 50 * sin(i * PI / 90.0)) * PI / 90.0)),
				GREEN);
}

void CGraphicMFCKDYView::example12(CDC* pDC)
{
	static int ratio[9][2] = {
		{1,1},{1,2},{1,3},{2,3},{2,5},{3,4},{3,5},{4,5},{5,6}
	};

	int x0, y0;
	int color = 0;
	//randomize(); // 대체
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 5; j++) {
			x0 = i * 70 + 35;
			y0 = j * 70 + 35;
			color = rand() % 16;
			lissajous(pDC,x0,y0,ratio[i][0],ratio[i][1],33,45*j,changeBookColorToMFCColor(rand()%16));
		}
}

void CGraphicMFCKDYView::example13(CDC* pDC)
{
	double j;
	for (j = 0.0; j <= 2 * PI; j += PI / 180.0)
		putpixel(pDC, 320 + (int)(100 * cos(j)), 200 - (int)(100 * sin(j)),RED );	//color, WHITE -> RED로 대체
}

void CGraphicMFCKDYView::example14(CDC* pDC)
{
	for (int i = 100; i <= 300; i += 5)
		my_circle(pDC, 320, i, i / 5);
}

void CGraphicMFCKDYView::example15(CDC* pDC)
{
	for (int c = 1; c <= 7; c++)
		for (int i = 50; i <= 600; i += 30)
			my_circle_c(pDC,i, 60 + c * 30, 20, c);
}

void CGraphicMFCKDYView::example16(CDC* pDC)
{
	for (int i = 50; i <= 250; i++)
		my_arc(pDC,320,300,i,i%16,45,135);
}

void CGraphicMFCKDYView::example17(CDC* pDC)
{
	int z = 0,x0 = 0,y0 = 0;
	for(int i=-100;i<=100;i+=2)
		for (int j = -100; j <= 100; j += 2) {
			z = i * i + j * j;
			x0 = 40000 * i / (z + 10000);
			y0 = 40000 * j / (z + 10000);
			putpixel(pDC, x0 + 320, y0 + 200, RED); //color -> WHITE -> RED로 대체
		}
}

void CGraphicMFCKDYView::example18(CDC* pDC)
{
	double x, y, z, x0, y0;

	for(x=-2.0;x<=2.0;x+=0.05)
		for (y = -2.0; y <= 2.0; y += 0.05) {
			z = exp(-x * x + y * y);
			x0 = 100 * x / (z + 1);
			y0 = 100 * y / (z + 1);
			putpixel(pDC, (int)x0 + 320, (int)y0 + 200, RED); //color -> WHITE -> RED로 대체
		}
}

void CGraphicMFCKDYView::example19(CDC* pDC)
{
	int i = 0;
	for (int color = 1; color <= 5; color++) {
		setcolor(pDC, color);
		if (color >= 4)
			i = 100;
		circle(pDC, color * 160 - i * 4, 150 + i, 100);
	}
}

void CGraphicMFCKDYView::example20(CDC* pDC)	//팔레트 좀더 알아봐야함
{
	//현재 setbkcolor 동작 안함 => CDC의 setbkcolor은 추후 textout()함수 사용 시 문자 공간의 문자 이외의 여백의 색상을 설정한다.
	int bkColor = 0;
	circle(pDC, 320, 200, 150);
	/*
	for (bkColor = 1; bkColor <= 7; bkColor++) {
		setbkcolor(pDC,bkColor);
	}
	setbkcolor(pDC,0);
	*/
	setbkcolor(pDC, RED);
}

void CGraphicMFCKDYView::example21(CDC* pDC)	//팔레트 좀더 알아봐야함
{
	//현재 setpallette 동작 안함
	int color;
	for (color = 1; color <= 14; color++) {
		setcolor(pDC,color);
		circle(pDC,320, 200, color * 12);
	}

	for (color = 1; color <= 14; color++) {
		setpallette(pDC, color, WHITE);
	}
}

void CGraphicMFCKDYView::example22(CDC* pDC)
{
	int x, y, x0 = 320, y0 = 200, r = 200;
	double i;

	setcolor(pDC,LIGHTRED);
	for (i = 0.0; i < 2 * PI; i += PI / 180.0) {
		x = x0 + (r * cos(i));
		y = y0 - (r * sin(i));
		line(pDC,x0, y0, x, y);
	}
}

void CGraphicMFCKDYView::example23(CDC* pDC)
{
	double s = PI / 36.0;
	setcolor(pDC, BLACK);	//color, WHITE to BLACK으로 대체
	outtextxy(pDC, 200, 20, L"** Rectifier Characteristics **");
	frame(pDC,CYAN);
	setcolor(pDC, BROWN);

	/* 교류 파형 */
	outtextxy(pDC, 0, 90, L"AC Input");
	for (int i = 70; i <= 570; i++) {
		if (i == 70)
			pDC->MoveTo(70, 100 - (int)(45 * cos(s * i)));
		else
			lineto(pDC, i, 100 - (int)(45 * cos(s * i)));
	}

	/* 전파정류 파형 */
	setcolor(pDC, MAGENTA);
	outtextxy(pDC, 0, 190, L"Fullwave");
	for (int i = 70; i <= 570; i++) {
		if (i == 70)
			pDC->MoveTo(70, 200 - (int)fabs(45 * cos(s * i)));
		else
			lineto(pDC, i, 200 - (int)fabs(45 * cos(s * i)));
	}

	/* 반파정류 파형*/
	setcolor(pDC, RED);
	outtextxy(pDC, 0, 290, L"Halfwave");
	for (int i = 70; i <= 570; i++) {
		if (i == 70)
			pDC->MoveTo(70, 300 - (int)fabs(45 * cos(s * i)));
		else if (cos(s * i) > 0)
			lineto(pDC, i, 300 - (int)(45 * cos(s * i)));
		else
			lineto(pDC, i, 300);
	}
}

void CGraphicMFCKDYView::example24(CDC* pDC)
{
	int style;
	setcolor(pDC,GREEN);

	outtextxy(pDC,120, 20, L"Normal Width");
	for (style = 0; style <= 3; style++) {
		setlinestyle(pDC, style, 0, NORM_WIDTH);
		line(pDC, style * 60+80, 50, style * 60 + 80, 460);
	}
	setcolor(pDC, CYAN);
	outtextxy(pDC, 420, 20, L"Thick Width");
	outtextxy(pDC, 421, 20, L"Thick Width");
	outtextxy(pDC, 422, 20, L"Thick Width");
	for (style = 0; style <= 3; style++) {
		setlinestyle(pDC, style, 0, THICK_WIDTH);
		line(pDC, style * 60 + 380, 50, style * 60 + 380, 460);
	}
}

void CGraphicMFCKDYView::example25(CDC* pDC)
{
	settextstyle(pDC, 9, HORIZ_DIR, 3); //TRIPLEX_FONT -> 맑은 고딕으로 치환
	outtextxy(pDC, 140, 0, L"User Defined Line Sytle");
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	settextjustify(pDC, LEFT_TEXT,CENTER_TEXT);
	unsigned m;
	m = 0x1111;	lineout(pDC, 60, m, L"1111 = 0001000100010001");
	m = 0x1717;	lineout(pDC, 100, m, L"1717 = 0001011100010111");
	m = 0x3333;	lineout(pDC, 140, m, L"3333 = 0011001100110011");
	m = 0x3d3d;	lineout(pDC, 180, m, L"3D3D = 0011110100111101");
	m = 0x4e4e;	lineout(pDC, 220, m, L"4E4E = 0100111001001110");
	m = 0xbebe;	lineout(pDC, 260, m, L"BEBE = 1011111010111110");
	m = 0xeeee;	lineout(pDC, 300, m, L"EEEE = 1110111011101110");
	m = 0xf0f0;	lineout(pDC, 340, m, L"F0F0 = 1111000011110000");
	m = 0xfa05;	lineout(pDC, 380, m, L"FA05 = 1111101000000101");
	m = 0xfafa;	lineout(pDC, 420, m, L"FAFA = 1111101011111010");
	m = 0xffff;	lineout(pDC, 460, m, L"FFFF = 1111111111111111");
}

void CGraphicMFCKDYView::example26(CDC* pDC)
{
	int i, r, x, y, d;
	double alpha = PI / 180.0;
	for (i = 100; i < 2200; i += 15) {
		r = 5 * exp(0.1 * i * alpha);
		d = r / 10;
		x = 320 + r * cos(i * alpha);
		y = 240 + r * sin(i * alpha);
		rectangle(pDC, x - d, y - d, x + d, y + d);
	}
}

void CGraphicMFCKDYView::example27(CDC* pDC)
{
	int x0=320,y0=240, r=150, x, y;
	int triangle[] = { 320,240,0,0,0,0,320,240 };
	double theta, twopi = 2 * PI, alpha = PI / 30.0;
	setcolor(pDC, BLUE);
	for (theta = 0; theta <= twopi; theta+=alpha) {
		x = x0 + r * cos(theta);
		y = y0 + r * sin(theta);
		triangle[2] = x;
		triangle[3] = y;
		triangle[4] = x;
		triangle[5] = y + 10;
		drawPloy(pDC, sizeof(triangle) / (2 * sizeof(int)), triangle);
	}
}

void CGraphicMFCKDYView::example28(CDC* pDC)
{
	int color, a = 3;
	my_text(pDC);
	for (color = 1; color <= 7; color++)
		round_rec(pDC,(180 + a * color),
			90 + a * color,
			280 - 2 * a * color,
			200 - 2 * a * color,
			30,
			color);
}

void CGraphicMFCKDYView::example29(CDC* pDC)
{

	int x = 0, y, r, i, k = 19;
	for (i = 1, r = 0; i <= k; i++) {
		setcolor(pDC, GREEN);
		r += i;
		y = 390 - r;
		my_circle(pDC, 320, y, r);
	}
	for (i = 1, r = 0; i <= k; i++) {
		setcolor(pDC, BLUE);
		r += i;
		y = 10 + r;
		my_circle(pDC, 320, y, r);
	}
	for (i = 1, r = 0; i <= k; i++) {
		setcolor(pDC, CYAN);
		r += i;
		x = 130 + r;
		my_circle(pDC, x, 200, r);
	}
	for (i = 1, r = 0; i <= k; i++) {
		setcolor(pDC, RED);
		r += i;
		x = 510 - r;
		my_circle(pDC, x, 200, r);
	}
}

void CGraphicMFCKDYView::example30(CDC* pDC)
{

	int x,y,h;
	for (h = 5; h < 12; h++) {
		setcolor(pDC,h - 4);
		ellipse(pDC, 320, 200, 0, 360, 200, 10 * h);
	}

	for(x=100;x<=540;x+=440)
		for(y=70;y<=330;y+=260)
			for (h = 5; h < 12; h++) {
				setcolor(pDC,h - 4);
				ellipse(pDC, x, y, 0, 360, 80, 5 * h);
			}

	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 4);
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	outtextxy(pDC, 320, 200, L"Graphics");
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 3);
	outtextxy(pDC, 100, 70, L"Turbo C");
	outtextxy(pDC, 540, 70, L"Borland C");
	outtextxy(pDC, 100, 330, L"Lattice C");
	outtextxy(pDC, 540, 330, L"MS-C");
}

void CGraphicMFCKDYView::example31(CDC* pDC)
{
	int repeat = 5000, m = 0, t = 0;
//	long now;
	double x, y;
	frame(pDC);
	srand((unsigned int)time(NULL));
	do {
		x = 2.0 * rand() / RAND_MAX;
		y = 2.0 * rand() / RAND_MAX;
		if (((x - 1) * (x - 1) + (y - 1) * (y - 1)) > 1.0)
			putpixel(pDC, (int)(x * 100 + 200), (int)(y * 100 + 100), RED);
		else {
			m++;
			putpixel(pDC, (int)(x * 100 + 200), (int)(y * 100 + 100), WHITE);
		}
		t++;
	} while (t < repeat);
	int posX=25, posY=25;
	pDC->MoveTo(posX,posY);
	CString str = L"";

	//책과 비슷하게 맞춰주기 위해 추가
	setcolor(pDC, BLACK);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	//추가 끝

	str.Format(L"Total count = %d", t);
	outtextxy(pDC, posX+280, posY+350, str);
	str.Format(L"Count in circle = %d", m);
	outtextxy(pDC, posX+280, posY+370, str);
	str.Format(L"The value of pi = %7.5f", (4.0 * m / t));
	outtextxy(pDC, posX+280, posY+390, str);
}

void CGraphicMFCKDYView::example32(CDC* pDC)
{

	const double RADIUS = 170.0;
	const double STEP = (PI / 80.0);
	const double DEGREE = (PI / 3.0 * 2.0);

	int x1, y1, x2, y2;
	double i, pi = PI;

	for (i = 0; i < 2.0 * pi; i += STEP) {
		x1 = (int)(RADIUS * cos(i)) + 320;
		y1 = (int)(RADIUS * sin(i)) + 240;
		x2 = (int)(RADIUS * cos(i+DEGREE)) + 320;
		y2 = (int)(RADIUS * sin(i+DEGREE)) + 240;
		line(pDC,x1, y1, x2, y2);
	}
}

void CGraphicMFCKDYView::example33(CDC* pDC)
{
	int n = 40, x, y, xmax, ymax, xn, yn;
	xmax = getmaxx();
	ymax = getmaxy();
	xn = (xmax + 1) / n;
	yn = (ymax + 1) / n;
	setcolor(pDC, BLUE);
	for (x = 0, y = 0; x <= xmax; x += xn, y += yn)
		line(pDC,xmax - x, 0, x, y);

	setcolor(pDC, GREEN);
	for (x = xmax, y = ymax; x >= 0; x -= xn, y -= yn)
		line(pDC,xmax - x, ymax, x, y);
	setcolor(pDC, RED);
	line(pDC, 0, 0, xmax, ymax);
}

void CGraphicMFCKDYView::example34(CDC* pDC)
{
	const double RADIUS = 170.0;
	int x, y, x0, y0;
	double angle = 0.;

	setcolor(pDC,RED);
	x0 = getmaxx()/2;
	y0 = getmaxy() / 2 - 170;
	y = y0 + 40;
	pDC->MoveTo(x0, y0);
	for (; angle <= 6. * PI; angle += PI / 25., y += 2, y0 += 2) {
		x = (int)(RADIUS * cos(angle)) + x0;
		pDC->LineTo(x, y);
		line(pDC, x0, y0, x, y);
	}
}

void CGraphicMFCKDYView::example35(CDC* pDC)
{
	//예재 37의 그림이 나타난다.
	const int RRR = 120;
	const int RR = 60;
	const int R = 40;

	int cen_x, cen_y, i, j;
	double x0, y0, xx0, yy0, step = PI / 180.;
	cen_x = getmaxx() / 2;
	cen_y = getmaxy() / 2;

	for (i = 0; i < 360; i += 60) {
		x0 = RRR * cos(i * step) + cen_x;
		y0 = RRR * sin(i * step) + cen_y;
		for (j = i + 252; j >= i; j -= 18) {
			xx0 = RR * cos(j * step) + x0;
			yy0 = RR * sin(j * step) + y0;
			my_circle(pDC, xx0, yy0, R);
		}
	}
}

void CGraphicMFCKDYView::example36(CDC* pDC)
{
	const int RADIUS = 100;
	
	int i, j, k, cen_x, cen_y, radius, x0, y0;
	double r, alpha = PI / 8.0, twopi = 2.0 * PI;
	for(j=0,k=1;j<=1;j++)
		for (i = 0; i <= 2; i++, k++) {
			radius = 12 * k;
			cen_x = 100 + i * 210;
			cen_y = 100 + j * 240;
			for (r = 0.; r < twopi; r += alpha) {
				setcolor(pDC, BLACK);
				x0 = (int)((double)radius * cos(r)) + cen_x;
				y0 = (int)((double)radius * sin(r)) + cen_y;
				my_circle(pDC, x0, y0, RADIUS - radius);
			}
			delay(1);
		}
}

void CGraphicMFCKDYView::example37(CDC* pDC)
{
	//예재 35의 그림이 그려짐
	const double RADIUS = 170.;
	const double VERTEX = 18.;

	int i, j, x1, y1, x2, y2;
	double twopi = 2 * PI;
//	randomize();
	for (i = 0; i < (int)VERTEX - 1; i++) {
		x1 = (int)(RADIUS * cos(i * twopi / VERTEX)) + 320;
		y1 = (int)(RADIUS * sin(i * twopi / VERTEX)) + 240;
		for (j = i + 1; j < VERTEX; j++) {
			x2 = (int)(RADIUS * cos(j * twopi / VERTEX)) + 320;
			y2 = (int)(RADIUS * sin(j * twopi / VERTEX)) + 240;
			line(pDC, x1, y1, x2, y2);
		}
	}
}

void CGraphicMFCKDYView::example38(CDC* pDC)
{
	int i, j, x = 0, y = 0;
	for (j = 0; j < 48; j++) {
		for (i = 0; i < 64; i++) {
			bar(pDC, x, y, x + 5, y + 5);
			x += 10;
		}
		x = 0; y += 10;
	}
	title(pDC);
}

void CGraphicMFCKDYView::example39(CDC* pDC)
{
	rectangle(pDC, 0, 0, 639, 479); /* 바탕화면 */
	fillstyledemo(pDC);
//	clearDevice(pDC);

//	pDC->Rectangle(0, 0, 639, 479);
//	rectangle(pDC, 0, 0, 639, 479);
//	colordemo(pDC);
}

//gwindow() 내부의 setfillpattern 구현에 있어 어려움이 따름
void CGraphicMFCKDYView::example40(CDC* pDC) 
{
	char *str[] = { "MY WINDOW SYSTEM","EDITOR","GRAPHICS","FILE" };
//	setfillstyle(pDC, INTERLEAVE_FILL, LIGHTGRAY);
	setfillstyle(pDC, LINE_FILL, LIGHTGRAY); //INTERLEAVE_FILL -> LINE_FILL로 변경
	bar(pDC, 0, 0, 639, 479);
	gwindow(pDC, 40, 40, 600, 360, WHITE, str[0]);
	gwindow(pDC, 60, 70, 400, 200, YELLOW, str[1]);
	gwindow(pDC, 300, 150, 630, 300, GREEN, str[2]);
	gwindow(pDC, 50, 250, 450, 380, LIGHTGRAY, str[3]);
} 

void CGraphicMFCKDYView::example41(CDC* pDC)
{
	char title[] = "FLOODFILL";
	setfillstyle(pDC, SLASH_FILL, LIGHTGRAY);	//INTERLEAVE_FILL -> SLASH_FILL로 대체
	bar(pDC, 0, 0, 639, 479);
	gwindow(pDC, 100, 80, 540, 320, WHITE, title);
	setcolor(pDC, CYAN);
	setfillstyle(pDC, SLASH_FILL, CYAN); //현재 하단의 circle에서의 setfillstyle을 적용 시키기 위해서는 gwindow() 함수 내부의 setfillstyle 적용이 적용되므로 다시 setfillstyle을 해주어야 한다.
	circle(pDC, 420, 210, 70);	
	rectangle(pDC, 150, 140, 290, 280);
	setfillstyle(pDC, 2, 2);
	pDC->FloodFill(420, 210, changeBookColorToMFCColor(CYAN));
	setfillstyle(pDC,7, 3);
	pDC->FloodFill(220, 210, changeBookColorToMFCColor(CYAN));
}

void CGraphicMFCKDYView::example42(CDC* pDC)
{
	int i, a[] = { 50,80,170,140,50 };
	char title[] = "WORLD POPULATION GROWTH";
	setfillstyle(pDC, WIDE_DOT_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);

	gwindow(pDC,100, 80, 540, 320, WHITE, title);
	setcolor(pDC, MAGENTA);
	for (i = 1; i <= 5; i++) {
		setfillstyle(pDC, i, i);
		bar3d(pDC, 100 + 70 * i, 300 - a[i - 1], 70 * i + 140, 300, 10, 1);
	}
	setcolor(pDC, WHITE);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	line(pDC, 150, 300, 520, 300);
	line(pDC, 150, 300, 150, 120);
}

void CGraphicMFCKDYView::example43(CDC* pDC)
{
	int i, j,color;
	char title[] = "CALENDAR",a[2];
	char year_month[] = "1994 May";
	CString str = L"";
	setfillstyle(pDC, WIDE_DOT_FILL, CYAN); //INTERLEAVE_FILL -> WIDE_DOT_FILL로 대체
	bar(pDC, 0, 0, 639, 479);

	
	gwindow(pDC, 100, 40, 540, 320, WHITE, title);
	cframe(pDC,145,69,349,40,3,WHITE,GREEN+8,GREEN);
	
	for (i = 1; i <= 7; i++) {
		for (j = 1; j <= 5; j++) {
			if (((j - 1) * 7 + 1) >= 32)break;
			if (i == 1)
				color = RED;
			else
				color = CYAN;
			cframe(pDC, 145 + (i - 1) * 50, 111 + (j - 1) * 30, 49, 29, 3, WHITE, color + 8, color);
		}
	}
	
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	
	setcolor(pDC, RED);
	settextstyle(pDC, 9, HORIZ_DIR, 1);	//GOTHICK_FONT -> 9로 대체
	
	str = CString(year_month);
	outtextxy(pDC, 320, 75, str);	//y, 85 -> 75
	setcolor(pDC, BLACK);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	for(j=1;j<=5;j++)
		for (i = 1; i <= 7; i++) {
			if (((j - 1) * 7 + i) >= 32) break;
//			_itoa((j - 1) * 7 + i, a, 10);
			str.Format(L"%d", (j - 1) * 7 + i);
			outtextxy(pDC, 170 + (i - 1) * 50, 110 + (j - 1) * 30, str);
		}
	special_day(pDC, 5, BLUE);
	special_day(pDC, 18, BLUE);
	
}

void CGraphicMFCKDYView::example44(CDC* pDC)
{
	int x0 = 320, y0 = 200, r = 150, s_angle = 120, e_angle = 200;
	setlinestyle(pDC, DOTTED_LINE, 0, NORM_WIDTH);
	setfillstyle(pDC, SLASH_FILL, RED);
	setcolor(pDC,CYAN);
	rectangle(pDC, x0 - r, y0 - r, x0 + r, y0 + r);
	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	setcolor(pDC, GREEN);
	circle(pDC, x0, y0, r);
	setcolor(pDC, YELLOW);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	pieslice(pDC, x0, y0, s_angle, e_angle, r);
}

void CGraphicMFCKDYView::example45(CDC* pDC)
{
	figure(pDC);
	title_example45(pDC);
}

void CGraphicMFCKDYView::example46(CDC* pDC)
{
	int x0 = 320, y0 = 200, xr = 250, yr = 150, s_angle = 120, e_angle = 200;
	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	setcolor(pDC, RED);
	ellipse(pDC, x0, y0, 0, 360, xr, yr);	//eclipse가 아래 rectangle에 의해 덮어 씌어진다. 이게 맞는지?


	setlinestyle(pDC, DASHED_LINE, 0, THICK_WIDTH);
	setcolor(pDC,MAGENTA);
	rectangle(pDC, x0 - xr, y0 - yr, x0 + xr, y0 + yr);
	setcolor(pDC, CYAN);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	setfillstyle(pDC, SOLID_FILL, LIGHTBLUE);
	fillellipse(pDC, x0, y0, xr, yr);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	setfillstyle(pDC, HATCH_FILL, GREEN);
	sector(pDC, x0, y0, s_angle, e_angle, xr, yr);
}

void CGraphicMFCKDYView::example47(CDC* pDC)
{
	star1(pDC, 160, 200, 150, 0, MAGENTA);
	star2(pDC, 480, 200, 150, 0, RED);
}

void CGraphicMFCKDYView::example48(CDC* pDC)
{
	int color = 1, radius, xp;
	char* title[] = { "Star Graphics I","Star Graphics II", "Star Graphics III", "Star Graphics IV" };
	double angle;
	setfillstyle(pDC, SOLID_FILL, LIGHTGRAY);	//INTERLEAVE_FILL -> SOLID_FILL로 대체
	bar(pDC, 0, 0, 639, 479);
	
	gwindow_example48(pDC, 20, 20, 300, 300, WHITE, title[0]);
	for (angle = 0.0; angle <= 5 * PI / 10; angle += PI / 10)
		star2_example48(pDC, 320 / 2, 320 / 2,
			100 - (int)(15 * angle), angle, ++color);
	color = 0;
	
	gwindow_example48(pDC, 270, 50, 550, 330, WHITE, title[1]);
	for (angle = 0.0; angle <= 5 * PI / 10; angle += PI / 50)
		star2_example48(pDC, (270 + 550) / 2, (50 + 330) / 2,
			100, angle, (++color) % 16);

	color = 0;
	
	gwindow_example48(pDC, 90, 305, 290, 440, WHITE, title[2]);
	for (radius = 0; radius <= 60; radius += 4)
		star2_example48(pDC, (90 + 290) / 2, (305 + 440) / 2 + 15, 60 - radius, 0, ++color);
	
	color = 0;
	gwindow_example48(pDC, 302, 350, 628, 430, WHITE, title[3]);
	for (xp = 0; xp < 300; xp += 20)
		star2_example48(pDC,330 + xp, (350 + 430) / 2 + 15, 20 - xp / 20, 0, ++color);

}

void CGraphicMFCKDYView::example49(CDC* pDC)
{
	char c = '1';
	char title[][30] = { "FLAG","View Nam","Cuba","Iraq","Chile","Panama","China",
					"Yugoslavia","Turkey","USA"};
	CString str = L"";
	setfillstyle(pDC, SOLID_FILL, LIGHTGRAY); //INTERLEAVE_FILL -> SOLID_FILL로 대체
	bar(pDC, 0, 0, 639, 479);
	setcolor(pDC, MAGENTA);
	outtextxy(pDC, 0, 50, L"Flags in the world!");
	outtextxy(pDC, 0, 80, L"[1] Viet Nam");
	outtextxy(pDC, 0, 100, L"[2] Cuba");
	outtextxy(pDC, 0, 120, L"[3] Iraq");
	outtextxy(pDC, 0, 140, L"[4] Chile");
	outtextxy(pDC, 0, 160, L"[5] Panama");
	outtextxy(pDC, 0, 180, L"[6] China");
	outtextxy(pDC, 0, 200, L"[7] Yugoslavia");
	outtextxy(pDC, 0, 220, L"[8] Turkey");
	outtextxy(pDC, 0, 240, L"[9] USA");
	outtextxy(pDC, 0, 260, L"others to exit");
	outtextxy(pDC, 0, 300, L"Press any key!");

MAIN: switch (c) {
case '1':
	gwindow(pDC,150, 65, 490, 320, WHITE, title[1]);
	vietnam(pDC);
	break;
case '2':
	gwindow(pDC, 150, 65, 490, 320, WHITE, title[2]);
	cuba(pDC);
	break;
case '3':
	gwindow(pDC, 150, 65, 490, 320, WHITE, title[3]);
	iraq(pDC);
	break;
case '4':
	gwindow(pDC, 150, 65, 490, 320, WHITE, title[4]);
	chile(pDC);
	break;
case '5':
	gwindow(pDC, 150, 65, 490, 320, WHITE, title[5]);
	panama(pDC);
	break;
case '6':
	gwindow(pDC, 150, 65, 490, 320, WHITE, title[6]);
	china(pDC);
	break;
case '7':
	gwindow(pDC, 150, 65, 490, 320, WHITE, title[7]);
	yugo(pDC);
	break;
case '8':
	gwindow(pDC, 150, 65, 490, 320, WHITE, title[8]);
	turkey(pDC);
	break;
case '9':
	gwindow(pDC, 150, 65, 490, 320, WHITE, title[9]);
	usa(pDC);
	break;
	}

}

void CGraphicMFCKDYView::example50(CDC* pDC)
{
	CString str = L"";
	struct textsetting text;
	
	gettextsetting(pDC,&text);
	str.Format(L"font = %d", text.font);
	outtextxy(pDC, 50, 50, str);
	str.Format(L"direction = %d", text.direction);
	outtextxy(pDC, 50, 150, str);
	str.Format(L"charsize = %d", text.charsize);
	outtextxy(pDC, 50, 200, str);
	str.Format(L"Horiz = %d", text.horiz);
	outtextxy(pDC, 50, 250, str);
	str.Format(L"Vert = %d", text.vert);
	outtextxy(pDC, 50, 300, str);
}

void CGraphicMFCKDYView::example51(CDC* pDC)
{
	CString str = L"";
	struct textsetting text;

	gettextsetting(pDC, &text);
	settextstyle(pDC, 9, VERT_DIR, 0);	//GOTHIC_FONT -> 9로 대체
	gettextsetting(pDC, &text);
	str.Format(L"font = %d", text.font);
	outtextxy(pDC, 50, 150, str);
	str.Format(L"direction = %d", text.direction);
	outtextxy(pDC, 50, 250, str);
	str.Format(L"charsize = %d", text.charsize);
	outtextxy(pDC, 50, 350, str);
}

void CGraphicMFCKDYView::example52(CDC* pDC)
{
	CString str = L"";
	struct textsetting text,newtext;

	gettextsetting(pDC, &text);
	settextstyle(pDC, 9, HORIZ_DIR, 0);	//GOTHIC_FONT -> 9로 대체, font_size 10 -> 3로 대체
	settextjustify(pDC, CENTER_TEXT, BOTTOM_TEXT);
	gettextsetting(pDC, &newtext);
	outtextxy(pDC, 50, 50, L"FIRST TEST");
	str.Format(L"font = %d", newtext.font);
	outtextxy(pDC, 50, 100, str);
	str.Format(L"direction = %d", newtext.direction);
	outtextxy(pDC, 50, 150, str);
	str.Format(L"charsize = %d", newtext.charsize);
	outtextxy(pDC, 50, 200, str);
	str.Format(L"horizontal = %d", newtext.horiz);
	outtextxy(pDC, 50, 250, str);
	str.Format(L"vertical = %d", newtext.vert);
	outtextxy(pDC, 50, 300, str);
	
	//현재 아래의 settextstyle, settextjustify를 실행하면 그 하단의 텍스트들이 출력이 정상적으로 안된다.
//	settextstyle(pDC, text.font, text.direction, text.charsize);
//	settextjustify(pDC, text.horiz, text.vert);
	
	outtextxy(pDC, 50, 400, L"SECOND TEST");
	str.Format(L"font = %d", text.font);
	outtextxy(pDC, 50, 450, str);
	str.Format(L"direction = %d", text.direction);
	outtextxy(pDC, 50, 500, str);
	str.Format(L"charsize = %d", text.charsize);
	outtextxy(pDC, 50, 550, str);
	str.Format(L"horizontal = %d", text.horiz);
	outtextxy(pDC, 50, 600, str);
	str.Format(L"vertical = %d", text.vert);
	outtextxy(pDC, 50, 650, str);
}

void CGraphicMFCKDYView::example53(CDC* pDC)
{
	CString str = L"";
	struct textsetting text, newtext;

	char tc[] = "Turbo C++";
	int i;

	str = CString(tc);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 3);
	setcolor(pDC,YELLOW);
	for (i = 0; i <= 4; i++) {
		outtextxy(pDC, 83 + i, 113 + i, str);
	}
	
	setcolor(pDC, RED);
	for (i = 0; i <= 5; i++) {
		outtextxy(pDC, 67 + i, 107 + i, str);
	}
}

void CGraphicMFCKDYView::example54(CDC* pDC)
{
	CString str = L"";
	int i;

	line(pDC, 0, 10, 639, 10);
	for (i = 0; i <= 4; i++) {
		settextstyle(pDC, (i+1), HORIZ_DIR, 3);	//font i -> (i+1) |font_size, 10 -> 3
		outtextxy(pDC, i * 125, 10, L"A");
	}

	line(pDC, 0, 160, 639, 160);
	for (i = 0; i <= 4; i++) {
		settextstyle(pDC, (i + 1), HORIZ_DIR, 3); //font_size 10 -> 3
		outtextxy(pDC, i * 125, 160, L"B");
	}

	line(pDC, 0, 310, 639, 310);
	for (i = 0; i <= 4; i++) {
		settextstyle(pDC, (i + 1), HORIZ_DIR, 3); //font_size 10 -> 3
		outtextxy(pDC, i * 125, 310, L"C");
	}
}

void CGraphicMFCKDYView::example55(CDC* pDC)
{
	CString str = L"";
	int i;

	
//	registerbgifont(pDC, triplex_font(pDC));
//	registerbgifont(pDC, small_font(pDC));
//	registerbgifont(pDC, sansserif_font(pDC));
//	registerbgifont(pDC, gothic_font(pDC));

	line(pDC, 0, 10, 639, 10);
	for (i = 0; i <= 4; i++) {
		settextstyle(pDC, i, HORIZ_DIR, 5); //font_size 10 -> 5
		outtextxy(pDC, i * 125, 10, L"A");
	}
	line(pDC, 0, 160, 639, 160);
	for (i = 0; i <= 4; i++) {
		settextstyle(pDC, i, HORIZ_DIR, 5); //font_size 10 -> 5
		outtextxy(pDC, i * 125, 160, L"B");
	}
	line(pDC, 0, 310, 639, 310);
	for (i = 0; i <= 4; i++) {
		settextstyle(pDC, i, HORIZ_DIR, 5); //font_size 10 -> 5
		outtextxy(pDC, i * 125, 310, L"C");
	}
}

void CGraphicMFCKDYView::example56(CDC* pDC)
{
	CString str = L"";
	int i;
	struct textsetting oldtext;

	//	registerbgifont(pDC, triplex_font(pDC));
	//	registerbgifont(pDC, small_font(pDC));
	gettextsetting(pDC, &oldtext);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 2);
	setcolor(pDC, CYAN);
	outtextxy(pDC, 0, 50, L"Colleage of Engineering, Dongguk Univ");
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 2);
	setcolor(pDC, BLACK);	//WHITE -> BLACK
	outtextxy(pDC, 130, 100, L"Digital System Lab");
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 2);
	setcolor(pDC, YELLOW);
	outtextxy(pDC, 0, 300, L"Turbo C Graphics");
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 2);
	setcolor(pDC, GREEN);
	outtextxy(pDC, 135, 170, L"Prof. Jaeho Shin");

	settextjustify(pDC, oldtext.horiz, oldtext.vert);
	settextstyle(pDC, oldtext.font, oldtext.direction, oldtext.charsize);
}

void CGraphicMFCKDYView::example57(CDC* pDC)
{
	CString str = L"";
	int i;

	for (i = 0; i < 10; i++) {
		line(pDC, i * 62, 0, i * 62, 479);
	}
	for (i = 0; i < 4; i++) {
		line(pDC, 0, i * 110, 639, i * 110);
	}
	for (i = 1; i <= 10; i++) {
		settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, i-1);	//DEFAULT_FONT -> 9 | font_size i -> i-1
		outtextxy(pDC,(i - 1) * 62, 0, L"C");
	}
	for (i = 1; i <= 10; i++) {
		settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, i-1);	//DEFAULT_FONT -> 9 | font_size i -> i-1
		outtextxy(pDC, (i - 1) * 62, 110, L"C");
	}
	for (i = 1; i <= 10; i++) {
		settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, i-1);	//DEFAULT_FONT -> 9 | font_size i -> i-1
		outtextxy(pDC, (i - 1) * 62, 220, L"C");
	}
	for (i = 1; i <= 10; i++) {
		settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, i-1);	//DEFAULT_FONT -> 9 | font_size i -> i-1
		outtextxy(pDC, (i - 1) * 62, 330, L"C");
	}
}

void CGraphicMFCKDYView::example58(CDC* pDC)
{
	CString str = L"";
	int i;

	settextstyle(pDC, 9, HORIZ_DIR, 0); //TRIPLEX_FONT -> 9로 대체
	setusercharsize(pDC, 4, 1, 1, 1);
	outtextxy(pDC, 40, 20, L"Turbo C");
	settextstyle(pDC, 9, HORIZ_DIR, 0); //TRIPLEX_FONT -> 9로 대체
	setusercharsize(pDC, 4, 1, 10, 1);
	outtextxy(pDC, 40, 40, L"Turbo C");
}

void CGraphicMFCKDYView::example59(CDC* pDC)
{
	CString str = L"";
	char tc[] = "Turbo C++";
	int i;
	str = CString(tc);
	char_in_box1(pDC, 170, 50, 470, 150, str);
	char_in_box2(pDC, 170, 250, 470, 350, str);
	char_in_box3(pDC, 40, 50, 140, 350, str);
	char_in_box4(pDC, 500, 50, 600, 350, str);
}

void CGraphicMFCKDYView::example60(CDC* pDC)
{
	CString str = L"";
	char* tc[] = { "Turbo C++","[1] History of C++","[2] Present of C++","[3] Future of C++"};
	setfillstyle(pDC, SOLID_FILL, RED);	//color WHITE -> RED로 대체
	str = CString(tc[0]);
	char_in_box5(pDC, 20, 20, 9, GREEN, 1, str);
	str = CString(tc[1]);
	char_in_box5(pDC, 300, 150, 9, LIGHTBLUE, 1, str);
	str = CString(tc[2]);
	char_in_box5(pDC, 250, 220, 9, CYAN, 1, str);
	str = CString(tc[3]);
	char_in_box5(pDC, 200, 300, 9, YELLOW, 1, str);
}

void CGraphicMFCKDYView::example61(CDC* pDC)
{
	CString str = L"";
	char* tc[] = { "Regular Character","Bold Character 1",
		"Bold Character 2","Bold Character 3" };
	
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 0);
	str = CString(tc[0]);
	outtextxy(pDC, 30, 10, str);
	setcolor(pDC, GREEN);
	settextstyle(pDC, 9, HORIZ_DIR, 0);	//font, GOTHIC_FONT(4) -> 9로 대체
	outtextxy(pDC, 350, 10, str);

	str = CString(tc[1]);
	bold_char1(pDC, 30, 50, 1, 1, str);
	bold_char1(pDC, 350, 50, 4, 2, str);
	str = CString(tc[2]);
	bold_char2(pDC, 30, 90, 1, 1, str);
	bold_char2(pDC, 350, 90, 4, 2, str);
	str = CString(tc[3]);
	bold_char3(pDC, 30, 130, 1, 1, str);
	bold_char3(pDC, 350, 130, 4, 2, str);
}

void CGraphicMFCKDYView::example62(CDC* pDC)
{
	CString str = L"";
	char tc[] = "Bold Character";
	int i = 0, j = 0;

	str = CString(tc);
	for (i = 0; i <= 2; i++)
		for (j = 0; j <= 2; j++)
			bold_char(pDC, 50, 30 * (4 * i + j), TRIPLEX_FONT, GREEN, str, i, j);
}

void CGraphicMFCKDYView::example63(CDC* pDC)
{
	CString str = L"";
	char tc[] = "KOREA SEOUL";
	int i = 0, j = 0;

	str = CString(tc);
	for (i = 1; i <= 4; i++)
		line_char(pDC, 30, i*50,9,i+4,i,str);
}

void CGraphicMFCKDYView::example64(CDC* pDC)
{
	CString str = L"";
	char tc[] = "KOREA SEOUL";
	int i = 0, j = 0;

	str = CString(tc);
	for (i = 1; i <= 4; i++)
		line_char_example64(pDC, 30, i * 50, 9, i + 4, i, str);
}

void CGraphicMFCKDYView::example65(CDC* pDC)
{
	CString str = L"";
	char* tc[] = { "IBM PC/XT","IBM PC/AT","IBM PC/386","IBM PC/486"};
	int i = 0 ;

	for (i = 1; i <= 4; i++) {
		str = CString(tc[i - 1]);
		line_char_example65(pDC, 30, i * 50, 9, i + 4, i, str);
	}
}

void CGraphicMFCKDYView::example66(CDC* pDC)
{
	CString str = L"";
	char* tc[] = { "Introduction to Turbo C++ Graphics",
		"[1] The BGI Quick Tour",
		"[2] BGI Drawing Functions",
		"[3] The BGI Fonts and Text",
		"[4] Examples of 3-D Graph" };
	int i = 0;
	str = CString(tc[0]);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	reverse_char(pDC, 20, 20, LIGHTGREEN, str);
	str = CString(tc[1]);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	reverse_char(pDC, 20, 100, LIGHTRED, str);
	str = CString(tc[2]);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	reverse_char(pDC, 20, 170, LIGHTBLUE, str);
	str = CString(tc[3]);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	reverse_char(pDC, 20, 240, LIGHTMAGENTA, str);
	str = CString(tc[4]);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	reverse_char(pDC, 20, 310, CYAN, str);
}

void CGraphicMFCKDYView::example67(CDC* pDC)
{
	CString str = L"";
	char* tc[] = { "Introduction to Turbo C++ Graphics",
		"[1] The BGI Quick Tour",
		"[2] BGI Drawing Functions",
		"[3] The BGI Fonts and Text",
		"[4] Examples of 3-D Graph"};
	int i = 0;
	str = CString(tc[0]);
	shadow_char(pDC, 15, 20, 9, 0, TRIPLEX_FONT, 3, str, 3);
	for (i = 1; i <= 4; i++) {
		str = CString(tc[i]);
		shadow_char(pDC, 25, 40 + 60 * i, i + 9, BLACK, TRIPLEX_FONT, 2, str, 3);
	}
}

void CGraphicMFCKDYView::example68(CDC* pDC)
{
	CString str = L"";
	char* tc[] = { "Introduction to Turbo C++ Graphics",
		"[1] The BGI Quick Tour",
		"[2] BGI Drawing Functions",
		"[3] The BGI Fonts and Text",
		"[4] Examples of 3-D Graph" };
	int i = 0;
	str = CString(tc[0]);
	for (i = 9; i > 4; i--) {
		str = CString(tc[9-i]);
		shadow_char1(pDC, 50, 60*(9-i), i + 4, BLACK, TRIPLEX_FONT, 2, str, i-2);
	}
}

void CGraphicMFCKDYView::example69(CDC* pDC)
{
	CString str = L"";
	char* tc[] = { "Introduction to Turbo C++ Graphics",
		"[1] The BGI Quick Tour",
		"[2] BGI Drawing Functions",
		"[3] The BGI Fonts and Text",
		"[4] Examples of 3-D Graph" };
	int i = 0;
	change_palette_g(pDC);
	for (i = 9; i > 4; i--) {
		str = CString(tc[9 - i]);
		shadow_char2(pDC, 10, 60 * (9 - i), 10-i, TRIPLEX_FONT, 2, str, 9);
	}
}

void CGraphicMFCKDYView::example70(CDC* pDC)
{
	CString str = L"";
	char* tc[] = { "J. SHIN",
		"Dongguk University",
		"SEOUL KOREA" };
	int i = 0;
	
	setfillstyle(pDC, SOLID_FILL, 8);
	bar(pDC, 0, 0, 639, 479);
	change_palette(pDC);
	str = CString(tc[0]);
	shadow_char3(pDC, 20, 20, 2, TRIPLEX_FONT, 10, str, 2);
	str = CString(tc[1]);
	shadow_char3(pDC, 20, 180, 1, TRIPLEX_FONT, 4, str, 3);
	str = CString(tc[2]);
	shadow_char3(pDC, 20, 320, 3, TRIPLEX_FONT, 6, str, 2);
}

void CGraphicMFCKDYView::example71(CDC* pDC)
{
	CString str = L"";
	char* tc[] = { "Introduction to Turbo C++ Graphics",
		"[1] The BGI Quick Tour",
		"[2] BGI Drawing Functions",
		"[3] The BGI Fonts and Text",
		"[4] Examples of 3-D Graph" };
	int i = 0;

	setfillstyle(pDC, SOLID_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 399);
	str = CString(tc[0]);
	hollow_char1(pDC, 0, 30, BLACK, GREEN, TRIPLEX_FONT, 4, str);

	str = CString(tc[1]);
	hollow_char1(pDC, 15, 100, BLACK, CYAN, TRIPLEX_FONT, 2, str);

	str = CString(tc[2]);
	hollow_char1(pDC, 15, 160, BLACK, YELLOW, TRIPLEX_FONT, 2, str);

	str = CString(tc[3]);
	hollow_char1(pDC, 15, 220, BLACK, LIGHTRED, TRIPLEX_FONT, 2, str);

	//책과는 소스코드가 다르나 그림과 같이 나오게 하기 위해선 아래 코드가 추가적으로 필요
	str = CString(tc[4]);
	hollow_char1(pDC, 15, 280, BLACK, BLUE, TRIPLEX_FONT, 2, str);
}

void CGraphicMFCKDYView::example72(CDC* pDC)
{
	CString str = L"";
	char tc[] = "Turbo C++ Graphics";
	int i = 0, j = 0;

	str = CString(tc);
	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
			hollow_char0(pDC, 50, 30 * (4 * (i - 1) + (j - 1)), TRIPLEX_FONT, GREEN, str, i, j);
}

void CGraphicMFCKDYView::example73(CDC* pDC)
{
	CString str = L"";
	char tc[] = "Introduction to Graphics using Turbo C++";
	int i = 0, j = 0;

	setfillstyle(pDC, SOLID_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479); 
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 3);
	setcolor(pDC, GREEN);
	str = CString(tc);
	outtextxy(pDC, 15, 10, str);

	char1(pDC, 15, 60, BLACK, CYAN, TRIPLEX_FONT, 3, str);
	char2(pDC, 15, 110, BLACK, RED,YELLOW, TRIPLEX_FONT, 3, str);
	char3(pDC, 15, 160, WHITE, BLACK,LIGHTGRAY, TRIPLEX_FONT, 3, str);
	char3(pDC, 15, 210, BLACK, WHITE, LIGHTGRAY, TRIPLEX_FONT, 3, str);
	char4(pDC, 15, 260, WHITE, BLACK, LIGHTGRAY, TRIPLEX_FONT, 3, str);
	char4(pDC, 15, 310, BLACK, WHITE, LIGHTGRAY, TRIPLEX_FONT, 3, str);
	char5(pDC, 15, 360, WHITE, BLACK, LIGHTGRAY, TRIPLEX_FONT, 3, str);
	char5(pDC, 15, 410, BLACK, WHITE, LIGHTGRAY, TRIPLEX_FONT, 3, str);
}

void CGraphicMFCKDYView::example74(CDC* pDC)
{
	CString str = L"";
	int i, j;
	int data1[] = { 200,230,250,90 };
	int data2[] = { 150,250,180,80 };
	char* comment[] = { "North Sea Oil","South Sea Oil" };
	char* xscale[] = { "1980","1990","2000","2010" };
	char* yscale[] = { "200","100" };
	char title[] = "CRUDE OIL PRODUCTION";

	setfillstyle(pDC, SOLID_FILL, WHITE);
	bar(pDC, 0, 0, 639, 479);
	s_bar(pDC, 115, 10, 505, 50, LIGHTGREEN);
	str = CString(title);
	h_char(pDC, 130, 15, WHITE, str);
	
	
	setcolor(pDC, CYAN);
	c_bar3d(pDC, 50, 100, 60, 350, 50, CYAN, CYAN, LIGHTCYAN);
	c_bar3d(pDC, 60, 340, 550, 350, 50, CYAN, LIGHTCYAN, CYAN);
	
	setcolor(pDC, LIGHTBLUE);
	for (i = 0; i <= 3; i++)
		c_bar3d(pDC, 150 + i * 100, 335, 155 + i * 100, 340, 50, BLACK, LIGHTCYAN, CYAN);
	
	for (i = 0; i <= 1; i++)
		c_bar3d(pDC, 60, 150 + i * 100, 65, 155 + i * 100, 50, BLACK, BLACK, CYAN);
	
	setcolor(pDC, CYAN);
	line(pDC, 60, 340, 110, 302);
	s_bar(pDC, 500, 100, 625, 150, BROWN);
	s_bar(pDC, 500, 200, 625, 250, YELLOW);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	for (j = 0; j <= 3; j++) {
		str = CString(xscale[j]);
		outtextxy(pDC, 120 + j * 100, 350, str);
	}
	for (j = 0; j <= 1; j++) {
		str = CString(yscale[j]);
		outtextxy(pDC, 1, 140 + j * 100, str);
	}
	
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 0);
	for (j = 0; j <= 1; j++) {
		str = CString(comment[j]);
		outtextxy(pDC, 505, 117 + j * 100, str);
	}
	
	c_line(pDC, data1, BROWN);
	c_line(pDC, data2, YELLOW);
}

void CGraphicMFCKDYView::example75(CDC* pDC)
{
	CString str = L"";
	int i, j;
	int data1[] = { 12,40,61,153 };
	char* xscale[] = { "1975","1980","1985","1991","[years]"};
	char* yscale[] = { "150","120","90","60","30" };
	char yunit[] = "[Billion $]";
	char title[] = "THE VOLUMN OF TRADE OF KOREA";
	change_palette_g1(pDC);
	setfillstyle(pDC, SOLID_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	s_bar_example75(pDC, 20, 10, 620, 50, MAGENTA);
	str = CString(title);
	h_char_example75(pDC, 70, 13, RED, str);	//c, WHITE -> RED로 대체
	for (i = 0; i <= 4; i++) {
		setfillstyle(pDC, SOLID_FILL, 10 + i);
		bar(pDC, 100, 100 + i * 50, 550, 150 + i * 50);
	}
	/*
	setcolor(pDC,WHITE);
	rectangle(pDC, 100, 100, 550, 350);
	*/
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 0);
	for (j = 0; j <= 4; j++) {
		str = CString(xscale[j]);
		outtextxy(pDC, 135 + j * 100, 350, str);
	}
	for (j = 0; j <= 1; j++) {
		str = CString(yscale[j]);
		outtextxy(pDC, 60, 90 + j * 50, str);
	}
	for (j = 2; j <= 4; j++) {
		str = CString(yscale[j]);
		outtextxy(pDC, 60, 90 + j * 50, str);
	}
	settextstyle(pDC, TRIPLEX_FONT, VERT_DIR, 0);
	str = CString(yunit);
	outtextxy(pDC, 10, 120, str);
	c_line_example75(pDC, data1, 4, BROWN);
	
}

void CGraphicMFCKDYView::example76(CDC* pDC)
{
	CString str = L"";
	int i = 0, j = 0;
	float data[] = { 0.0,0.1,0.2,0.3,1.2,2.4,3.6 };
	char xunit[] = "Drive Current [Amps]";
	char yunit[] = "CW Optical Power [Watts]";
	char* xaxis[] = { "0","2","4","6","8","10","12","14" };
	char* yaxis[] = { "4","3","2","1" };
	char title[] = "DIODE LASER POWER";

	setfillstyle(pDC, SOLID_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	mac_frame2(pDC, 100, 50, 440, 300, 3, GREEN);
	str = CString(title);
	relief_char(pDC, 170, 10, WHITE, BLACK, LIGHTGRAY, TRIPLEX_FONT, HORIZ_DIR, 1, str);
	for (i = 0; i <= 7; i++) {
		str = CString(xaxis[i]);
		relief_char(pDC, 145 + 50 * i, 305, BLACK, LIGHTGREEN, GREEN, TRIPLEX_FONT, HORIZ_DIR, 0, str);
	}
	str = CString(xunit);
	relief_char(pDC, 255, 322, BLACK, LIGHTGREEN, GREEN, TRIPLEX_FONT, HORIZ_DIR, 0, str);
	for (i = 0; i <= 3; i++) {
		str = CString(yaxis[i]);
		relief_char(pDC, 130, 100 + i * 50, BLACK, LIGHTGREEN, GREEN, TRIPLEX_FONT, HORIZ_DIR, 0, str);
	}
	str = CString(yunit);
	relief_char(pDC, 105, 300, BLACK, LIGHTGREEN, GREEN, TRIPLEX_FONT, VERT_DIR, 0, str);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	for (i = 0; i <= 7; i++) {
		relief_line(pDC, 150 + 50 * i, 100, 150 + 50 * i, 300, BLACK, LIGHTGREEN, GREEN);
	}
	relief_line(pDC, 148, 38 * i, 500, 38 * i, BLACK, LIGHTGREEN, GREEN);
	bold_line(pDC, data, 7, YELLOW);
}

void CGraphicMFCKDYView::example77(CDC* pDC)
{
	CString str = L"";
	int i, j;
	int data1[] = { 19,37,94,99 };
	char* xscale[] = { "1975","1980","1989","1991","[years]" };
	char* yscale[] = { "100","80","60","40","20"};
	char yunit[] = "[GWh]";
	char title[] = "KOREA ELECTRICITY PRODUCTION";
	change_palette_r(pDC);
	setfillstyle(pDC, SOLID_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	s_bar_example77(pDC, 40, 10, 600, 50, BROWN);
	str = CString(title);
	h_char1(pDC, 70, 13, BLUE, str);
	
	for (i = 0; i <= 4; i++) {
		setfillstyle(pDC, SOLID_FILL, 10 + i);
		bar(pDC, 100, 100 + i * 50, 550, 150 + i * 50);
	}
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	for (j = 0; j <= 4; j++) {
		str = CString(xscale[j]);
		outtextxy(pDC, 150 + j * 100, 350, str);
	}

	for (j = 1; j <= 4; j++) {
		str = CString(yscale[j]);
		outtextxy(pDC, 60, 80 + j * 50, str);
	}
	settextstyle(pDC, TRIPLEX_FONT, VERT_DIR, 1);
	str = CString(yunit);
	outtextxy(pDC, 10, 150, str);

	c_bar1(pDC, data1, 4, 100);
	setcolor(pDC, BLACK);
//	rectangle(pDC, 100, 100, 550, 350);
}

void CGraphicMFCKDYView::example78(CDC* pDC)
{
	CString str = L"";
	int i, j;
	int data1[] = { 19,37,94,99 };
	char* xscale[] = { "1975","1980","1989","1991","[years]" };
	char* yscale[] = { "100","80","60","40","20" };
	char yunit[] = "[GWh]";
	char title[] = "KOREA ELECTRICITY PRODUCTION";
	change_palette_r(pDC);
	setfillstyle(pDC, SOLID_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	s_bar_example77(pDC, 40, 10, 600, 50, BROWN);
	str = CString(title);
	h_char1(pDC, 70, 13, BLUE, str);

	for (i = 0; i <= 4; i++) {
		setfillstyle(pDC, SOLID_FILL, 10 + i);
		bar(pDC, 100, 100 + i * 50, 550, 150 + i * 50);
	}
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	for (j = 0; j <= 4; j++) {
		str = CString(xscale[j]);
		outtextxy(pDC, 150 + j * 100, 350, str);
	}

	for (j = 1; j <= 4; j++) {
		str = CString(yscale[j]);
		outtextxy(pDC, 60, 80 + j * 50, str);
	}
	settextstyle(pDC, TRIPLEX_FONT, VERT_DIR, 1);
	str = CString(yunit);
	outtextxy(pDC, 10, 150, str);

	c_bar1(pDC, data1, 4, 100);
	setcolor(pDC, BLACK);
//	rectangle(pDC, 100, 100, 550, 350);
}

void CGraphicMFCKDYView::example79(CDC* pDC)
{
	CString str = L"";
	int i, j,n=0,angle[10];
	double v[10];
	double data[] = { 2728,427,1077,15 };
	struct arccoordstype arcc; //해당 구조체는 그려지는 직전 호에 대한 정보를 담고 있다. 추후 만들어야 함.!!
	char* comment[] = { "passenger car","bus","truck","others" };
	char title[] = "THE COMPONENT RATIO OF AUTOMOBILE";
	
	n = sizeof(data) / sizeof(double);
	for (j = 0; j <= 9; j++)
		for (i = 0; i <= 9; i++)
			cframe_example79(pDC, i * 64, 50 * j, 63, 49, 2, WHITE, LIGHTBLUE, BLUE);
	s_bar_example79(pDC, 40, 10, 600, 50, LIGHTGREEN);
	str = CString(title);
	h_jchar(pDC, 60, 25, WHITE, str);
	s_bar_example79(pDC, 450, 420, 580, 460, LIGHTGREEN);
	h_jchar(pDC, 460, 435, WHITE, L"in 1991");
	v[0] = 0.0;
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	setcolor(pDC, RED);
	for (i = 1; i <= n; i++)
		v[i] = v[i - 1] + data[i - 1];
	for (i = 0; i <= n; i++)
		angle[i] = (int)(v[i] / v[n] * 360);
	ellipse(pDC, 320, 250, 180, 360, 200, 100);
	line(pDC, 120, 200, 120, 250);
	line(pDC, 520, 200, 520, 250);
	
	
	for (i = 0; i <= n - 1; i++) {
		setfillstyle(pDC, i + 2, i + 1);
		sector(pDC, 320, 200, angle[i], angle[i + 1], 200, 100);
		getarccoords(&arcc);
		line(pDC, arcc.xend, arcc.yend, arcc.xend, arcc.yend + 50);
		if (angle[i + 1] > 180) {
			pDC->FloodFill(arcc.xend - 2, arcc.yend + 25, changeBookColorToMFCColor(RED));
			// ExtFloodFill(pDC->m_hDC, arcc.xend -2, arcc.yend +25, changeBookColorToMFCColor(RED), FLOODFILLSURFACE);
		}
	}
	
	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	s_bar_example79(pDC, 50, 100, 300, 140, WHITE);
	str = CString(comment[0]);
	h_jchar(pDC,70, 110, RED, str);

	s_bar_example79(pDC, 200, 210, 280, 250, WHITE);
	str = CString(comment[1]);
	h_jchar(pDC, 220, 220, RED, str);

	s_bar_example79(pDC, 420, 250, 530, 290, WHITE);
	str = CString(comment[2]);
	h_jchar(pDC, 440, 260, RED, str);

	s_bar_example79(pDC, 450, 140, 580, 180, WHITE);
	str = CString(comment[3]);
	h_jchar(pDC, 470, 150, RED, str);
	
}

void CGraphicMFCKDYView::initialized_arccoordstype(struct arccoordstype* arcc)
{
	arcc->x = 0;
	arcc->y = 0;
	arcc->xend = 0;
	arcc->yend = 0;
	arcc->xstart = 0;
	arcc->ystart = 0;
}

void CGraphicMFCKDYView::getarccoords(struct arccoordstype* arcc)
{
	arcc->x = main_arccoordstyle.x;
	arcc->y = main_arccoordstyle.y;
	arcc->xend = main_arccoordstyle.xend;
	arcc->yend = main_arccoordstyle.yend;
	arcc->xstart = main_arccoordstyle.xstart;
	arcc->ystart = main_arccoordstyle.ystart;
}

void CGraphicMFCKDYView::setarccoords(int x1, int y1, int x2, int y2)
{
	int center_x = x1+((x2 - x1) / 2);
	int center_y = y2 + ((y1 - y2) / 2);

	main_arccoordstyle.x = center_x;
	main_arccoordstyle.y = center_y;
	main_arccoordstyle.xstart = main_arccoordstyle.x;
	main_arccoordstyle.ystart = y1;
	main_arccoordstyle.xend = main_arccoordstyle.xstart;
	main_arccoordstyle.yend = main_arccoordstyle.ystart;
}
void CGraphicMFCKDYView::setarccoords(int x, int y, int radius)
{
	// 100, 100, radius 5
	main_arccoordstyle.x = x;
	main_arccoordstyle.y = y;
	main_arccoordstyle.xstart = y+radius;
	main_arccoordstyle.ystart = y+radius;
	main_arccoordstyle.xend = main_arccoordstyle.xstart;
	main_arccoordstyle.yend = main_arccoordstyle.ystart;
}
void CGraphicMFCKDYView::setarccoords(int x, int y, int startAngle, int endAngle, int xradius, int yradius)
{
	
	int startX_dot = x + (round((xradius * cos(getRadian(360 - startAngle)))));
	int startY_dot = y + (round((yradius * sin(getRadian(360 - startAngle)))));
	int endX_dot = x + (round((xradius * cos(getRadian(360 - endAngle)))));
	int endY_dot = y + (round((yradius * sin(getRadian(360 - endAngle)))));
	main_arccoordstyle.x = x;
	main_arccoordstyle.y = y;
	main_arccoordstyle.xstart = startX_dot;
	main_arccoordstyle.ystart = startY_dot;
	main_arccoordstyle.xend = endX_dot;
	main_arccoordstyle.yend = endY_dot;
}


void CGraphicMFCKDYView::example80(CDC* pDC)
{
	CString str = L"";
	int i, j, n, angle[10], x0=0, y0=0;
	double v[10], data[] = { 10,20,30,40 };
	struct arccoordstype arcc;
	char* perc[] = { "Kindergarten 10%","Primary school 20%","Middle school 30%","High school 40%" };
	char title[] = "SPREAD RATE OF COMPUTER";

	v[0] = 0.0;
	n = sizeof(data) / sizeof(double);
	setfillstyle(pDC, HATCH_FILL, CYAN);
	bar(pDC, 0, 0, 639, 479);
	s_bar_example80(pDC, 115, 10, 505, 50, LIGHTGREEN);	
	str = CString(title);
	h_jchar(pDC, 130, 20, WHITE, str);
	setcolor(pDC, GREEN);
	for (i = 1; i <= n; i++)
		v[i] = v[i - 1] + data[i - 1];
	for (i = 0; i <= n; i++)
		angle[i] = (int)(v[i] / v[n] * 360);
	for (i = 0; i <= n - 1; i++) {
		setfillstyle(pDC, SOLID_FILL, i + 2);
		sector(pDC, 320, 200, angle[i], angle[i + 1], 200, 100);
	}
	
	change_palette_g_example80(pDC);
	ellipse(pDC, 320, 250, 180, 360, 200, 100);
	line(pDC, 120, 200, 120, 250);
	j = 7;
	for (i = 180; i <= 270; i += 10) {
		ellipse(pDC, 320, 200, i, i + 10, 200, 100);
		getarccoords(&arcc);
		line(pDC, arcc.xend, arcc.yend, arcc.xend, arcc.yend + 50);
		setfillstyle(pDC, SOLID_FILL, j--);
		pDC->FloodFill(arcc.xend - 2, arcc.yend + 25, changeBookColorToMFCColor(GREEN));
	//	ExtFloodFill(pDC->m_hDC, arcc.xend -2, arcc.yend +25, changeBookColorToMFCColor(GREEN), FLOODFILLSURFACE);
	}

	j = 15;
	for (i = 270; i <= 350; i += 10) {
		ellipse(pDC, 320, 200, i, i + 10, 200, 100);
		getarccoords(&arcc);
		line(pDC, arcc.xend, arcc.yend, arcc.xend, arcc.yend + 50);
		setfillstyle(pDC, SOLID_FILL, j--);
		pDC->FloodFill(arcc.xend - 2, arcc.yend + 25, changeBookColorToMFCColor(GREEN));
	//	ExtFloodFill(pDC->m_hDC, arcc.xend - 2, arcc.yend + 25, changeBookColorToMFCColor(GREEN), FLOODFILLSURFACE);
	}

	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 0);
	for (i = 0; i <= n - 1; i++) {
		ellipse(pDC, 320, 200, angle[i], angle[i + 1], 200, 100);
		getarccoords(&arcc);
		x0 = (arcc.xstart + arcc.xend) / 2;
		y0 = (arcc.ystart + arcc.yend) / 2;
		s_bar_example80(pDC, x0 - 50, y0, x0 + 110, y0 + 20, WHITE);
		setcolor(pDC, BLACK);
		str = CString(perc[i]);
		outtextxy(pDC, x0 - 40, y0 + 5, str);
		outtextxy(pDC, x0 - 39, y0 + 5, str);
	}
	
}

void CGraphicMFCKDYView::example81(CDC* pDC)
{
	CString str = L"";
	int i, j;
	int data1[] = { 100,80,50,70,90 };
	int data2[] = { 90,60,90,95,80 };
	char* item[] = { "Salary","Food","Traffic","Leisure","Tax" };
	char* field[] = { "Sept. ","Oct. " };
	char title[] = "Incomings and Expenses";
	change_palette_b2(pDC);
	setfillstyle(pDC, SOLID_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	s_bar_example81(pDC, 140, 5, 500, 45, BROWN);
	str = CString(title);
	h_char2(pDC, 150, 5, BLUE, str);
	for (i = 5; i >= 1; i--)
		fc_circle(pDC, 320, 220, i * 25, 15 - i);

	radar1(pDC, 5, 320, 220, 125, RED, item);
	
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	radar_data(pDC, 5, 320, 220, BLACK, data1);
	radar_data(pDC, 5, 320, 220, RED, data2);
	setcolor(pDC, BLACK);
	line(pDC, 30, 100, 80, 100);
	str = CString(field[0]);
	relief_char_example81(pDC, 100, 80, BLACK, WHITE, LIGHTGRAY, TRIPLEX_FONT, HORIZ_DIR, 1, str);
	setcolor(pDC, RED);
	line(pDC, 30, 130, 80, 130);
	str = CString(field[1]);
	relief_char_example81(pDC, 100, 115, BLACK, WHITE, LIGHTGRAY, TRIPLEX_FONT, HORIZ_DIR, 1, str);
}

//for example 82,83
// typedef enum { false, true } boolean;
#define EXAMPLE82_SIZE 1.5
#define EXAMPLE82_ZROTATE 11.
#define EXAMPLE82_YROTATE 40.
#define EXAMPLE82_XROTATE 0.
//~for example 82

void CGraphicMFCKDYView::example82(CDC* pDC)
{
	CString str = L"";
	std::vector<CString> str_array;
	int plotted = false;
	int xx, yy, cen_x, cen_y;
	double x, y, z, x0, y0, z0, xr, yr, zr;
	char title[] = "3-dimensional graph I";
	xr = EXAMPLE82_XROTATE * PI / 180.;
	yr = EXAMPLE82_YROTATE * PI / 180.;
	zr = EXAMPLE82_ZROTATE * PI / 180.;
	setfillstyle(pDC, SOLID_FILL , LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	str = CString(title);
	gwindow_example82(pDC, 50, 50, 590, 450, CYAN, str);
	cen_x = 320;
	cen_y = 260;
	setcolor(pDC, MAGENTA);
	
	for (x = 115.; x >= -115; x -= 5.) {
		for (y = -115.; y <= 115.; y += 5.) {
			z = sync(x, y);
			x0 = x * EXAMPLE82_SIZE;
			y0 = y * EXAMPLE82_SIZE;
			z0 = z * EXAMPLE82_SIZE;
			rotate3d(pDC, xr, yr, zr, &x0, &y0, &z0);
			xx = cen_x + (int)y0;
			yy = cen_y - (int)z0;
			if (plotted == false)
				pDC->MoveTo(xx, yy);
			else {
				//pDC->LineTo(xx, yy);
				lineto(pDC, xx, yy);
			}
			plotted = true;
		}
		plotted = false;
	}
	
}

void CGraphicMFCKDYView::example83(CDC* pDC)
{
	CString str = L"";
	std::vector<CString> str_array;
	int i, xp[100] = { 0 }, yp[100] = { 0 };
	int xplotted = false,yplotted = false;
	int xx, yy, cen_x, cen_y;
	double x, y, z, x0, y0, z0, xr, yr, zr;
	char title[] = "3-dimensional graph II";
	xr = EXAMPLE82_XROTATE * PI / 180.;
	yr = EXAMPLE82_YROTATE * PI / 180.;
	zr = EXAMPLE82_ZROTATE * PI / 180.;
	setfillstyle(pDC, INTERLEAVE_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	str = CString(title);
	gwindow_example82(pDC, 50, 50, 590, 450, CYAN, str);
	cen_x = 320;
	cen_y = 260;
	setcolor(pDC, MAGENTA);
	for (x = 115.; x >= -115; x -= 5.) {
		for (i=0,y = -115.; y <= 115.;i++, y += 5.) {
			z = sync(x, y);
			x0 = x * EXAMPLE82_SIZE;
			y0 = y * EXAMPLE82_SIZE;
			z0 = z * EXAMPLE82_SIZE;
			rotate3d(pDC, xr, yr, zr, &x0, &y0, &z0);
			xx = cen_x + (int)y0;
			yy = cen_y - (int)z0;
			if (xplotted == true) {
				line(pDC, xp[i], yp[i], xx, yy);
			}
			if (yplotted == false)
				pDC->MoveTo(xx, yy);
			else {
				lineto(pDC, xx, yy);
			}
			yplotted = true;
			xp[i] = xx;
			yp[i] = yy;
		}
		yplotted = false;
		xplotted = true;
	}
}

void CGraphicMFCKDYView::example84(CDC* pDC)
{
	CString str = L"";
	int i, cen_x, cen_y, xs, ys, poly[100];
	double x, y, z, x0, y0, z0, xr, yr, zr;
	char title[] = "3-dimensional graph III";
	xr = EXAMPLE82_XROTATE * PI / 180.;
	yr = EXAMPLE82_YROTATE * PI / 180.;
	zr = EXAMPLE82_ZROTATE * PI / 180.;
	setfillstyle(pDC, INTERLEAVE_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	str = CString(title);
	gwindow_example82(pDC, 50, 50, 590, 450, CYAN, str);
	cen_x = 320;
	cen_y = 260;

	poly[95] = 440;
	poly[94] = 320;

	for (x = 115.; x >= -115; x -= 5.) {
		setcolor(pDC, GREEN);
		for (i = 0, y = -115.; y <= 115.; y += 5.,i+=2) {
			z = sync(x, y);
			x0 = x * EXAMPLE82_SIZE;
			y0 = y * EXAMPLE82_SIZE;
			z0 = z * EXAMPLE82_SIZE;
			rotate3d(pDC, xr, yr, zr, &x0, &y0, &z0);
			poly[i] = cen_x + (int)y0;
			poly[i+1] = cen_y - (int)z0;
		}
		poly[96] = poly[0];
		poly[97] = poly[1];
		setfillstyle(pDC, SOLID_FILL, WHITE);
		//fillPoly(pDC, 48, poly);
		drawPloy(pDC, 48, poly);
		setcolor(pDC, WHITE);
		line(pDC, poly[94], poly[95], poly[96], poly[97]);
		line(pDC, poly[92], poly[93], poly[94], poly[95]);
	}
}

void CGraphicMFCKDYView::example85(CDC* pDC)
{
	CSize asp;
	asp = pDC->GetAspectRatioFilter();
	CString str = L"";
	int i, j,xp[50],yp[50],cen_x, cen_y, xs, ys, poly[100],plotted=false;
	double x, y, z, x0, y0, z0, xr, yr, zr;
	char title[] = "3-dimensional graph IV";
	xr = EXAMPLE82_XROTATE * PI / 180.;
	yr = EXAMPLE82_YROTATE * PI / 180.;
	zr = EXAMPLE82_ZROTATE * PI / 180.;
	setfillstyle(pDC, INTERLEAVE_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	str = CString(title);
	gwindow_example82(pDC, 50, 50, 590, 450, CYAN, str);
	cen_x = 320;
	cen_y = 260;

	poly[95] = 440;
	poly[94] = 320;

	for (x = 115.; x >= -115; x -= 5.) {
		setcolor(pDC, GREEN);
		for (i = 0,j=0 ,y = -115.; y <= 115.; y += 5., i += 2,j++) {
			z = sync(x, y);
			x0 = x * EXAMPLE82_SIZE;
			y0 = y * EXAMPLE82_SIZE;
			z0 = z * EXAMPLE82_SIZE;
			rotate3d(pDC, xr, yr, zr, &x0, &y0, &z0);
			poly[i] = cen_x + (int)y0;
			poly[i + 1] = cen_y - (int)z0; //poly[i + 1] = cen_y - (int)(z0*xasp/yasp);
			if (plotted == true)
				line(pDC,xp[j], yp[j], poly[i], poly[i + 1]);
			xp[j] = poly[i];
			yp[j] = poly[i + 1];
		}
		poly[96] = poly[0];
		poly[97] = poly[1];
		setfillstyle(pDC, SOLID_FILL, WHITE);
//		fillPoly(pDC, 48, poly);
		drawPloy(pDC, 48, poly);
		setcolor(pDC, WHITE);
		line(pDC, poly[94], poly[95], poly[96], poly[97]);
		line(pDC, poly[92], poly[93], poly[94], poly[95]);
		plotted = true;
	}
}

void CGraphicMFCKDYView::example86(CDC* pDC)
{
	CString str = L"";
	int i, j, cen_x, cen_y,
		xs, ys, plotted = false,xx,yy,min[640],max[640],xd,yd,xp,yp;
	double x, y, z, x0, y0, z0, xr, yr, zr;
	char title[] = "3-dimensional graph IV";
	xr = EXAMPLE82_XROTATE * PI / 180.;
	yr = EXAMPLE82_YROTATE * PI / 180.;
	zr = EXAMPLE82_ZROTATE * PI / 180.;

	for (i = 0; i < 640; i++) {
		min[i] = 479;
		max[i] = 0;
	}
	setfillstyle(pDC, INTERLEAVE_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	str = CString(title);
	gwindow_example82(pDC, 50, 50, 590, 450, CYAN, str);
	cen_x = 320;
	cen_y = 260;

	for (x = 115.; x >= -115; x -= 5.) {
		xp = 0;
		for (i = 0, j = 0, y = -115.; y <= 115.; y += 5., i += 2, j++) {
			z = sync(x, y);
			x0 = x * EXAMPLE82_SIZE;
			y0 = y * EXAMPLE82_SIZE;
			z0 = z * EXAMPLE82_SIZE;
			rotate3d(pDC, xr, yr, zr, &x0, &y0, &z0);
			xx = cen_x + (int)y0;
			yy = cen_y - (int)z0;
			xd = xx - xp;
			if (xp == 0 || xd == 1 || xd == 0) {
				xp = xx;
				yp = yy;
				if (yy < min[xx]) {
					min[xx] == yy;
					putpixel(pDC, xx, yy, changeBookColorToMFCColor(BLACK));
				}
				if (yy > max[xx]) {
					max[xx] = yy;
					putpixel(pDC, xx, yy, changeBookColorToMFCColor(BLACK));
				}
			}
			else {
				yd = (double)((yy - yp) / xd);
				for (i = 1; i <= xd; i++) {
					xx = xp + i;
					yy = yp + (int)(yd * i + 0.5);
					if (yy < min[xx]) {
						min[xx] = yy;
						putpixel(pDC, xx, yy, changeBookColorToMFCColor(BLACK));
					}
					if (yy > max[xx]) {
						max[xx] = yy;
						putpixel(pDC, xx, yy, changeBookColorToMFCColor(BLACK));
					}
				}
				xp = xx;
				yp = yy;
			}
		}
	}
}

void CGraphicMFCKDYView::example87(CDC* pDC)
{
	CString str = L"";
	int i, j, cen_x, cen_y,
		xs, ys, plotted = false, xx, yy, min[640], max[640], xd, yd, xp, yp,color;
	double x, y, z, x0, y0, z0, xr, yr, zr;
	char title[] = "3-dimensional graph VI";
	xr = EXAMPLE82_XROTATE * PI / 180.;
	yr = EXAMPLE82_YROTATE * PI / 180.;
	zr = EXAMPLE82_ZROTATE * PI / 180.;

	for (i = 0; i < 640; i++) {
		min[i] = 479;
		max[i] = 0;
	}
	setfillstyle(pDC, INTERLEAVE_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	str = CString(title);
	gwindow_example82(pDC, 50, 50, 590, 450, CYAN, str);
	cen_x = 320;
	cen_y = 260;

	for (x = 115.; x >= -115; x -= 5.) {
		xp = 0;
		for (y = -115.; y <= 115.; y++) {
			z = sync(x, y);
			x0 = x * EXAMPLE82_SIZE;
			y0 = y * EXAMPLE82_SIZE;
			z0 = z * EXAMPLE82_SIZE;
			if (z0 > 100)
				color = RED;
			else if (z0 <= 100 && z0 > 50)
				color = GREEN;
			else if (z0 <= 50 && z0 > 0)
				color = LIGHTMAGENTA;
			else
				color = BLUE;
			rotate3d(pDC, xr, yr, zr, &x0, &y0, &z0);
			xx = cen_x + (int)y0;
			yy = cen_y - (int)z0;
			xd = xx - xp;
			if (xp == 0 || xd == 1 || xd == 0) {
				xp = xx;
				yp = yy;
				if (yy < min[xx]) {
					min[xx] == yy;
					putpixel(pDC, xx, yy, changeBookColorToMFCColor(color));
				}
				if (yy > max[xx]) {
					max[xx] = yy;
					putpixel(pDC, xx, yy, changeBookColorToMFCColor(color));
				}
			}
			else {
				yd = (double)(yy - yp) / xd;
				for (i = 1; i <= xd; i++) {
					xx = xp + i;
					yy = yp + (int)(yd * i + 0.5);
					if (yy < min[xx]) {
						min[xx] = yy;
						putpixel(pDC, xx, yy, changeBookColorToMFCColor(BLACK));
					}
					if (yy > max[xx]) {
						max[xx] = yy;
						putpixel(pDC, xx, yy, changeBookColorToMFCColor(BLACK));
					}
				}
				xp = xx;
				yp = yy;
			}
		}
	}
}

//for example 88
// typedef enum { false, true } boolean;
#define LATITUDE 37.29
#define LONGITUDE 127.04
#define RADIUS 200.
#define INTERVAL 15.
#define ZROTATE -LONGITUDE
#define YROTATE -LATITUDE
#define XROTATE 22.5
#define PI_2 (PI / 2)
//~for example 88

void CGraphicMFCKDYView::example88(CDC* pDC)
{
	CString str = L"";
	int plotted = false;
	double x, y, z, p, fi, zr, yr, xr;
	char title[] = "3-dimensional graph VI";
	xr = XROTATE * PI / 180.;
	yr = YROTATE * PI / 180.;
	zr = ZROTATE * PI / 180.;

	circle(pDC, getmaxx() / 2, getmaxy() / 2, RADIUS);
	circle(pDC, getmaxx() / 2, getmaxy() / 2, 1);
	/*Latitude*/
	for (p = PI_2; p > -PI_2; p -= INTERVAL * PI / 180.) {
		plotted = false;
		if (fabs(p - 0.) < 1.e-5)
			setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
		else
			setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
		for (fi = 0.; fi <= 2. * PI; fi += PI / 24.) {
			x = RADIUS * cos(p) * cos(fi);
			y = RADIUS * cos(p) * sin(fi);
			z = RADIUS * sin(p);
			rotate3d(pDC, xr, yr, zr, &x, &y, &z);
			if (x < 0.)
				plotted = false;
			else
				graph(pDC, y, z, &plotted);
		}
	}
	/*Longitude*/
	for (fi = 0; fi < PI; fi += INTERVAL * PI / 180) {
		plotted = false;
		if (fi == 0) {
			setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
		}
		else {
			setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
		}
		for (p = 0.; p <= 2. * PI; p += PI / 24.) {
			x = RADIUS * cos(p) * cos(fi);
			y = RADIUS * cos(p) * sin(fi);
			z = RADIUS * sin(p);
			rotate3d(pDC, xr, yr, zr, &x, &y, &z);
			if (x < 0.)
				plotted = false;
			else
				graph(pDC, y, z, &plotted);
		}
	}
}

void CGraphicMFCKDYView::example89(CDC* pDC)
{
	CString str = L"";
	unsigned s;
	void* b1, * b2, * b3, * b4, * b5, * b6;
	char title[][30] = { "FLAG","View Nam","Cuba","Iraq","Chile","Panama","China",
						"Yugoslavia","Turkey","USA" };
	s = imagesize(245, 150, 395, 250);
	b1 = malloc(s);
	b2 = malloc(s);
	b3 = malloc(s);
	b4 = malloc(s);
	b5 = malloc(s);
	b6 = malloc(s);
	setfillstyle(pDC, INTERLEAVE_FILL, LIGHTGRAY);
	bar(pDC, 0, 0, 639, 479);
	str = CString(title[1]);
	gwindow_example82(pDC, 150, 65, 490, 320, WHITE, str); vietnam(pDC);
	str = CString(title[2]);
		getimage(pDC, 245, 150, 395, 250, b1);
	gwindow_example82(pDC, 150, 65, 490, 320, WHITE, str); cuba(pDC);
	str = CString(title[3]);
		getimage(pDC, 245, 150, 395, 250, b2);
	gwindow_example82(pDC, 150, 65, 490, 320, WHITE, str); iraq(pDC);
//	getimage(pDC, 245, 150, 395, 250, b3);
	str = CString(title[4]);
	gwindow_example82(pDC, 150, 65, 490, 320, WHITE, str); chile(pDC);
		getimage(pDC, 245, 150, 395, 250, b4);
	str = CString(title[5]);
	gwindow_example82(pDC, 150, 65, 490, 320, WHITE, str); panama(pDC);
		getimage(pDC, 245, 150, 395, 250, b5);
		str = CString(title[6]);
	gwindow_example82(pDC, 150, 65, 490, 320, WHITE, str); china(pDC);
		getimage(pDC, 245, 150, 395, 250, b6);
	str = CString(title[7]);
	gwindow_example82(pDC, 150, 65, 490, 320, WHITE, str); yugo(pDC);
	str = CString(title[8]);
	gwindow_example82(pDC, 150, 65, 490, 320, WHITE, str); turkey(pDC);
		getimage(pDC, 245, 150, 395, 250, b3);
	str = CString(title[9]);
	gwindow_example82(pDC, 150, 65, 490, 320, WHITE, str); usa(pDC);
	
	putimage(pDC, 50, 0, b1, COPY_CUT);
	putimage(pDC, 439, 0, b2, COPY_CUT);
	putimage(pDC, 50, 160, b3, COPY_CUT);
	putimage(pDC, 439, 160, b4, COPY_CUT);
	putimage(pDC, 50, 320, b5, COPY_CUT);
	putimage(pDC, 439, 320, b6, COPY_CUT);
	free(b1);
	free(b2);
	free(b3);
	free(b4);
	free(b5);
	free(b6);

}

void CGraphicMFCKDYView::example90(CDC* pDC)
{
	CString str = L"";
	int i = 0;
	textcolor(pDC, WHITE);
	setfillstyle(pDC, HATCH_FILL, WHITE); //color, BLUE -> WHITE
	bar(pDC,0, 0, 639, 479);
	setwritemode(pDC, XOR_PUT);
	setcolor(pDC, GREEN);
	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	line(pDC, 320, 150, 220, 250);
	line(pDC, 220, 250, 420, 250);
	line(pDC, 420, 250, 320, 150);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 2);
	outtextxy(pDC, 0, 50, L"press any key to become triangle bigger!");
//	_getch();
//	clearDevice(pDC);
	
	/*
	line(pDC, 320, 150, 220, 250);
	line(pDC, 220, 250, 420, 250);
	line(pDC, 420, 250, 320, 150);
	setlinestyle(pDC, DOTTED_LINE, 0, NORM_WIDTH);
	outtextxy(pDC, 100, 50, L"press any key to stop triangle!");
	*/
	
	//kbhit()는 키입력이 있는 경우에만 1 아니면 0이다.
	while (_kbhit() == 1) {
//	while (i <= 10) {
		line(pDC, 320, 150, 420 + 2 * i, 250 + i);
		line(pDC, 220, 250, 420 + 2 * i, 250 + i);
		delay(100);
		line(pDC, 320, 150, 420 + 2 * i, 250 + i);
		line(pDC, 220, 250, 420 + 2 * i, 250 + i);
		++i;
	}
//	clearDevice(pDC);
	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	line(pDC, 320, 150, 220, 250);
	line(pDC, 320, 150, 420 + 2 * i, 250 + i);
	line(pDC, 220, 250, 420 + 2 * i, 250 + i);
	
}

void CGraphicMFCKDYView::setwritemode(CDC* pDC, int mode)
{
	//작도선 판단을 현재 구현하기에 어려움이 따름
}


void CGraphicMFCKDYView::textcolor(CDC* pDC,int color)
{
	setcolor(pDC, color);
}

int imagesize(int left, int top, int right, int bottom)
{
	double value = 408.28;
	int width, height, area, totalSize;
	width = right - left;
	height = bottom - top;
	area = width * height; //넓이
	totalSize = round(area * value);
	if (totalSize < 65536)
		return totalSize;
	else
		return -1;
}

void CGraphicMFCKDYView::getimage(CDC* pDC, int left, int top, int right, int bottom, void* bitmap)
{
	CBitmap screen_bitmap,*pOldBitmap;
	screen_bitmap.CreateCompatibleBitmap(pDC, (right - left), (bottom - top));

	pOldBitmap = pDC->SelectObject(&screen_bitmap);
	pDC->StretchBlt(left, top, right, bottom, pDC, left, top, right, bottom, SRCCOPY);
}

void CGraphicMFCKDYView::putimage(CDC* pDC, int left, int top, void* bitmap, int op)
{
	
}

void CGraphicMFCKDYView::star2_example89(CDC* pDC, int x0, int y0, int r, double a, int c)
{
	int i, p[12];
	double s, ph;
	setcolor(pDC, c);
	setfillstyle(pDC, SOLID_FILL, c);
	s = 4 * PI / 5;
	ph = PI / 2;
	for (i = 0; i < 5; i++) {
		p[2 * i] = x0 + (int)(r * cos(i * s + ph));
		p[2 * i+1] = y0 + (int)(r * sin(i * s + ph));
	}
	p[10] = p[0];
	p[11] = p[1];
	fillPoly(pDC, 6, p);
	pDC->FloodFill(x0, y0, changeBookColorToMFCColor(GREEN));
}

void CGraphicMFCKDYView::graph(CDC* pDC, double y, double z, int* plotted)
{
	int xx, yy;
	xx = getmaxx() / 2 + (int)y;
	yy = getmaxy() / 2 - (int)z;
	if (*plotted == false)
		pDC->MoveTo(xx, yy);
	else
		pDC->LineTo(xx, yy);
	*plotted = true;
}


void CGraphicMFCKDYView::rotate3d(CDC* pDC, double xr, double yr, double zr,
	double* px, double* py, double* pz)
{
	double x, y, z;
	x = (*px) * cos(zr) - (*py) * sin(zr);
	y = (*px) * sin(zr) + (*py) * cos(zr);
	z = x * sin(yr) + (*pz) * cos(yr);
	*px = x * cos(yr) - (*pz) * sin(yr);
	*py = y * cos(xr) - z * sin(xr);
	*pz = y * sin(xr) + z * cos(xr);
}

void CGraphicMFCKDYView::gwindow_example82(CDC* pDC, int x1, int y1, int x2, int y2, int color, CString str)
{
	int text_width;
	char line_pattern[] = { 0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff };
	setfillstyle(pDC, SOLID_FILL, WHITE);
	bar(pDC, x1 - 2, y1 - 2, x2 + 2, y2 + 2);
	setfillstyle(pDC, SOLID_FILL, color);
	bar(pDC, x1, y1 + 1, x2, y1 + 2);
	
	text_width = textwidth_example49(str);
	setfillpattern(pDC, line_pattern, color);
	bar(pDC,x1 + 5, y1 + 2, (x1 + x2) / 2 - 20 - text_width / 2, y1 + 19);
	bar(pDC, (x1 + x2) / 2 + text_width / 2 + 20, y1 + 2, x2 - 5, y1 + 19);
//	setcolor(pDC, color);
//	rectangle(pDC, x1, y1, x2, y2);
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	setcolor(pDC, BLACK);
	outtextxy(pDC, (x1 + x2) / 2, y1, str);
	outtextxy(pDC, (x1 + x2) / 2 + 1, y1, str);
}
double CGraphicMFCKDYView::sync(double x, double y)
{
	double f;
	f = hypot(x, y) / 35;
	if (fabs(f) < 1.e-5)
		return (40. * PI);
	else
		return (40. * sin(f * PI) / f);
}

void CGraphicMFCKDYView::change_palette_b2(CDC* pDC)
{
	CPalette* c_pal = 0;
	getpallette(pDC, c_pal);
	setrgbpalette(pDC, 11, 0, 0, 63);
	setrgbpalette(pDC, 12, 20, 20, 63);
	setrgbpalette(pDC, 13, 30, 30, 63);
	setrgbpalette(pDC, 14, 40, 40, 63);
	setrgbpalette(pDC, 15, 50, 50, 63);
}
void CGraphicMFCKDYView::s_bar_example81(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 10;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 + d, y1 + d, x2 + d, y2 + d);
	setfillstyle(pDC, SOLID_FILL, c);
	bar(pDC, x1, y1, x2, y2);
	rectangle(pDC, x1, y1, x2, y2);
}
void CGraphicMFCKDYView::h_char2(CDC* pDC, int x, int y, int c, CString str)
{
	setcolor(pDC, WHITE);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(pDC, x-1, y, str);
	outtextxy(pDC, x+1, y, str);
	outtextxy(pDC, x, y-1, str);
	outtextxy(pDC, x, y+1, str);
	setcolor(pDC, c);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(pDC, x, y, str);
}
void CGraphicMFCKDYView::fc_circle(CDC* pDC, int x0, int y0, int r, int c)
{
	setcolor(pDC, c);
	setfillstyle(pDC, SOLID_FILL, c);
	pieslice(pDC, x0, y0, 0, 360, r);
}
void CGraphicMFCKDYView::relief_char_example81(CDC* pDC, int x, int y, int sc, int bc, int fc, int font,
	int dire, int size, CString str)
{
	settextstyle(pDC, font, dire, size);
	setcolor(pDC, bc);
	outtextxy(pDC, x + 1, y + 1, str);
	setcolor(pDC, sc);
	outtextxy(pDC, x - 1, y - 1, str);
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);

}
void CGraphicMFCKDYView::radar1(CDC* pDC, int n, int x0, int y0, int r, int c, char* s[])
{
	CString str = L"";
	int i, x1, y1;
	double alpha;
	setcolor(pDC, c);
	/*
	for (i = 1; i <= 5; i++)
		circle(pDC, x0, y0, i * r / 5);
		*/

	alpha = 2 * PI / n;
	for (i = 0; i <= n - 1; i++) {
		x1 = x0 + (int)(r * cos(i * alpha - PI / 2));
		y1 = y0 + (int)(r * sin(i * alpha - PI / 2));
		line(pDC, x0, y0, x1, y1);
	}
	for (i = 0; i <= n - 1; i++) {
		x1 = x0 + (int((r + 36) * cos(i * alpha - PI / 2)));
		y1 = y0 + (int((r + 36) * sin(i * alpha - PI / 2)));
		if (x1 <= 200)
			x1 -= 50;
		str = CString(s[i]);
		relief_char_example81(pDC, x1, y1, WHITE, BLACK, LIGHTGRAY, TRIPLEX_FONT, HORIZ_DIR, 1, str);
	}
}
void CGraphicMFCKDYView::radar_data(CDC* pDC, int n, int x0, int y0, int c, int d[])
{
	int i, x1[10] = { 0 }, y1[10] = { 0 };
	double alpha = 2 * PI / n, pi2 = PI / 2;
	setcolor(pDC, c);
	for (i = 0; i <= n - 1; i++) {
		d[i] = (int(d[i] * 1.25));
		x1[i] = x0 + (int)(d[i] * cos(i * alpha - pi2));
		y1[i] = y0 + (int)(d[i] * sin(i * alpha - pi2));
		if (i == 0)
			continue;
		line(pDC, x1[i - 1], y1[i - 1], x1[i], y1[i]);
	}
	line(pDC, x1[0], y1[0], x1[n - 1], y1[n - 1]);
}

void CGraphicMFCKDYView::change_palette_g_example80(CDC* pDC)
{
	int i;
	CPalette* c_pal = 0;
	getpallette(pDC, c_pal);
	for (i = 7; i <= 14; i++) {
		setrgbpalette(pDC, i, (i - 7) * 8, 60, (i - 7) * 8);
	}
	setrgbpalette(pDC, 16, 60, 60, 60);
}

void CGraphicMFCKDYView::s_bar_example80(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 10;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 + d, y1 + d, x2 + d, y2 + d);
	setfillstyle(pDC, SOLID_FILL, c);
	bar(pDC, x1, y1, x2, y2);
//	setcolor(pDC, BLACK);
//	rectangle(pDC, x1, y1, x2, y2);
}

void CGraphicMFCKDYView::h_char_example80(CDC* pDC, int x, int y, int c, CString str)
{
	setcolor(pDC, BLACK);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 2);
	outtextxy(pDC, x-1, y, str);
	outtextxy(pDC, x+1, y, str);
	outtextxy(pDC, x, y-1, str);
	outtextxy(pDC, x, y+1, str);
	setcolor(pDC, c);
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::s_bar_example79(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 10;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 + d, y1 + d, x2 + d, y2 + d);
	setfillstyle(pDC, SOLID_FILL, c);
	bar(pDC, x1, y1, x2, y2);
	setcolor(pDC, BLACK);
	rectangle(pDC, x1, y1, x2, y2);
}
void CGraphicMFCKDYView::h_jchar(CDC* pDC, int x, int y, int c, CString str)
{
	setcolor(pDC, BLACK);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(pDC, x-1, y, str);
	outtextxy(pDC, x+1, y, str);
	outtextxy(pDC, x, y-1, str);
	outtextxy(pDC, x, y+1, str);
	setcolor(pDC, c);
	outtextxy(pDC, x, y, str);
}
void CGraphicMFCKDYView::cframe_example79(CDC* pDC, int x, int y, int x_d, int y_d, int d, int bc, int fc, int sc)
{
	int f1[14], f2[14];
	f1[0] = x + x_d;
	f1[1] = y;
	f1[2] = x + x_d;
	f1[3] = y + y_d;
	f1[4] = x;
	f1[5] = y + y_d;
	f1[6] = x + d;
	f1[7] = y + y_d - d;
	f1[8] = x + x_d - d;
	f1[9] = y + y_d - d;
	f1[10] = x + x_d - d;
	f1[11] = y + d;
	f1[12] = x + x_d;
	f1[13] = y;

	f2[0] = x + x_d;
	f2[1] = y;
	f2[2] = x;
	f2[3] = y;
	f2[4] = x;
	f2[5] = y + y_d;
	f2[6] = x + d;
	f2[7] = y + y_d - d;
	f2[8] = x + d;
	f2[9] = y + d;
	f2[10] = x + x_d - d;
	f2[11] = y + d;
	f2[12] = x + x_d;
	f2[13] = y;
	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(pDC, SOLID_FILL, fc);
	bar(pDC, x + d, y + d, x + x_d - d, y + y_d - d);
	setcolor(pDC, sc);
	setfillstyle(pDC, SOLID_FILL, sc);
	fillPoly(pDC, 7, f1);
	setcolor(pDC, bc);
	setfillstyle(pDC, SOLID_FILL, bc);
	fillPoly(pDC, 7, f2);
	setcolor(pDC, fc);
	line(pDC, x + x_d - d, y + y_d - d, x + x_d, y + y_d);
	line(pDC, x, y, x + d, y + d);
}

void CGraphicMFCKDYView::s_bar_example78(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 10;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 + d, y1 + d, x2 + d, y2 + d);
	setfillstyle(pDC, SOLID_FILL, c);
	bar(pDC, x1, y1, x2, y2);
}
void CGraphicMFCKDYView::g_bar1_example78(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 10;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1, y1 + d, x2 + d, y2 + d);
	cframe(pDC, x1, y1, x2 - x1, y2 - y1, 2, BLACK, c + 8, c);	//bc, WHITE -> BLACK으로 대체
}
void CGraphicMFCKDYView::h_char1_example78(CDC* pDC, int x, int y, int c, CString str)
{
	setcolor(pDC, BLACK);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 4);
	outtextxy(pDC, x-1, y, str);
	outtextxy(pDC, x+1, y, str);
	outtextxy(pDC, x, y-1, str);
	outtextxy(pDC, x, y+1, str);
	setcolor(pDC, c);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 4);
	outtextxy(pDC, x, y, str);
}
void CGraphicMFCKDYView::cframe_example78(CDC* pDC, int x, int y, int x_d, int y_d, int d, int bc, int fc, int sc)
{
	int f1[14], f2[14];
	f1[0] = x + x_d;
	f1[1] = y;
	f1[2] = x + x_d;
	f1[3] = y + y_d;
	f1[4] = x;
	f1[5] = y + y_d;
	f1[6] = x + d;
	f1[7] = y + y_d - d;
	f1[8] = x + x_d - d;
	f1[9] = y + y_d - d;
	f1[10] = x + x_d - d;
	f1[11] = y + d;
	f1[12] = x + x_d;
	f1[13] = y;
	f2[0] = x + x_d;
	f2[1] = y;
	f2[2] = x;
	f2[3] = y;
	f2[4] = x;
	f2[5] = y + y_d;
	f2[6] = x + d;
	f2[7] = y + y_d - d;
	f2[8] = x + d;
	f2[9] = y + d;
	f2[10] = x + x_d - d;
	f2[11] = y + d;
	f2[12] = x + x_d;
	f2[13] = y;

	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(pDC, SOLID_FILL, fc);
	bar(pDC, x + d, y + d, x + x_d - d, y + y_d - d);
	setcolor(pDC, sc);
	setfillstyle(pDC, SOLID_FILL, sc);
	fillPoly(pDC, 7, f1);
	setcolor(pDC,bc);
	setfillstyle(pDC, SOLID_FILL, bc);
	fillPoly(pDC, 7, f2);
	setcolor(pDC, fc);
	line(pDC, x + x_d - d, y + y_d - d, x + x_d, y + y_d);
	line(pDC, x, y, x + d, y + d);
}

void CGraphicMFCKDYView::change_palette_r(CDC* pDC)
{
	CPalette* c_pal = 0;
	getpallette(pDC, c_pal);
	setrgbpalette(pDC, 11, 60, 0, 0);
	setrgbpalette(pDC, 12, 60, 30, 30);
	setrgbpalette(pDC, 13, 60, 39, 39);
	setrgbpalette(pDC, 14, 60, 48, 48);
	setrgbpalette(pDC, 15, 60, 55, 55);
}
void CGraphicMFCKDYView::s_bar_example77(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 10;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 + d, y1 + d, x2 + d, y2 + d);
	setfillstyle(pDC, SOLID_FILL, c);
	bar(pDC, x1, y1, x2, y2);
	setcolor(pDC, BLACK);
	rectangle(pDC, x1, y1, x2, y2);
}
void CGraphicMFCKDYView::g_bar1(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 0;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 + d, y1 - d, x2 + d, y2);
	setfillstyle(pDC, SOLID_FILL, c);
	bar(pDC, x1, y1, x2, y2);
}
void CGraphicMFCKDYView::c_bar1(CDC* pDC, int data[], int num, int full_scale)
{
	for (int i = 0; i <= num - 1; i++)
		g_bar1(pDC,150 + i * 100, 350 - data[i] * 250 / full_scale, 200 + i * 100, 350, i + 2);
}
void CGraphicMFCKDYView::h_char1(CDC* pDC, int x, int y, int c, CString str)
{
	setcolor(pDC, BLACK);	//color, WHITE(배경색) -> BLACK으로 변경
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(pDC, x - 1, y, str);
	outtextxy(pDC, x + 1, y, str);
	outtextxy(pDC, x, y-1, str);
	outtextxy(pDC, x, y+1, str);
	setcolor(pDC, c);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::relief_char(CDC* pDC, int x, int y, int sc, int bc, int fc,
	int font, int dire, int size, CString str)
{
	settextstyle(pDC, font, dire, size);
	setcolor(pDC, bc);
	outtextxy(pDC, x + 1, y + 1, str);
	setcolor(pDC, sc);
	outtextxy(pDC, x - 1, y - 1, str);
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::relief_line(CDC* pDC, int x0, int y0, int x1, int y1, int sc, int bc, int fc)
{
	setcolor(pDC, bc);
	line(pDC, x0 + 1, y0 + 1, x1 + 1, y1 + 1);
	setcolor(pDC, sc);
	line(pDC, x0 - 1, y0 - 1, x1 - 1, y1 - 1);
	setcolor(pDC, fc);
	line(pDC, x0, y0, x1, y1);
}

void CGraphicMFCKDYView::s_bar_example76(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 10;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 + d, y1 + d, x2 + d, y2 + d);
	setfillstyle(pDC, SOLID_FILL, c);
	bar(pDC, x1, y1, x2, y2);
}

void CGraphicMFCKDYView::mac_frame2(CDC* pDC, int x, int y, int x_d, int y_d, int d, int fc)
{
	int frame[14];
	frame[0] = x + x_d;
	frame[1] = y;
	frame[2] = x+x_d;
	frame[3] = y+y_d+1;
	frame[4] = x;
	frame[5] = y+y_d+1;
	frame[6] = x+d;
	frame[7] = y+y_d-d;
	frame[8] = x+x_d-d;
	frame[9] = y+y_d-d;
	frame[10] = x+x_d-d;
	frame[11] = y+d;
	frame[12] = x+x_d;
	frame[13] = y;

	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x, y, x + x_d, y + y_d);
	setfillstyle(pDC, SOLID_FILL, fc);
	bar(pDC, x + d, y + d, x + x_d - d, y + y_d - d);
	setfillstyle(pDC, SOLID_FILL, RED);	//color, WHITE -> RED로 대체
	fillPoly(pDC, 7, frame);
	setcolor(pDC, fc);
	line(pDC, x + x_d - d, y + y_d - d, x + x_d, y + y_d);
}

void CGraphicMFCKDYView::bold_line(CDC* pDC, float data[], int num, int c)
{
	int i, j;
	for (i = 0; i <= num - 1; i++)
		data[i] *= 50.0;
	setcolor(pDC, c);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	for (j = 0; j <= 3; j += 3) {
		pDC->MoveTo(150, 300 + j - (int)data[0]);
		for (i = 1; i <= num - 1; i++)
			lineto(pDC,150 + i * 50, 300 + j - (int)data[i]);
	}
}

void CGraphicMFCKDYView::change_palette_g1(CDC* pDC)
{
	CPalette* c_pal = 0;
	getpallette(pDC, c_pal);
	setrgbpalette(pDC, 11, 0, 60, 0);
	setrgbpalette(pDC, 12, 25, 60, 25);
	setrgbpalette(pDC, 13, 37, 60, 37);
	setrgbpalette(pDC, 14, 47, 60, 47);
	setrgbpalette(pDC, 15, 55, 60, 55);
}

void CGraphicMFCKDYView::s_bar_example75(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 10;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 + d, y1 + d, x2 + d, y2 + d);
	setfillstyle(pDC, SOLID_FILL, c);
	bar(pDC, x1, y1, x2, y2);
	setcolor(pDC, BLACK);
	rectangle(pDC, x1, y1, x2, y2);
}

void CGraphicMFCKDYView::h_char_example75(CDC* pDC, int x, int y, int c, CString str)
{
	setcolor(pDC, BLACK);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(pDC, x - 1, y, str);
	outtextxy(pDC, x + 1, y, str);
	outtextxy(pDC, x, y - 1, str);
	outtextxy(pDC, x, y + 1, str);
	setcolor(pDC, c);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(pDC, x, y, str);

}

void CGraphicMFCKDYView::c_line_example75(CDC* pDC, int data[], int num, int c)
{
	int i, j;
	for (i = 0; i <= num - 1; i++)
		data[i] = (int)(data[i] * 5.0 / 3.0);
	setcolor(pDC, c);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	for (j = 0; j <= 3; j++) {
		pDC->MoveTo(150, 350 + j - data[0]);
		for (i = 1; i <= num - 1; i++)
			pDC->LineTo(150 + i * 100, 350 + j - data[i]);
	}
	setcolor(pDC, BLACK);
	setfillstyle(pDC, SOLID_FILL, BLACK);
	for (i = 0; i <= num - 1; i++)
		pieslice(pDC, 150 + i * 100, 350 + 3 - data[i], 0, 360, 4);
}

void CGraphicMFCKDYView::c_bar3d(CDC* pDC, int x1, int y1, int x2, int y2, int d, int c, int ct, int cs)
{
	int s = SOLID_FILL;
	setfillstyle(pDC, s, c);
	bar3d(pDC, x1, y1, x2, y2, d, 1);
	setfillstyle(pDC, s, ct);
//	ExtFloodFill(pDC->m_hDC, ((x1+x2)/2), y1-1, getcolor(), FLOODFILLSURFACE);
//	pDC->FloodFill(((x1+x2)/2), y1 - 1, getcolor());
//	pDC->ExtFloodFill(((x1 + x2) / 2), y1 - 1, getcolor(),FLOODFILLSURFACE);
	setfillstyle(pDC, s, cs);
//	ExtFloodFill(pDC->m_hDC, x2+1, (y1+y2)/2, getcolor(), FLOODFILLSURFACE);
//	pDC->FloodFill(x2 + 1, (y1+y2)/2, getcolor());
}

void CGraphicMFCKDYView::s_bar(CDC* pDC, int x1, int y1, int x2, int y2, int c)
{
	int d = 10;
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 + d, y1 + d, x2 + d, y2 + d);
	setfillstyle(pDC, SOLID_FILL, c);
	bar(pDC, x1, y1, x2, y2);
	rectangle(pDC, x1, y1, x2, y2);
}

void CGraphicMFCKDYView::h_char(CDC* pDC, int x, int y, int c, CString str)
{
	setcolor(pDC, BLACK);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(pDC, x-1, y, str);
	outtextxy(pDC, x+1, y, str);
	outtextxy(pDC, x, y-1, str);
	outtextxy(pDC, x, y+1, str);
	setcolor(pDC, c);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(pDC, x, y, str);
}
void CGraphicMFCKDYView::c_line(CDC* pDC, int data[], int c)
{
	int i = 0;
	setcolor(pDC, c);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	pDC->MoveTo(200, 350 - data[0]);
	for (i = 1; i <= 3; i++) {
//		pDC->LineTo(200 + i * 100, 350 - data[i]);
		lineto(pDC, 200 + i * 100, 350 - data[i]);
	}

	setcolor(pDC, BLACK);
	setfillstyle(pDC, SOLID_FILL, BLACK);
	for (i = 0; i <= 3; i++)
		pieslice(pDC, 200 + i * 100, 350 + 3 - data[i], 0, 360, 4);
}

void CGraphicMFCKDYView::hollow_char0(CDC* pDC, int x, int y, int font, int color, CString str, int xd, int yd)
{
	int i, j;
	settextstyle(pDC, font, HORIZ_DIR, 4);
	setcolor(pDC, color);
	for (i = -xd; i <= xd; i++) {
		for (j = -yd; j <= yd; j++)
			outtextxy(pDC, x + i, y + j, str);
	}
	setcolor(pDC, pDC->GetBkColor());
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::char1(CDC* pDC, int x, int y, int dc, int fc, int font, int size, CString str)
{
	settextstyle(pDC, font, HORIZ_DIR, size);
	setcolor(pDC, dc);
	outtextxy(pDC, x - 1, y, str);
	outtextxy(pDC, x + 1, y, str);
	outtextxy(pDC, x, y - 1, str);
	outtextxy(pDC, x, y + 1, str);
	setcolor(pDC,fc);
	outtextxy(pDC,x, y, str);
}
void CGraphicMFCKDYView::char2(CDC* pDC, int x, int y, int dc, int bc, int fc, int font, int size, CString str)
{
	settextstyle(pDC, font, HORIZ_DIR, size);
	setcolor(pDC, bc);
	outtextxy(pDC, x +2, y+1, str);
	outtextxy(pDC, x+3, y+2, str);
	outtextxy(pDC, x+4, y+3, str);
	setcolor(pDC, dc);
	outtextxy(pDC, x-1, y, str);
	outtextxy(pDC, x+1, y, str);
	outtextxy(pDC, x, y-1, str);
	outtextxy(pDC, x, y+1, str);
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}
void CGraphicMFCKDYView::char3(CDC* pDC, int x, int y, int sc, int bc, int fc, int font, int size, CString str)
{
	settextstyle(pDC, font, HORIZ_DIR, size);
	setcolor(pDC, bc);
	outtextxy(pDC, x + 1, y, str);
	outtextxy(pDC, x + 2, y, str);
	setcolor(pDC, sc);
	outtextxy(pDC, x - 1, y, str);
	outtextxy(pDC, x - 2, y, str);
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}
void CGraphicMFCKDYView::char4(CDC* pDC, int x, int y, int sc, int bc, int fc, int font, int size, CString str)
{
	settextstyle(pDC, font, HORIZ_DIR, size);
	setcolor(pDC, bc);
	outtextxy(pDC, x + 1, y, str);
	setcolor(pDC, sc);
	outtextxy(pDC, x - 1, y, str);
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}
void CGraphicMFCKDYView::char5(CDC* pDC, int x, int y, int sc, int bc, int fc, int font, int size, CString str)
{
	settextstyle(pDC, font, HORIZ_DIR, size);
	setcolor(pDC, bc);
	outtextxy(pDC, x + 1, y, str);
	outtextxy(pDC, x + 2, y, str);
	setcolor(pDC, sc);
	outtextxy(pDC, x - 1, y, str);
	outtextxy(pDC, x - 2, y, str);
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::hollow_char1(CDC* pDC, int x, int y, int dc, int fc, int font, int size, CString str)
{
	settextstyle(pDC, font, HORIZ_DIR, size);
	setcolor(pDC, dc);
	outtextxy(pDC, x - 1, y, str);
	outtextxy(pDC, x + 1, y, str);
	outtextxy(pDC, x, y - 1, str);
	outtextxy(pDC, x, y + 1, str);
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::shadow_char3(CDC* pDC, int x, int y, int fc, int font, int size, CString str, int d)
{
	int i, j, k;
	settextstyle(pDC, font, HORIZ_DIR, size);
	for (i = 4; i <= 15; i++) {
		setcolor(pDC, i);
		k = (16 - i) * d + 1;
		for (j = d; j >= 1; j--)
			outtextxy(pDC, x + k--, y + k--, str);
	}
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::change_palette(CDC* pDC)
{
	CPalette* c_pal = 0;
	int i;
	getpallette(pDC, c_pal);
	for (i = 4; i <= 15; i++) {
		setrgbpalette(pDC, i, i * 4, i * 4, i * 4);
	}
	setrgbpalette(pDC, 2, 63, 0, 0);
	setrgbpalette(pDC, 3, 0, 63, 0);
	setrgbpalette(pDC, 4, 0, 0, 63);
}

void CGraphicMFCKDYView::shadow_char2(CDC* pDC, int x, int y, int fc, int font, int size, CString str, int d)
{
	int i;
	settextstyle(pDC, font, HORIZ_DIR, size);
	for (i = d; i >= 1; i--) {
		setcolor(pDC, 16 - i);
		outtextxy(pDC, x + i, y + i, str);
	}
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::setrgbpalette(CDC* pDC, int palette_num, int r, int g, int b)
{
	CPalette c_pal,*oldPalette;
	LPLOGPALETTE pLogPal = (LPLOGPALETTE)new char[sizeof(LOGPALETTE) + sizeof(PALETTEENTRY)*256];
	PALETTEENTRY pal_entry;
	
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = 256;
	pLogPal->palPalEntry[0].peBlue = b;
	pLogPal->palPalEntry[0].peGreen = g;
	pLogPal->palPalEntry[0].peRed = r;
	c_pal.CreatePalette(pLogPal);
	oldPalette = pDC->SelectPalette(&c_pal, 0);
	pDC->RealizePalette();
}

void CGraphicMFCKDYView::getpallette(CDC* pDC, CPalette* c_pal)
{
	c_pal = pDC->GetCurrentPalette();
}

void CGraphicMFCKDYView::change_palette_g(CDC* pDC)
{
	CPalette* c_pal = 0;
	int i = 0;
	getpallette(pDC, c_pal);
	for (i = 7; i <= 14; i++)
		setrgbpalette(pDC, i, (i - 7) * 8, (i - 7) * 8, (i - 7) * 8);
	setrgbpalette(pDC, 16, 60, 60, 60);
}

void CGraphicMFCKDYView::shadow_char1(CDC* pDC, int x, int y, int sc, int fc, int font, int size, CString str, int d)
{
	int i;
	settextstyle(pDC, font, HORIZ_DIR, size);
	setcolor(pDC, sc);
	for (i = 1; i <= d; i++)
		outtextxy(pDC, x + i, y + i, str);
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::shadow_char(CDC* pDC, int x, int y, int sc, int fc, int font, int size, CString str, int d)
{
	int i;
	settextstyle(pDC, font, HORIZ_DIR, size);
	setcolor(pDC, sc);
	for (i = 1; i <= d; i++)
		outtextxy(pDC, x + i, y + i, str);
	setcolor(pDC, fc);
	outtextxy(pDC, x, y, str);
}

void CGraphicMFCKDYView::reverse_char(CDC* pDC,int left,int top,int color, CString str)
{
	int trimming = 2;
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	setfillstyle(pDC, SOLID_FILL, color);
	bar(pDC, left - trimming, top - trimming, left + textwidth_example49(str) + trimming,
		top + textheight(str) * 3 / 2 + trimming);
	setcolor(pDC, changeMFCColorToBookColor(pDC->GetBkColor()));
	outtextxy(pDC, left + textwidth_example49(str) / 2, top + textheight(str) * 3 / 4, str);
}

void CGraphicMFCKDYView::line_char_example65(CDC* pDC, int x, int y, int font,
	int size, int color, CString str)
{
	int i, h, w, d = 2;
	setcolor(pDC, color);
	settextstyle(pDC, font, HORIZ_DIR, size);
	h = textheight(str) / 10;
	w = textwidth_example49(str);
	outtextxy(pDC, x, y, str);
	outtextxy(pDC, x + 1, y, str);
	outtextxy(pDC, x + 2, y, str);
	setfillstyle(pDC, SOLID_FILL, pDC->GetBkColor());
	for (i = 4 * h; i <= 10 * h; i += h)
		bar(pDC, x, y + i, x + w, y + i + h / 5);
}

void CGraphicMFCKDYView::line_char_example64(CDC* pDC, int x, int y, int font,
	int size, int color, CString str)
{
	int i, h, w, d = 2;
	setcolor(pDC, color);
	settextstyle(pDC, font, HORIZ_DIR, size);
	h = textheight(str) / 12;
	w = textwidth_example49(str);
	outtextxy(pDC, x, y, str);
	outtextxy(pDC, x+1, y, str);
	outtextxy(pDC, x+2, y, str);
	setfillstyle(pDC, SOLID_FILL, pDC->GetBkColor());
	for (i = 9 * h; i <= 13 * h; i += h)
		bar(pDC, x, y + i, x + w, y + i + h / 2);
}


void CGraphicMFCKDYView::line_char(CDC* pDC, int x, int y, int font,
	int size, int color, CString str)
{
	int i, h, w, d = 2;
	setcolor(pDC, color);
	settextstyle(pDC, font, HORIZ_DIR, size);
	h = textheight(str) * 0.6;
	w = textwidth_example49(str);
	outtextxy(pDC, x, y, str);
	outtextxy(pDC, x + 1, y, str);
	outtextxy(pDC, x + 2, y, str);
	setfillstyle(pDC, SOLID_FILL, WHITE);	//color, WHITE -> RED로 대체
	setcolor(pDC, pDC->GetBkColor());
	bar(pDC, x, y + h, x + w, y + h + d);
}

void CGraphicMFCKDYView::bold_char(CDC* pDC, int x, int y, int font,
	int color, CString str, int xd, int yd)
{
	int i, j;
	setcolor(pDC, color);
	settextstyle(pDC, font, HORIZ_DIR, 0);
	for (i = 0; i <= xd; i++)
		for (j = 0; j <= yd; j++)
			outtextxy(pDC, x + i, y + j, str);
}

void CGraphicMFCKDYView::bold_char1(CDC* pDC, int x, int y, int font, int color, CString str)
{
	setcolor(pDC, color);
	settextstyle(pDC, font, HORIZ_DIR, 0);
	outtextxy(pDC, x, y, str);
	outtextxy(pDC,x + 1, y, str);
}
void CGraphicMFCKDYView::bold_char2(CDC* pDC, int x, int y, int font, int color, CString str)
{
	setcolor(pDC, color);
	settextstyle(pDC, font, HORIZ_DIR, 0);
	outtextxy(pDC, x, y, str);
	outtextxy(pDC, x+1, y, str);
	outtextxy(pDC, x + 2, y, str);
}
void CGraphicMFCKDYView::bold_char3(CDC* pDC, int x, int y, int font, int color, CString str)
{
	setcolor(pDC, color);
	settextstyle(pDC, font, HORIZ_DIR, 0);
	outtextxy(pDC, x, y, str);
	outtextxy(pDC, x + 1, y, str);
	outtextxy(pDC, x + 2, y, str);
	outtextxy(pDC, x + 3, y, str);
}

void CGraphicMFCKDYView::char_in_box5(CDC* pDC, int left, int top,int font, int color,int size, CString str)
{
	int trimming = 10;
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	settextstyle(pDC, font, HORIZ_DIR, size);
	setcolor(pDC, BLACK);
	setfillstyle(pDC, SOLID_FILL, color);
//	bar3d(pDC, left - trimming, top - trimming, left + textwidth_example49(str) + trimming, top + textheight(str) * 1.5 + trimming, 0, 0);
	bar(pDC, left - trimming,
		top - trimming + 50,
		left + textwidth_example49(str) + trimming + 100,
		top + textheight(str) * 1.5 + trimming);
//	setcolor(pDC, changeMFCColorToBookColor(pDC->GetBkColor()));
	setcolor(pDC, changeMFCColorToBookColor(BLACK));
	outtextxy(pDC, left + textwidth_example49(str) + 4, top + textheight(str) * 3 / 4, str);
}

void CGraphicMFCKDYView::char_in_box1(CDC* pDC, int left, int top, int right, int bottom, CString str)
{
	setcolor(pDC,BROWN);
//	setusercharsize(pDC, 1, 1, 1, 1);
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	rectangle(pDC, left, top, right, bottom);
	settextstyle(pDC, 9, HORIZ_DIR, 3); // TRIPLEX_FONT -> 9로 대체
//	setusercharsize(pDC, right - left, textwidth_example49(str),bottom-top,textheight(str));
	setcolor(pDC, GREEN);
	outtextxy(pDC, (left + right) / 2, (top + bottom) / 3, str);
}
void CGraphicMFCKDYView::char_in_box2(CDC* pDC, int left, int top, int right, int bottom, CString str)
{
	setcolor(pDC, BROWN);
//	setusercharsize(pDC, 1, 1, 1, 1);
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	rectangle(pDC, left, top, right, bottom);
	settextstyle(pDC, 9, HORIZ_DIR, 3); // TRIPLEX_FONT -> 9로 대체
//	setusercharsize(pDC, right - left, textwidth_example49(str), bottom - top, textheight(str)*1.5);
	setcolor(pDC, GREEN);
	outtextxy(pDC, (left + right) / 2+4, (top + bottom) / 2-10, str);
}
void CGraphicMFCKDYView::char_in_box3(CDC* pDC, int left, int top, int right, int bottom, CString str)
{
	setcolor(pDC, BROWN);
	setusercharsize(pDC, 1, 1, 1, 1);
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	rectangle(pDC, left, top, right, bottom);
	settextstyle(pDC, 9, VERT_DIR, 3); // TRIPLEX_FONT -> 9로 대체
	setusercharsize(pDC, bottom-top, textwidth_example49(str), right-left, textheight(str));
	setcolor(pDC, GREEN);
	outtextxy(pDC, (left + right) / 2, (top + bottom) / 2, str);
}
void CGraphicMFCKDYView::char_in_box4(CDC* pDC, int left, int top, int right, int bottom, CString str)
{
	setcolor(pDC, BROWN);
	setusercharsize(pDC, 1, 1, 1, 1);
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	setlinestyle(pDC, SOLID_LINE, 0, THICK_WIDTH);
	rectangle(pDC, left, top, right, bottom);
	settextstyle(pDC, 9, VERT_DIR, 3); // TRIPLEX_FONT -> 9로 대체
	setusercharsize(pDC, bottom-top, textwidth_example49(str), right-left - top, textheight(str)*1.5);
	setcolor(pDC, GREEN);
	outtextxy(pDC, (left + right) / 2-10, (top + bottom) / 2-4, str);
}

void CGraphicMFCKDYView::setusercharsize(CDC* pDC, int multx, int divx, int multy, int divy)
{
	//4, 1, 1, 1

	int widthSize = (multx / divx);
	int heightSize = (multy / divy);
	CFont font;
	LOGFONT logFont;

	pDC->GetCurrentFont()->GetLogFont(&logFont);

	if (logFont.lfWidth == 10 && logFont.lfHeight == 20) {
		settextstyle(pDC, getFont_number_of_name(pDC, logFont.lfFaceName),
			(int)logFont.lfEscapement, gettingCharSize((int)logFont.lfHeight * heightSize, (int)logFont.lfWidth * widthSize));
	}
}


void CGraphicMFCKDYView::triplex_font(CDC* pDC)
{
	CFont font;
	LOGFONT logFont;
	font.GetLogFont(&logFont);
	settextstyle(pDC, TRIPLEX_FONT, logFont.lfEscapement, gettingCharSize(logFont.lfHeight, logFont.lfWidth));
}
void CGraphicMFCKDYView::small_font(CDC* pDC)
{
	CFont font;
	LOGFONT logFont;
	font.GetLogFont(&logFont);
	settextstyle(pDC, SMALL_FONT, logFont.lfEscapement, gettingCharSize(logFont.lfHeight, logFont.lfWidth));

}
void CGraphicMFCKDYView::sansserif_font(CDC* pDC)
{
	CFont font;
	LOGFONT logFont;
	font.GetLogFont(&logFont);
	settextstyle(pDC, SANS_SERIF_FONT, logFont.lfEscapement, gettingCharSize(logFont.lfHeight, logFont.lfWidth));

}
void CGraphicMFCKDYView::gothic_font(CDC* pDC)
{
	CFont font;
	LOGFONT logFont;
	font.GetLogFont(&logFont);
	settextstyle(pDC, GOTHIC_FONT, logFont.lfEscapement, gettingCharSize(logFont.lfHeight, logFont.lfWidth));

}

void CGraphicMFCKDYView::registerbgifont(CDC* pDC, void (*font)(CDC* pDC))
{
	//스크로트 폰트 등록 혹은 링크에 대해 이해가 불가능
	font(pDC);
}

void initialize_font(struct textsetting* text) {
	text->font = 0;
	text->direction = 0;	//0 => HORIZ_FONT, 1 => VERT_FONT
	text->charsize = 0;
	text->horiz = 0;
	text->vert = 0;
}

int gettingCharSize(LONG height, LONG width)
{
	int temp_height = 0, temp_width = 0,return_size;
	while (height > 20) {
		height /= 2;
		temp_height++;
	}
	
	while (width > 10) {
		width /= 2;
		temp_width++;
	}

	if (temp_height < temp_width)
		return_size = temp_height;
	else
		return_size = temp_width;

	return (return_size);
}

int getFont_number_of_name(CDC* pDC,WCHAR* lfFaceName)
{
	FontCount datas;
	// 람다 표현식 참조 소스
	// https://docs.microsoft.com/ko-kr/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
	EnumFontFamilies(
		pDC->m_hDC,
		(LPCTSTR)NULL,
		[](CONST LOGFONTW* lplf, CONST TEXTMETRICW* lpntm, DWORD FontType, LPARAM aFontCount) ->BOOL {
			FontCount* aiFontCount = (FontCount*)aFontCount;

			// Record the number of raster, TrueType, and vector  
			// fonts in the font-count array.  

			if (FontType & RASTER_FONTTYPE)
				aiFontCount->raster.push_back(*lplf);
			else if (FontType & TRUETYPE_FONTTYPE)
				aiFontCount->truetype.push_back(*lplf);
			else
				aiFontCount->unknown.push_back(*lplf);
			return TRUE;
		},
		(LPARAM)&datas
			);


	std::list<LOGFONT>::iterator iter = datas.truetype.begin();
	int count = 0;
	int font_num = 0;
	while (iter != datas.truetype.end()) {
		if (StrCmpCW(iter->lfFaceName, lfFaceName) == 0) {
			break;
		}
		iter++;
		count++;
	}

	return count;
}


void CGraphicMFCKDYView::gettextsetting(CDC* pDC,struct textsetting* text) {
	CFont *font;
	LOGFONT logFont;
	font = pDC->GetCurrentFont();
	font->GetLogFont(&logFont);
	int k = 0;
	
	//lfHeight => 20
	//lfWidth => 10
	// charsize(0) is lfHeight(20),lfWidth(10)
	//lfEscapement => 방향
	//lfWeight => 굵기 default : 400

	text->direction = logFont.lfEscapement;
	text->charsize = gettingCharSize(logFont.lfHeight, logFont.lfWidth);
	text->horiz = LEFT_TEXT;
	text->vert = CENTER_TEXT;	//맞는지 추후 재확인
	//현재 logFont의 숫자를 가져오나 Turbo C++에서의 5개(+5개)의 폰트값과 대조해야한다. -> 무시
	text->font = getFont_number_of_name(pDC, logFont.lfFaceName);
}

void CGraphicMFCKDYView::vietnam(CDC* pDC)
{
	setfillstyle(pDC, SOLID_FILL, RED);
	bar(pDC, 170, 100, 470, 300);
	star2_example49(pDC, 320, 200, 60, 0, YELLOW);
}

void CGraphicMFCKDYView::cuba(CDC* pDC)
{
	int i;
	setfillstyle(pDC, SOLID_FILL, BLUE);
	bar(pDC,170, 100, 470, 140);
	bar(pDC,170, 180, 470, 220);
	bar(pDC,170, 260, 470, 300);
	setfillstyle(pDC,SOLID_FILL, WHITE);
	
	bar(pDC, 170, 140, 470, 180);
	bar(pDC, 170, 220, 470, 260);
	setcolor(pDC,RED);
	setfillstyle(pDC, SOLID_FILL, RED);
	
	
	CBrush brush, * pOldBrush;
	brush.CreateSolidBrush(changeBookColorToMFCColor(RED));
	pOldBrush = pDC->SelectObject(&brush);
	pDC->BeginPath();
	pDC->MoveTo(170, 100);
	pDC->LineTo(170, 300);
	pDC->LineTo(290, 200);
	pDC->LineTo(170, 100);
	pDC->EndPath();
	pDC->FillPath();
	pDC->SelectObject(pOldBrush);
	DeleteObject(brush);
	
//	ExtFloodFill(pDC->m_hDC, 172, 200, changeBookColorToMFCColor(RED), FLOODFILLSURFACE);
	pDC->FloodFill(172, 200 , changeBookColorToMFCColor(RED));
	star2_example49(pDC, 210, 200, 20, 0, WHITE);
	
}

void CGraphicMFCKDYView::iraq(CDC* pDC)
{
	setfillstyle(pDC, SOLID_FILL, RED);
	bar(pDC, 170, 100, 470, 166);
	setfillstyle(pDC, SOLID_FILL, WHITE);
	bar(pDC, 170, 167, 470, 233);
	setfillstyle(pDC, SOLID_FILL, DARKGRAY);
	bar(pDC, 170, 234, 470, 300);
	
	star2_example49(pDC, 245, 200, 18, 0, GREEN);
	star2_example49(pDC, 320, 200, 18, 0, GREEN);
	star2_example49(pDC, 395, 200, 18, 0, GREEN);
}

void CGraphicMFCKDYView::chile(CDC* pDC)
{
	//setwritemode(COPY_PUT);
	setfillstyle(pDC, SOLID_FILL, WHITE);
	bar(pDC, 210, 100, 470, 200);
	setfillstyle(pDC, SOLID_FILL, RED);
	bar(pDC, 170, 200, 470, 300);
	setfillstyle(pDC, SOLID_FILL, BLUE);
	bar(pDC, 170, 100, 245, 200);

	star2_example49(pDC, 208, 150, 18, 0, WHITE);
}

void CGraphicMFCKDYView::panama(CDC* pDC)
{
	//setwritemode(COPY_PUT);
	setfillstyle(pDC, SOLID_FILL, RED);
	bar(pDC, 320, 100, 470, 200);
	setfillstyle(pDC, SOLID_FILL, BLUE);
	bar(pDC, 170, 200, 320, 300);
	setfillstyle(pDC, SOLID_FILL, WHITE);
	bar(pDC, 170, 100, 320, 200);
	bar(pDC, 320, 200, 470, 300);
	star2_example49(pDC, 245, 150, 20, 0, BLUE);
	star2_example49(pDC, 395, 250, 20, 0, RED);
}

void CGraphicMFCKDYView::china(CDC* pDC)
{
	//setwritemode(COPY_PUT);
	setfillstyle(pDC, SOLID_FILL, RED);
	bar(pDC, 170, 100, 470, 300);
	star2_example49(pDC, 210, 145, 20, 0, YELLOW);
	star2_example49(pDC, 240, 120, 6, 5*PI/5, YELLOW);
	star2_example49(pDC, 250, 140, 6, 4 * PI / 5, YELLOW);
	star2_example49(pDC, 250, 160, 6, 3 * PI / 5, YELLOW);
	star2_example49(pDC, 240, 180, 6, 2 * PI / 5, YELLOW);
}

void CGraphicMFCKDYView::yugo(CDC* pDC)
{
	//setwritemode(COPY_PUT);
	setfillstyle(pDC, SOLID_FILL, BLUE);
	bar(pDC, 170, 100, 470, 166);
	setfillstyle(pDC, SOLID_FILL, WHITE);
	bar(pDC, 170, 167, 470, 233);
	setfillstyle(pDC, SOLID_FILL, RED);
	bar(pDC, 170, 234, 470, 300);

	star2_example49(pDC, 320, 200, 60, 0, YELLOW);
	star2_example49(pDC, 320, 200, 54, 0, RED);
}

void CGraphicMFCKDYView::turkey(CDC* pDC)
{
	//setwritemode(COPY_PUT);
	setfillstyle(pDC, SOLID_FILL, RED);
	bar(pDC, 170, 100, 470, 300);
	setfillstyle(pDC, SOLID_FILL, WHITE);
	setcolor(pDC, WHITE);
	pieslice(pDC, 250, 200, 0, 360, 50);
	setfillstyle(pDC, SOLID_FILL, RED);
	setcolor(pDC, RED);
	pieslice(pDC, 270, 200, 0, 360, 42);

	star2_example49(pDC, 310, 200, 20, 7*PI/10, WHITE);
}

void CGraphicMFCKDYView::usa(CDC* pDC)
{
	int m, n, x, y;
	//setwritemode(COPY_PUT);
	setfillstyle(pDC, SOLID_FILL, RED);
	bar(pDC, 170, 100, 470, 300);
	setfillstyle(pDC, SOLID_FILL, WHITE);
	for (n = 0; n < 6; n++) {
		y = 115 + n * 31;
		bar(pDC, 170, y, 470, y + 15);
	}
	
	setfillstyle(pDC, SOLID_FILL, BLUE);
	bar(pDC, 170, 100, 310, 207);
	for (m = 0; m < 6; m++) {
		x = 180 + m * 24;
		for (n = 0; n < 5; n++) {
			y = 110 + n * 22;
			star2_example49(pDC, x, y, 5, 0, WHITE);
		}
	}
	for (m = 0; m < 5; m++) {
		x = 192 + m * 24;
		for (n = 0; n < 4; n++) {
			y = 121 + n * 22;
			star2_example49(pDC, x, y, 5, 0, WHITE);
		}
	}
}


void CGraphicMFCKDYView::star1(CDC* pDC, int x0, int y0, int r, double a, int c)
{
	int i, p[12];
	double s, ph;
	setcolor(pDC, c);
	s = 4 * PI / 5;
	ph = PI / 2 + a;
	for (i = 0; i < 5; i++) {
		p[2 * i] = x0 + (int)(r * cos(i * s + ph));
		p[2 * i + 1] = y0 + (int)(r * sin(i * s + ph));
	}
	p[10] = p[0];
	p[11] = p[1];
	drawPloy(pDC, 6, p);
}

void CGraphicMFCKDYView::star2(CDC* pDC, int x0, int y0, int r, double a, int c)
{
	int i, x[5],y[5],p[12];
	double s, ph;
	setcolor(pDC, c);
	setfillstyle(pDC, SOLID_FILL, c);
	s = 4 * PI / 5;
	ph = PI / 2 + a;
	for (i = 0; i < 5; i++) {
		p[2 * i] = x0 + (int)(r * cos(i * s + ph));
		p[2 * i + 1] = y0 + (int)(r * sin(i * s + ph));
	}
	p[10] = p[0];
	p[11] = p[1];
	fillPoly(pDC, 6, p);
	pDC->FloodFill(x0, y0, changeBookColorToMFCColor(c));
//	ExtFloodFill(pDC->m_hDC, x0, y0, changeBookColorToMFCColor(c), FLOODFILLSURFACE);
}

void CGraphicMFCKDYView::star2_example49(CDC* pDC, int x0, int y0, int r, double a, int c)
{
	int i, p[12];
	double s, ph;
	setcolor(pDC,c);
	setfillstyle(pDC, SOLID_FILL, c);
	s = 4 * PI / 5;
	ph = PI / 2 + a;
	for (i = 0; i < 5; i++) {
		p[2 * i] = x0 + (int)(r * cos(i * s + ph));
		p[2 * i + 1] = y0 + (int)(r * sin(i * s + ph));
	}
	p[10] = p[0];
	p[11] = p[1];

	// fill
	BOOL fillCheck = FALSE;
	CBrush brush, * pOldBrush;
	LOGBRUSH lb;
	DWORD pstyle;

	if (usePFF.useFillCheck == TRUE) {
		lb.lbHatch = usePFF.pattern;
		lb.lbColor = usePFF.fill_color;
		if (usePFF.pattern == MFC_SOLID_FILL)
			lb.lbStyle = BS_SOLID;
		else if (usePFF.pattern == MFC_EMPTY_FILL)
			lb.lbStyle = BS_HOLLOW;
		else
			lb.lbStyle = BS_HATCHED;

		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	else if (usePFF.useFillCheck == FALSE) {
		lb.lbHatch = NULL;
		lb.lbColor = changeBookColorToMFCColor(BLACK);
		lb.lbStyle = -1;
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}

	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}


	pDC->BeginPath();
	fillPoly(pDC, 6, p);
	pDC->EndPath();
	pDC->FillPath();
	pDC->FloodFill(x0, y0, changeBookColorToMFCColor(c));
//	ExtFloodFill(pDC->m_hDC, x0, y0, changeBookColorToMFCColor(c), FLOODFILLSURFACE);

	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}

}

void CGraphicMFCKDYView::gwindow_example48(CDC* pDC, int x1, int y1, int x2, int y2, int color, char str[])
{
	CString temp_str = L"";
	int text_width;
	char line_pattern[] = { 0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff };
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC, x1 - 2, y1 - 2, x2 + 2, y2 + 2);
	setfillstyle(pDC, SOLID_FILL, color);
	bar(pDC, x1, y1 + 1, x2, y2 + 2);
	text_width = textwidth(str);
	setfillpattern(pDC, line_pattern, color);
	bar(pDC, x1 + 5, y1 + 2, (x1 + x2) / 2 - 20 - text_width / 2, y1 + 19);
	bar(pDC, (x1 + x2) / 2 + text_width / 2 + 20, y1 + 2, x2 - 5, y1 + 19);
	setcolor(pDC, color);
	rectangle(pDC, x1, y1, x2, y2);
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	setcolor(pDC, BLACK);
	temp_str = CString(str);
	outtextxy(pDC, (x1 + x2) / 2, y1 + 10, temp_str);
	outtextxy(pDC, (x1 + x2) / 2 + 1, y1 + 10, temp_str);
}

void CGraphicMFCKDYView::star2_example48(CDC* pDC, int x0, int y0, int r, double a, int c)
{
	int i, p[12];
	double s, ph;
	setcolor(pDC, c);
	setfillstyle(pDC, SOLID_FILL, c);
	s = 4 * PI / 5;
	ph = PI / 2 + a;
	for (i = 0; i < 5; i++) {
		p[2 * i] = x0 + (int)(r * cos(i * s + ph));
		p[2 * i + 1] = y0 + (int)(r * sin(i * s + ph));
	}
	p[10] = p[0];
	p[11] = p[1];
	fillPoly(pDC, 6, p);
	pDC->FloodFill(x0, y0, changeBookColorToMFCColor(c));
//	ExtFloodFill(pDC->m_hDC, x0, y0, changeBookColorToMFCColor(c), FLOODFILLSURFACE);
}


void CGraphicMFCKDYView::figure(CDC* pDC)
{
	int color;
	static char pattern[] = { 0x00,0x7f,0x7f,0x7f,0x00,0xf7,0xf7,0xf7 };
	for (color = 7; color >= 1; color--) {
		setcolor(pDC,color);
		setfillpattern(pDC, pattern, color);
		fillellipse(pDC, 320, 200, color * 40, color * 25);
	}
}

void CGraphicMFCKDYView::title_example45(CDC* pDC)
{
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 3);
	setcolor(pDC, BLACK);
	outtextxy(pDC, 320, 100, L"INTRODUCATION");
	outtextxy(pDC, 320, 260, L"GRAPHICS");
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 2);
	setcolor(pDC, YELLOW);
	outtextxy(pDC, 320, 180, L"TO");
}

void CGraphicMFCKDYView::special_day(CDC* pDC, int date, int color)
{
	int i, j;
	char a[2];
	CString str = L"";

	i = date % 7;
	j = 1 + date / 7;
	cframe(pDC, 145 + (i - 1) * 50, 111 + (j - 1) * 30, 49, 29, 3, WHITE, color + 8, color);
	setcolor(pDC, BLACK);
//	_itoa((j - 1) * 7 + i, a, 10);
	str.Format(L"%d", (j - 1) * 7 + i);
	outtextxy(pDC, 170 + (i - 1) * 50, 110 + (j - 1) * 30, str);
}

void CGraphicMFCKDYView::cframe(CDC* pDC, int x, int y, int x_d, int y_d, int d, int bc, int fc, int sc)
{
	int f1[14], f2[14];
	f1[0] = x + x_d;
	f1[1] = y;
	f1[2] = x + x_d;
	f1[3] = y + y_d;
	f1[4] = x;
	f1[5] = y + y_d;
	f1[6] = x + d;
	f1[7] = y + y_d - d;
	f1[8] = x + x_d - d;
	f1[9] = y + y_d - d;
	f1[10] = x + x_d - d;
	f1[11] = y + d;
	f1[12] = x + x_d;
	f1[13] = y;
	f2[0] = x + x_d;
	f2[1] = y;
	f2[2] = x;
	f2[3] = y;
	f2[4] = x;
	f2[5] = y + y_d;
	f2[6] = x + d;
	f2[7] = y + y_d - d;
	f2[8] = x + d;
	f2[9] = y + d;
	f2[10] = x + x_d - d;
	f2[11] = y + d;
	f2[12] = x + x_d;
	f2[13] = y;

	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(pDC, SOLID_FILL, fc);
	bar(pDC, x + d, y + d, x + x_d - d, y + y_d - d);
	setcolor(pDC, sc);
	setfillstyle(pDC, SOLID_FILL, sc);
	fillPoly(pDC, 7, f1);
	setcolor(pDC, bc);
	fillPoly(pDC, 7, f2);
	setcolor(pDC, fc);
	line(pDC, x + x_d - d, y + y_d - d, x + x_d, y + y_d);
	line(pDC, x, y, x + d, y + d);

}

void CGraphicMFCKDYView::gwindow(CDC* pDC, int x1, int y1, int x2, int y2, int color, char str[])
{
	CString temp_str = L"";
	int text_width;
	char line_pattern[] = { 0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff };
	setfillstyle(pDC, SOLID_FILL, BLACK);
	bar(pDC,x1 - 2, y1 - 2, x2 + 2, y2 + 2);
	setfillstyle(pDC, SOLID_FILL, color);
	bar(pDC, x1, y1 + 1, x2, y2 + 2);
	text_width = textwidth(str);
	setfillpattern(pDC, line_pattern, color);
	bar(pDC, x1 + 5, y1 + 2, (x1 + x2) / 2 - 20 - text_width / 2, y1 + 19);
	bar(pDC, (x1 + x2) / 2 + text_width / 2 + 20, y1 + 2, x2 - 5, y1 + 19);
	setcolor(pDC,color);
	rectangle(pDC, x1, y1, x2, y2);
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	setcolor(pDC, BLACK);
	temp_str = CString(str);
	outtextxy(pDC, (x1 + x2) / 2, y1 + 10, temp_str);
	outtextxy(pDC, (x1 + x2) / 2+1, y1 + 10, temp_str);
}

void CGraphicMFCKDYView::setfillpattern(CDC* pDC, char* upattern, int color)
{
	
}

int textwidth(char s[])
{
	int i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return (i * 6);
}

int textwidth_example49(CString str)
{
	return str.GetLength()*6;
}

int textheight(CString str)
{
	return str.GetLength() * 6;
}

void CGraphicMFCKDYView::clearDevice(CDC* pDC)
{
	COLORREF initialBkColor = RGB(255, 255, 255);
	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(initialBkColor);
	pDC->FillRect(&rect, &brush);
}

void CGraphicMFCKDYView::fillstyledemo(CDC* pDC)
{
	//	char str[3];
	CString str = L"";
	int x, y, h, w, style, i, j;
	w = 2 * (640 / 13);
	x = w / 2;
	h = 2 * (470 / 10);
	y = h / 2;
	for (style = 0, i = 0; i < 3; i++, x = w / 2, y += h / 2 * 3) {
		for (j = 0; j < 4; j++, style++, x += w / 2 * 3) {
			setfillstyle(pDC, style, getcolor());
			rectangle(pDC, x, y, x + w, y + h);
			pDC->FloodFill(x+1, y+1, usePFF.pen_color);
		//	ExtFloodFill(pDC->m_hDC, x+1, y+1, usePFF.pen_color, FLOODFILLSURFACE);
			//itoa(style, str, 10);
			str.Format(L"%d", style);
			outtextxy(pDC, x + w / 2, y + h + 4, str);
		}
	}
}

int return_pattern(int pattern) {
	int return_pat = 0;
	switch (pattern) {
	case EMPTY_FILL:
		return_pat = MFC_EMPTY_FILL;
		break;
	case SOLID_FILL:
		return_pat = MFC_SOLID_FILL;
		break;
	case LINE_FILL:
		return_pat = MFC_LINE_FILL;
		break;
	case LTSLASH_FILL:
		return_pat = MFC_LTSLASH_FILL;
		break;
	case SLASH_FILL:
		return_pat = MFC_SLASH_FILL;
		break;
	case BKSLASH_FILL:
		return_pat = MFC_BKSLASH_FILL;
		break;
	case LTBKSLASH_FILL:
		return_pat = MFC_LTBKSLASH_FILL;
		break;
	case HATCH_FILL:
		return_pat = MFC_HATCH_FILL;
		break;
	case XHATCH_FILL:
		return_pat = MFC_XHATCH_FILL;
		break;
	default:
		return_pat = MFC_SOLID_FILL;
		break;
	}
	return return_pat;
}

void CGraphicMFCKDYView::setfillstyle(CDC* pDC, int pattern, int color)
{
	//2022.09.28 통합 color control
	usePFF.useFillCheck = TRUE;
	usePFF.pattern = return_pattern(pattern);
	usePFF.fill_color = changeBookColorToMFCColor(color);
}

void CGraphicMFCKDYView::colordemo(CDC* pDC)
{
	//	char str[3];
	CString str = L"";
	int x, y, h, w, color, i, j;
	w = 2 * (640 / 13);
	x = w / 2;
	h = 2 * (470 / 10);
	y = h / 2;
	/*
	FT_SOLID = 0,
		FT_VERTGRADIENT = 1,
		FT_HORZGRADIENT = 2,
		FT_RADIALGRADIENT = 3,
		FT_TILEIMAGE = 4,
	*/
	for (color = 0, i = 0; i < 4; i++, x = w / 2, y += h / 2 * 3) {
		for (j = 0; j < 4; j++, color++, x += w / 2 * 3) {
			setfillstyle(pDC, FT_SOLID, color);
			setcolor(pDC,color);
			if (color == BLACK)
				setcolor(pDC, WHITE);
			pDC->Rectangle(x, y, x + w, y + h);
			pDC->FloodFill(x+1, y+1, changeBookColorToMFCColor(color));
		//	ExtFloodFill(pDC->m_hDC, x+1, y+1, changeBookColorToMFCColor(color), FLOODFILLSURFACE);
			//itoa(style, str, 10);
			str.Format(L"%d", color);
			outtextxy(pDC, x + w / 2, y + h + 4, str);
		}
	}
}

int CGraphicMFCKDYView::getcolor()
{
	if (usePFF.usePenCheck)
		return changeMFCColorToBookColor(usePFF.pen_color);
	else
		return BLACK;
}

void CGraphicMFCKDYView::title(CDC* pDC)
{
	int i, x, y;
	CString str[3] = { L"Turbo C++",L"Graphics",L"by J.Shin" };
	settextstyle(pDC,9, HORIZ_DIR, 8);
	settextjustify(pDC, CENTER_TEXT, CENTER_TEXT);
	for (i = 0; i <= 2; i++) {
		setcolor(pDC, MAGENTA);
		for (x = -2; x <= 2; x++)
			for (y = -2; y <= 2; y++)
				outtextxy(pDC, 320 + x, /*100 +*/ i * 160 + y, str[i]);
		setcolor(pDC,YELLOW);
		outtextxy(pDC, 320, /*100 +*/ i * 160, str[i]);
	}
}

void CGraphicMFCKDYView::delay(int msec) {
	static LARGE_INTEGER g_Frequency;
	QueryPerformanceFrequency(&g_Frequency);
	static LARGE_INTEGER beginTime;
	static LARGE_INTEGER endTime;

	QueryPerformanceCounter(&beginTime);
	while (1) {
		QueryPerformanceCounter(&endTime);
		if (((float)(endTime.QuadPart - beginTime.QuadPart) / (float)g_Frequency.QuadPart) * 1000.0f >= msec)
			break;
	}
}

int CGraphicMFCKDYView::getmaxx() {
	CRect rect;
	GetClientRect(&rect);
	return rect.Size().cx;
}

int CGraphicMFCKDYView::getmaxy() {
	CRect rect;
	GetClientRect(&rect);
	return rect.Size().cy;
}

void CGraphicMFCKDYView::frame(CDC* pDC)
{
	setcolor(pDC, CYAN);
	line(pDC, 100, 300, 500, 300);
	line(pDC, 200, 60, 200, 350);
	line(pDC, 195, 200, 200, 200);
	line(pDC, 300, 300, 300, 305);
	setcolor(pDC, RED);
	rectangle(pDC, 200, 100, 400, 300);
	setcolor(pDC, WHITE);
	my_circle(pDC, 300, 200, 100);
	setcolor(pDC,YELLOW);
	settextstyle(pDC, BOOK_DEVICE_DEFAULT_FONT, HORIZ_DIR, 2);
	settextjustify(pDC, CENTER_TEXT, TOP_TEXT);	
	outtextxy(pDC, 200, 0, L"Calculation of pi");	//x, 320 -> 200
	setcolor(pDC, GREEN);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 0);
	settextjustify(pDC, CENTER_TEXT, TOP_TEXT);
	outtextxy(pDC, 180, 305, L"0");
	outtextxy(pDC, 300, 305, L"1");
	outtextxy(pDC, 400, 305, L"2");
	outtextxy(pDC, 520, 280, L"x");
	settextjustify(pDC, LEFT_TEXT, CENTER_TEXT);
	outtextxy(pDC, 180, 200, L"1");
	outtextxy(pDC, 180, 100, L"2");
	outtextxy(pDC, 190, 40, L"y");
}

void CGraphicMFCKDYView::round_rec(CDC* pDC, int x, int y, int w, int h, int r, int dc)
{
	setlinestyle(pDC, SOLID_LINE, 0, NORM_WIDTH);
	setcolor(pDC,dc);
	my_arc(pDC, x, y,r,changeMFCColorToBookColor(usePFF.pen_color),90,180);
	my_arc(pDC, x, y+h,r, changeMFCColorToBookColor(usePFF.pen_color),180,270);
	my_arc(pDC, x + w, y + h, r, changeMFCColorToBookColor(usePFF.pen_color), 270, 360);
	my_arc(pDC, x + w, y, r, changeMFCColorToBookColor(usePFF.pen_color), 0, 90);
	line(pDC, x - r, y, x - r, y + h);
	line(pDC, x, y + h + r, x + w, y + h + r);
	line(pDC, x + w + r, y + h, x + w + r, y);
	line(pDC, x + w, y - r, x, y - r);
}
void CGraphicMFCKDYView::my_text(CDC* pDC)
{
	settextjustify(pDC,CENTER_TEXT, CENTER_TEXT);
	setcolor(pDC, GREEN);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 4);
	outtextxy(pDC, 320, 130, L"Turbo C++");
	setcolor(pDC,CYAN);
	settextstyle(pDC, BOOK_DEVICE_DEFAULT_FONT, HORIZ_DIR, 3);
	outtextxy(pDC, 320, 200, L"Graphics");
	setcolor(pDC, RED);
	settextstyle(pDC, TRIPLEX_FONT, HORIZ_DIR, 4);	//GOTHIC_FONT -> TRIPLEX_FONT(맑은 고딕)으로 변경
	outtextxy(pDC, 320, 250, L"J. Shin");
}

void CGraphicMFCKDYView::lineout(CDC* pDC, int y, unsigned m, CString str)
{
	
	outtextxy(pDC, 0, y, str);
	setlinestyle(pDC, USERBIT_LINE, m, NORM_WIDTH);
	line(pDC, 230, y, 430, y);
	setlinestyle(pDC, USERBIT_LINE, m, THICK_WIDTH);
	line(pDC, 440, y, 639, y);
}


void CGraphicMFCKDYView::settextjustify(CDC* pDC, int horiz, int vertical)
{
	if (usePFF.useFontCheck != FALSE && usePFF.useFontCheck != TRUE)
		usePFF.useFontCheck = FALSE;
	pDC->SetTextAlign(horiz);
	pDC->SetTextAlign(vertical);
}


void CGraphicMFCKDYView::frame(CDC* pDC,int c)
{
	int i;
	setcolor(pDC,c);
	for (i = 70; i <= 570; i += 10)
		line(pDC,i, 50, i, 350);
	for (i = 50; i <= 350; i += 10)
		line(pDC, 70, i, 570, i);
	for (i = 71; i <= 571; i += 100)
		line(pDC, i, 50, i, 350);
	for (i = 51; i <= 351; i += 100)
		line(pDC, 70, i, 570, i);
}

void CGraphicMFCKDYView::setpallette(CDC* pDC, int prev_color, int next_color)
{
	CPalette palette,*pOldPalette;
//	LPLOGPALETTE lplgPalette;
//	lplgPalette->palNumEntries = 256;
//	lplgPalette->palVersion = 0x300;
//	lplgPalette->palPalEntry.
	
}

void CGraphicMFCKDYView::setbkcolor(CDC* pDC, int color)
{
//	OnCtlColor(pDC, this, CTLCOLOR_STATIC, color);
	pDC->SetBkColor(changeBookColorToMFCColor(color));
}

void CGraphicMFCKDYView::my_arc(CDC* pDC, int x, int y, int radius, int color, int startAngle,int endAngle)
{
	setarccoords(x, y, radius);
	for (int i = startAngle; i <= endAngle; i++)
		putpixel(pDC, x + (int)(radius * cos(i * PI / 180)),
			y - (int)(radius * sin(i * PI / 180)), color);
}

void CGraphicMFCKDYView::my_circle_c(CDC* pDC, int x, int y, int radius, int color)
{
	setarccoords(x, y, radius);
	for (int i = 0; i <= 360; i++)
		putpixel(pDC, x + (int)(radius * cos(i * PI / 180)), y - (int)(radius * sin(i * PI / 180)), color);
}

void CGraphicMFCKDYView::my_circle(CDC* pDC, int x, int y, int radius)
{
	setarccoords(x, y, radius);
	for (int i = 0; i <= 360; i++)
		putpixel(pDC, x + (int)(radius * cos(i * PI / 180)), y - (int)(radius * sin(i * PI / 180)), changeMFCColorToBookColor(usePFF.pen_color));	//color, WHITE -> GREEN으로 대체
}


void CGraphicMFCKDYView::lissajous(CDC* pDC, int x0, int y0,
	int fx, int fy, int radius, int delta, COLORREF color)
{
	int step, x, y;
	double factor = PI / 180;
	setcolor(pDC,changeMFCColorToBookColor(color));

	//pen
	CPen pen, * pOldPen = 0;
	if (usePFF.usePenCheck = TRUE) {
		pen.CreatePen(usePFF.pen_style,usePFF.pen_nWidth,usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
	}
	else {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
	}

	for (step = 0; step <= 360; step += 3) {
		x = radius * cos(fx * step * factor);
		y = radius * cos((fy * step + delta) * factor);
		if (step == 0)
			pDC->MoveTo(x0 + x, y0 - y);
		else
			pDC->LineTo(x0 + x, y0 - y);
	}
	pDC->SelectObject(pOldPen);
}


void CGraphicMFCKDYView::putpixel(CDC* pDC, int x, int y, int color)
{
	pDC->SetPixel(x, y, changeBookColorToMFCColor(color));
}

CString getFont_name(CDC* pDC,int font_num) {
	FontCount datas;
	// 람다 표현식 참조 소스
	// https://docs.microsoft.com/ko-kr/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
	EnumFontFamilies(
		pDC->m_hDC,
		(LPCTSTR)NULL,
		[](CONST LOGFONTW* lplf, CONST TEXTMETRICW* lpntm, DWORD FontType, LPARAM aFontCount) ->BOOL {
			FontCount* aiFontCount = (FontCount*)aFontCount;

			// Record the number of raster, TrueType, and vector  
			// fonts in the font-count array.  

			if (FontType & RASTER_FONTTYPE)
				aiFontCount->raster.push_back(*lplf);
			else if (FontType & TRUETYPE_FONTTYPE)
				aiFontCount->truetype.push_back(*lplf);
			else
				aiFontCount->unknown.push_back(*lplf);
			return TRUE;
		},
		(LPARAM)&datas
			);
	
	
	std::list<LOGFONT>::iterator iter = datas.truetype.begin();
	int count = 0;

	if (font_num >= datas.truetype.size()) {
		//현재 시스템 기본 폰트의 number가 322으로 최대값 321보다 높다.
		//고로 이상이 넘어가면 Arial(window 기본 폰트)를 return한다.
		while (iter != datas.truetype.end()) {
			if (StrCmpCW(iter->lfFaceName,L"Arial"))
				break;
			iter++;
			count++;
		}
	}
	else {
		while (iter != datas.truetype.end()) {
			if (count == font_num)
				break;
			iter++;
			count++;
		}
	}
	
	return iter->lfFaceName;
}

void CGraphicMFCKDYView::initialized_font() {
	fontData.nHeight = 16;
	fontData.nWidth = 8;
	fontData.nEscapement = HORIZ_DIR;
	fontData.nOrientation = NORM_WIDTH;
	fontData.nWeight;
	fontData.bItalic;
	fontData.bUnderline;
	fontData.cStrikeOut;
	fontData.nCharSet;
	fontData.nOutPrecision;
	fontData.nClipPrecision;
	fontData.nQuality;
	fontData.nPitchAndFamily;
	fontData.lpszFacename;
	fontData.loadCount;
}

void CGraphicMFCKDYView::settingFontData(int font, int direction, int font_size)
{
	fontData.nHeight = (font_size + 1) * 16;
	fontData.nWidth = (font_size + 1) * 8;
	fontData.nEscapement = HORIZ_DIR;
	fontData.nOrientation = 0;
	fontData.nWeight = FW_NORMAL;
	fontData.bItalic = FALSE;
	fontData.bUnderline = FALSE;
	fontData.cStrikeOut = FALSE;
	fontData.nCharSet = DEFAULT_CHARSET;
	fontData.nOutPrecision = OUT_DEFAULT_PRECIS;
	fontData.nClipPrecision = CLIP_CHARACTER_PRECIS;
	fontData.nQuality = DEFAULT_QUALITY;
	fontData.nPitchAndFamily = DEFAULT_PITCH;
	fontData.lpszFacename = L"Arial";
	fontData.loadCount = 0;
}

void CGraphicMFCKDYView::settextstyle(CDC* pDC, int font, int direction, int font_size)
{
	usePFF.useFontCheck = TRUE;
	usePFF.font = font;
	usePFF.direction = direction;
	usePFF.font_size = font_size;
	usePFF.fontStr = getFont_name(pDC, font);

	//height default value is 20
	//width default value is 10
}

void CGraphicMFCKDYView::setlinestyle(CDC* pDC, int line_style, int upattern, int line_size)
{
	CPen pen,* pOldPen;
	int style = 0;
	int cwidth = 0;
	switch (line_style) {
	case SOLID_LINE:
		style = PS_SOLID;
		break;
	case DOTTED_LINE:
		style = PS_DOT;
		break;
	case CENTER_LINE:
		style = PS_DASHDOT;
		break;
	case DASHED_LINE:
		style = PS_DASH;
		break;
	case USERBIT_LINE:
		style = PS_USERSTYLE;
		break;
	default:
		style = PS_SOLID;
		break;
	}

	switch (line_size) {
	case NORM_WIDTH:
		cwidth = 1;
		break;
	case THICK_WIDTH:
		cwidth = 3;
		break;
	default:
		cwidth = line_size;
		break;
	}

	if (upattern != 0) {
		usePFF.upattern = upattern;
	}

	usePFF.usePenCheck = TRUE;
	usePFF.pen_nWidth = cwidth;
	usePFF.pen_style = style;

}

int changeBookColorToMFCColor(int colorNum)
{
	switch (colorNum) {
	case BLACK:
		return MFC_BLACK;
		break;
	case BLUE:
		return MFC_BLUE;
		break;
	case GREEN:
		return MFC_GREEN;
		break;
	case CYAN:
		return MFC_CYAN;
		break;
	case RED:
		return MFC_RED;
		break;
	case MAGENTA:
		return MFC_MAGENTA;
		break;
	case BROWN:
		return MFC_BROWN;
		break;
	case LIGHTGRAY:
		return MFC_LIGHTGRAY;
		break;
	case DARKGRAY:
		return MFC_DARKGRAY;
		break;
	case LIGHTBLUE:
		return MFC_LIGHTBLUE;
		break;
	case LIGHTGREEN:
		return MFC_LIGHTGREEN;
		break;
	case LIGHTRED:
		return MFC_LIGHTRED;
		break;
	case LIGHTMAGENTA:
		return MFC_LIGHTMAGENTA;
		break;
	case YELLOW:
		return MFC_YELLOW;
		break;
	case WHITE:
		return MFC_WHITE;
		break;
	case LIGHTCYAN:
		return MFC_LIGHTCYAN;
		break;
	default:
		return MFC_BLACK;
		break;
	}
	return 0;
}

int changeMFCColorToBookColor(COLORREF colorNum)
{
	switch (colorNum) {
	case MFC_BLACK:
		return BLACK;
		break;
	case MFC_BLUE:
		return BLUE;
		break;
	case MFC_GREEN:
		return GREEN;
		break;
	case MFC_CYAN:
		return CYAN;
		break;
	case MFC_RED:
		return RED;
		break;
	case MFC_MAGENTA:
		return MAGENTA;
		break;
	case MFC_BROWN:
		return BROWN;
		break;
	case MFC_LIGHTGRAY:
		return LIGHTGRAY;
		break;
	case MFC_DARKGRAY:
		return DARKGRAY;
		break;
	case MFC_LIGHTBLUE:
		return LIGHTBLUE;
		break;
	case MFC_LIGHTGREEN:
		return LIGHTGREEN;
		break;
	case MFC_LIGHTRED:
		return LIGHTRED;
		break;
	case MFC_LIGHTMAGENTA:
		return LIGHTMAGENTA;
		break;
	case MFC_YELLOW:
		return YELLOW;
		break;
	case MFC_WHITE:
		return WHITE;
		break;
	default:
		return BLACK;
		break;
	}
	return 0;
}

int brush_changeBookColorToMFCColor(int colorNum)
{
	COLORREF color;
	
	switch (colorNum) {
	case BLACK:
		return MFC_BLACK;
		break;
	case BLUE:
		return MFC_BLUE;
		break;
	case GREEN:
		return MFC_GREEN;
		break;
	case CYAN:
		return MFC_CYAN;
		break;
	case RED:
		return MFC_RED;
		break;
	case MAGENTA:
		return MFC_MAGENTA;
		break;
	case BROWN:
		return MFC_BROWN;
		break;
	case LIGHTGRAY:
		return MFC_LIGHTGRAY;
		break;
	case DARKGRAY:
		return MFC_DARKGRAY;
		break;
	case LIGHTBLUE:
		return MFC_LIGHTBLUE;
		break;
	case LIGHTGREEN:
		return MFC_LIGHTGREEN;
		break;
	case LIGHTRED:
		return MFC_LIGHTRED;
		break;
	case LIGHTMAGENTA:
		return MFC_LIGHTMAGENTA;
		break;
	case YELLOW:
		return MFC_YELLOW;
		break;
	case WHITE:
		return MFC_WHITE;
		break;
	default:
		return MFC_BLACK;
		break;
	}
	return 0;
}

void CGraphicMFCKDYView::setcolor(CDC* pDC, int color)
{
	//2022.09.28 통합 컬러 control
	usePFF.usePenCheck = TRUE;
	usePFF.pen_color = changeBookColorToMFCColor(color);
	usePFF.useFillCheck = TRUE;
	usePFF.fill_color = changeBookColorToMFCColor(color);
}

void CGraphicMFCKDYView::bar(CDC* pDC, int leftTopX, int leftTopY, int rightBottomX, int rightBottomY)
{
	CPoint top,bottom;
	top.x = leftTopX;
	top.y = leftTopY;
	bottom.x = rightBottomX;
	bottom.y = rightBottomY;

	CRect rect(top, bottom);

	rectangle(pDC, top.x, top.y, bottom.x, bottom.y);
//	initialized_usePFF();
}

void CGraphicMFCKDYView::bar3d(CDC* pDC, int leftTopX, int leftTopY,
	int rightBottomX, int rightBottomY, int depth, int topFlag)
{
	CPoint top, bottom;
	top.x = leftTopX;
	top.y = leftTopY;
	bottom.x = rightBottomX;
	bottom.y = rightBottomY;

	CRect rect(top, bottom);

//	pDC->Rectangle(rect);
	rectangle(pDC, top.x, top.y, bottom.x, bottom.y);

	//색 채워진 사각형 완료.

	/*
	double temp_depth = rightBottomX - leftTopX;
	temp_depth /= 4;
	
	temp_depth = round(temp_depth);
	*/

	double temp_depth = depth;
	if (temp_depth < 0)
		return;

	POINT sideRectangleBottom,sideRectangleTop;
	sideRectangleBottom.x = rightBottomX + temp_depth;
	sideRectangleBottom.y = rightBottomY - temp_depth;

	sideRectangleTop.x = (leftTopX + (rightBottomX - leftTopX))+temp_depth;
	sideRectangleTop.y = leftTopY - temp_depth;

	line(pDC, rightBottomX, rightBottomY, sideRectangleBottom.x, sideRectangleBottom.y);
	line(pDC, sideRectangleBottom.x, sideRectangleBottom.y, sideRectangleTop.x, sideRectangleTop.y);
	line(pDC, (leftTopX + (rightBottomX - leftTopX)), leftTopY, sideRectangleTop.x, sideRectangleTop.y);
	
	if (topFlag == 1) {
		POINT topRectangleTop;
		topRectangleTop.x = leftTopX + temp_depth;
		topRectangleTop.y = leftTopY - temp_depth;

		line(pDC, leftTopX, leftTopY, topRectangleTop.x, topRectangleTop.y);
		line(pDC, topRectangleTop.x, topRectangleTop.y, sideRectangleTop.x, sideRectangleTop.y);
	}
}

void CGraphicMFCKDYView::line(CDC* pDC, int startX, int startY, int endX, int endY) {
	//pen
	BOOL penCheck = FALSE;
	CPen pen, * pOldPen;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}

//	initialized_usePFF();
	
}

void CGraphicMFCKDYView::sector(CDC* pDC, int x, int y, int startAngle, int endAngle, int xradius, int yradius)
{
	// pen, fill
	BOOL penCheck = FALSE, fillCheck = FALSE;
	CPen pen, * pOldPen;
	CBrush brush, * pOldBrush;
	LOGBRUSH lb;
	DWORD pstyle;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	if (usePFF.useFillCheck == TRUE) {
		lb.lbHatch = usePFF.pattern;
		lb.lbColor = usePFF.fill_color;
		if (usePFF.pattern == MFC_SOLID_FILL)
			lb.lbStyle = BS_SOLID;
		else if (usePFF.pattern == MFC_EMPTY_FILL)
			lb.lbStyle = BS_HOLLOW;
		else
			lb.lbStyle = BS_HATCHED;

		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	else if (usePFF.useFillCheck == FALSE) {
		lb.lbHatch = NULL;
		lb.lbColor = changeBookColorToMFCColor(BLACK);
		lb.lbStyle = -1;
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}


	int leftTopX = x - xradius;
	int leftTopY = y + yradius;
	int rightBottomX = x + xradius;
	int rightBottomY = y - yradius;

	if (startAngle == 0 && endAngle == 360)
	{
		//온전한 원
		setarccoords(leftTopX, leftTopY, rightBottomX, rightBottomY);
		pDC->Ellipse(leftTopX, leftTopY,
			rightBottomX, rightBottomY);
	}
	else {
		//온전치 않은 원
		int realStartAngle = 360 - startAngle;
		int realEndAngle = 360 - endAngle;


		int startX_dot = x + (round((xradius * cos(getRadian(realStartAngle)))));
		int startY_dot = y + (round((yradius * sin(getRadian(realStartAngle)))));
		int endX_dot = x + (round((xradius * cos(getRadian(realEndAngle)))));
		int endY_dot = y + (round((yradius * sin(getRadian(realEndAngle)))));

		setarccoords(x, y, startAngle, endAngle, xradius, yradius);
		pDC->Pie(leftTopX, leftTopY,
			rightBottomX, rightBottomY,
			startX_dot, startY_dot,
			endX_dot, endY_dot
		);
	}

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}
//	initialized_usePFF();
}

void CGraphicMFCKDYView::rectangle(CDC* pDC, int leftTopX, int leftTopY, int rightBottomX, int rightBottomY) {

	// pen, fill
	BOOL penCheck = FALSE, fillCheck = FALSE;
	CPen pen, * pOldPen;
	CBrush brush, * pOldBrush;
	LOGBRUSH lb;
	DWORD pstyle;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	if (usePFF.useFillCheck == TRUE) {
		lb.lbHatch = usePFF.pattern;
		lb.lbColor = usePFF.fill_color;
		if (usePFF.pattern == MFC_SOLID_FILL)
			lb.lbStyle = BS_SOLID;
		else if (usePFF.pattern == MFC_EMPTY_FILL)
			lb.lbStyle = BS_HOLLOW;
		else
			lb.lbStyle = BS_HATCHED;
		
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	else if (usePFF.useFillCheck == FALSE) {
		lb.lbHatch = NULL;
		lb.lbColor = changeBookColorToMFCColor(BLACK);
		lb.lbStyle = BS_SOLID;
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	

	pDC->Rectangle(leftTopX, leftTopY, rightBottomX, rightBottomY);

	/*
	if (fill_PatternData.checkUse == TRUE) {
		CBrush brush, after_brush;
		brush.CreateSolidBrush(fill_PatternData.color);
		COLORREF bkcolor = pDC->GetBkColor();
		pDC->SelectObject(&brush);
		pDC->Rectangle(leftTopX, leftTopY, rightBottomX, rightBottomY);
		DeleteObject(brush);
		std::vector<FILL_POINT> fill_point;
		fill_point = setting_pattern(leftTopX, leftTopY, rightBottomX, rightBottomY);
		//		initialize_fill_pattern();
		if (fill_point.size() > 0) {
			setcolor(pDC, changeMFCColorToBookColor(bkcolor));
			after_brush.CreateSolidBrush(bkcolor);
			pDC->SelectObject(&after_brush);
			std::vector<FILL_POINT>::iterator iter;
			for (iter = fill_point.begin(); iter != fill_point.end(); iter++) {
				if (iter->rightBottomX == 0 && iter->rightBottomY == 0)
					putpixel(pDC, iter->leftTopX, iter->leftTopY, bkcolor);
				else
					rectangle(pDC, iter->leftTopX, iter->leftTopY, iter->rightBottomX, iter->rightBottomY);
			}
			DeleteObject(after_brush);
		}
		else {
			CBrush brush, * pOldBrush = 0;
			brush.CreateBrushIndirect(&lb);
			pOldBrush = pDC->SelectObject(&brush);
			pDC->BeginPath();
			pDC->Rectangle(leftTopX, leftTopY, rightBottomX, rightBottomY);
			pDC->EndPath();
			pDC->FillPath();
			pDC->SelectObject(pOldBrush);
		}
	}
	else {
		pDC->Rectangle(leftTopX, leftTopY, rightBottomX, rightBottomY);
	}
	*/

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}

//	initialized_usePFF();
}

void CGraphicMFCKDYView::arcCircle_book(CDC* pDC, int x, int y, int startAngle, int endAngle, int radius)
{
	//pen
	BOOL penCheck = FALSE;
	CPen pen, * pOldPen;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	//Window의 y축은 일반적인 수학연산에서의 상하의 위치가 아닌 위쪽이 '-', 아래쪽이 '+' 형식으로 되어 있다.
	//고로 추후의 좌표들은 상하 대칭을 통하여 재검증해야한다.

	//Arc가 그려지는 순서 세팅
//	pDC->SetArcDirection(AD_CLOCKWISE); //시계방향
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE); //반시계방향



	//설명 참고 사이트 : http://www.ucancode.net/Visual_C_MFC_COM_Control/CDC_Arc_Pie_Chord.htm

	// (x,y) 좌표는 원의 중간지점
	// 주어진 것. 시작각, 종료각, 반지름
	// 즉, 시작각으로부터 종료각까지 회전시킨다.(0 ~ 360도 사이)
	// startAngle 각도부터 시작하여 endAngle 각도 까지만 현시한다.
	//angle은 '각'

	//x축 오른쪽부터 시작하여 위로 startAngle, endAngle을 계산한다.
	//MFC는 x축 오른쪽부터 시작하여 아래쪽으로 startAngle, endAngle을 계산한다.

	int leftTopX = x - radius;
	int leftTopY = y + radius;
	int rightBottomX = x + radius;
	int rightBottomY = y - radius;

	int realMFC_Angle = 360 - (startAngle + endAngle);
	int realStartAngle = startAngle + realMFC_Angle;
	int realEndAngle = endAngle + realMFC_Angle;


	int startAngle_selectXPlus = 0;
	int startAngle_selectYPlus = 0;
	int endAngle_selectXPlus = 0;
	int endAngle_selectYPlus = 0;


	if (realStartAngle >= 0 && realStartAngle <= 90) {
		startAngle_selectXPlus = 1;
		startAngle_selectYPlus = 0;
	}
	else if (realStartAngle >= 90 && realStartAngle <= 180) {
		startAngle_selectXPlus = 0;
		startAngle_selectYPlus = 0;
	}
	else if (realStartAngle >= 180 && realStartAngle <= 270) {
		startAngle_selectXPlus = 0;
		startAngle_selectYPlus = 1;
	}
	else {
		startAngle_selectXPlus = 1;
		startAngle_selectYPlus = 1;
	}

	if (realEndAngle >= 0 && realEndAngle <= 90) {
		endAngle_selectXPlus = 1;
		endAngle_selectYPlus = 0;
	}
	else if (realEndAngle >= 90 && realEndAngle <= 180) {
		endAngle_selectXPlus = 0;
		endAngle_selectYPlus = 0;
	}
	else if (realEndAngle >= 180 && realEndAngle <= 270) {
		endAngle_selectXPlus = 0;
		endAngle_selectYPlus = 1;
	}
	else {
		endAngle_selectXPlus = 1;
		endAngle_selectYPlus = 1;
	}


	do {
		if (realStartAngle > 90)
			realStartAngle -= 90;

		if (realEndAngle > 90)
			realEndAngle -= 90;
	} while (realStartAngle > 90 || realEndAngle > 90);

	int b = 0;

	//밑변(x 좌표) 구하는 공식
	// -> tan(각도) = (높이) / (밑변)
	// -> 그러나 우리는 빗변만 즉, radius값만 알고 있으므로
	// sin(각도)을 활용하여 높이를 구해야한다.
	// 높이 = radius * sin()
	// 밑변 = 높이 * tan()

	double height = radius * (ceil((sin(getRadian(realStartAngle)) * 100)) / 100);
	double width = radius * abs((ceil((cos(getRadian(realStartAngle)) * 100)) / 100));
	int startX_dot = 0;
	int startY_dot = 0;

	if (startAngle_selectXPlus == 1)
		startX_dot = x + round(width);
	else
		startX_dot = x - round(width);

	if (startAngle_selectYPlus == 1)
		startY_dot = y + round(height);
	else
		startY_dot = y - round(height);

	height = radius * (ceil((sin(getRadian(realEndAngle)) * 100)) / 100);
	width = radius * abs((ceil((cos(getRadian(realEndAngle)) * 100)) / 100));

	int endX_dot = 0;
	int endY_dot = 0;

	if (endAngle_selectXPlus == 1)
		endX_dot = x + round(width);
	else
		endX_dot = x - round(width);

	if (endAngle_selectYPlus == 1)
		endY_dot = y + round(height);
	else
		endY_dot = y - round(height);

	setarccoords(x, y,startAngle,endAngle,radius,radius);
	pDC->Arc(leftTopX, leftTopY,
		rightBottomX, rightBottomY,
		startX_dot, startY_dot,
		endX_dot, endY_dot
	);

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}

//	initialized_usePFF();
}

void CGraphicMFCKDYView::drawPloy(CDC* pDC, int number, int* polypoints) {
	// pen, fill
	BOOL penCheck = FALSE, fillCheck = FALSE;
	CPen pen, * pOldPen;
	CBrush brush, * pOldBrush;
	LOGBRUSH lb;
	DWORD pstyle;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	if (usePFF.useFillCheck == TRUE) {
		lb.lbHatch = usePFF.pattern;
		lb.lbColor = usePFF.fill_color;
		if (usePFF.pattern == MFC_SOLID_FILL)
			lb.lbStyle = BS_SOLID;
		else if (usePFF.pattern == MFC_EMPTY_FILL)
			lb.lbStyle = BS_HOLLOW;
		else
			lb.lbStyle = BS_HATCHED;

		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	else if (usePFF.useFillCheck == FALSE) {
		lb.lbHatch = NULL;
		lb.lbColor = changeBookColorToMFCColor(BLACK);
		lb.lbStyle = -1;
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}


	POINT* points = (POINT*)malloc(sizeof(POINT) * number);
	if (points == nullptr) {
		return;
	}
	memset(points, 0, sizeof(POINT) * number);
	BYTE* bytes = (BYTE*)malloc(sizeof(BYTE) * number);
	if (bytes == nullptr) {
		return;
	}
	memset(bytes, 0, sizeof(BYTE) * number);
	int j = 0;
	for (int i = 0; i < (number * 2); i++) {
		points[j].x = polypoints[i];
		i++;
		points[j].y = polypoints[i];

		if (j == 0)
			bytes[j] = PT_MOVETO;
		else
			bytes[j] = PT_LINETO;

		TRACE(L"%d,%d\n", points[j].x, points[j].y);
		j++;
	}

	pDC->PolyDraw(points, bytes, number);

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}

//	initialized_usePFF();
}

void CGraphicMFCKDYView::ellipse(CDC* pDC, int x, int y,
	int startAngle, int endAngle,
	int xradius, int yradius)
{
	// pen, fill
	BOOL penCheck = FALSE, fillCheck = FALSE;
	CPen pen, * pOldPen;
	CBrush brush, * pOldBrush;
	LOGBRUSH lb;
	DWORD pstyle;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	if (usePFF.useFillCheck == TRUE) {
		lb.lbHatch = usePFF.pattern;
		lb.lbColor = usePFF.fill_color;
		if (usePFF.pattern == MFC_SOLID_FILL)
			lb.lbStyle = BS_SOLID;
		else if (usePFF.pattern == MFC_EMPTY_FILL)
			lb.lbStyle = BS_HOLLOW;
		else
			lb.lbStyle = BS_HATCHED;

		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	else if (usePFF.useFillCheck == FALSE) {
		lb.lbHatch = NULL;
		lb.lbColor = changeBookColorToMFCColor(BLACK);
		lb.lbStyle = -1;
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}

	int leftTopX = x - xradius;
	int leftTopY = y + yradius;
	int rightBottomX = x + xradius;
	int rightBottomY = y - yradius;

	if (startAngle == 0)
	{
		//온전한 원
		setarccoords(x, y, startAngle, endAngle, xradius, yradius);
		for (int i = 0; i <= 360; i++)
			putpixel(pDC, x + (int)(xradius * cos(i * PI / 180)), y - (int)(yradius * sin(i * PI / 180)), 
				changeMFCColorToBookColor(usePFF.pen_color));
		//		pDC->Ellipse(leftTopX, leftTopY,
		//			rightBottomX, rightBottomY);
	}
	else {
		//온전치 않은 원
		int realStartAngle = 360 - startAngle;
		int realEndAngle = 360 - endAngle;


		int startX_dot = x + (round((xradius * cos(getRadian(realStartAngle)))));
		int startY_dot = y + (round((yradius * sin(getRadian(realStartAngle)))));
		int endX_dot = x + (round((xradius * cos(getRadian(realEndAngle)))));
		int endY_dot = y + (round((yradius * sin(getRadian(realEndAngle)))));

		setarccoords(x, y, startAngle, endAngle, xradius, yradius);
		pDC->Arc(leftTopX, leftTopY,
			rightBottomX, rightBottomY,
			startX_dot, startY_dot,
			endX_dot, endY_dot
		);
	}
	

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}

//	initialized_usePFF();
}

void CGraphicMFCKDYView::pieslice(CDC* pDC, int x, int y, int startAngle, int endAngle, int radius)
{
	// pen, fill
	BOOL penCheck = FALSE, fillCheck = FALSE;
	CPen pen, * pOldPen;
	CBrush brush, * pOldBrush;
	LOGBRUSH lb;
	DWORD pstyle;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	if (usePFF.useFillCheck == TRUE) {
		lb.lbHatch = usePFF.pattern;
		lb.lbColor = usePFF.fill_color;
		if (usePFF.pattern == MFC_SOLID_FILL)
			lb.lbStyle = BS_SOLID;
		else if (usePFF.pattern == MFC_EMPTY_FILL)
			lb.lbStyle = BS_HOLLOW;
		else
			lb.lbStyle = BS_HATCHED;

		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	else if (usePFF.useFillCheck == FALSE) {
		lb.lbHatch = NULL;
		lb.lbColor = changeBookColorToMFCColor(BLACK);
		lb.lbStyle = -1;
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}

	//원호(파이) 그리기
//	arcCircle_book(pDC, x, y, startAngle, endAngle, radius);
	int leftTopX = x - radius;
	int leftTopY = y + radius;
	int rightBottomX = x + radius;
	int rightBottomY = y - radius;

	int realStartAngle = 360 - startAngle;
	int realEndAngle = 360 - endAngle;

	int startX_dot = x + (round((radius * cos(getRadian(realStartAngle)))));
	int startY_dot = y + (round((radius * sin(getRadian(realStartAngle)))));
	int endX_dot = x + (round((radius * cos(getRadian(realEndAngle)))));
	int endY_dot = y + (round((radius * sin(getRadian(realEndAngle)))));

	setarccoords(leftTopX, leftTopY, startAngle, endAngle, radius, radius);
	pDC->Pie(leftTopX, leftTopY,
		rightBottomX, rightBottomY,
		startX_dot, startY_dot,
		endX_dot, endY_dot
	);

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}

//	initialized_usePFF();
}

void CGraphicMFCKDYView::fillellipse(CDC* pDC, int x, int y, int xradius, int yradius)
{
	// pen, fill
	BOOL penCheck = FALSE, fillCheck = FALSE;
	CPen pen, * pOldPen;
	CBrush brush, * pOldBrush;
	LOGBRUSH lb;
	DWORD pstyle;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	if (usePFF.useFillCheck == TRUE) {
		lb.lbHatch = usePFF.pattern;
		lb.lbColor = usePFF.fill_color;
		if (usePFF.pattern == MFC_SOLID_FILL)
			lb.lbStyle = BS_SOLID;
		else if (usePFF.pattern == MFC_EMPTY_FILL)
			lb.lbStyle = BS_HOLLOW;
		else
			lb.lbStyle = BS_HATCHED;

		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	else if (usePFF.useFillCheck == FALSE) {
		lb.lbHatch = NULL;
		lb.lbColor = changeBookColorToMFCColor(BLACK);
		lb.lbStyle = -1;
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}

	int leftTopX = x - xradius;
	int leftTopY = y + yradius;
	int rightBottomX = x + xradius;
	int rightBottomY = y - yradius;

	setarccoords(leftTopX, leftTopY, rightBottomX, rightBottomY);
	pDC->Ellipse(leftTopX, leftTopY,
		rightBottomX, rightBottomY);

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}

//	initialized_usePFF();
}

void CGraphicMFCKDYView::fillPoly(CDC* pDC, int number, int* polypoints) {

	// pen, fill
	BOOL penCheck = FALSE, fillCheck = FALSE;
	CPen pen, * pOldPen;
	CBrush brush, * pOldBrush;
	LOGBRUSH lb;
	DWORD pstyle;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	if (usePFF.useFillCheck == TRUE) {
		lb.lbHatch = usePFF.pattern;
		lb.lbColor = usePFF.fill_color;
		if (usePFF.pattern == MFC_SOLID_FILL)
			lb.lbStyle = BS_SOLID;
		else if (usePFF.pattern == MFC_EMPTY_FILL)
			lb.lbStyle = BS_HOLLOW;
		else
			lb.lbStyle = BS_HATCHED;

		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	else if (usePFF.useFillCheck == FALSE) {
		lb.lbHatch = NULL;
		lb.lbColor = changeBookColorToMFCColor(BLACK);
		lb.lbStyle = -1;
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}

	POINT* points = (POINT*)malloc(sizeof(POINT) * number);
	if (points == nullptr) {
		return;
	}
	memset(points, 0, sizeof(POINT) * number);
	BYTE* bytes = (BYTE*)malloc(sizeof(BYTE) * number);
	if (bytes == nullptr) {
		return;
	}
	memset(bytes, 0, sizeof(BYTE) * number);
	int j = 0;
	for (int i = 0; i < (number * 2); i++) {
		points[j].x = polypoints[i];
		i++;
		points[j].y = polypoints[i];

		if (j == 0)
			bytes[j] = PT_MOVETO;
		else
			bytes[j] = PT_LINETO;

		TRACE(L"%d,%d\n", points[j].x, points[j].y);
		j++;
	}

	int polyMode = pDC->GetPolyFillMode();
	pDC->SetPolyFillMode(WINDING);
	pDC->BeginPath();
	pDC->PolyDraw(points, bytes, number);
	pDC->EndPath();

	//다각형 색 채우기
	pDC->FillPath();
	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}

//	initialized_usePFF();
}

void CGraphicMFCKDYView::outtextxy(CDC* pDC, int x, int y, CString text)
{
	// pen, font
	CFont font, * pOldFont;
	BOOL penCheck = FALSE, fontCheck = FALSE;
	CPen pen, * pOldPen;
//	LOGBRUSH lb;
//	DWORD pstyle;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	if (usePFF.useFontCheck == TRUE) {
		font.CreateFont((usePFF.font_size + 1) * 16, (usePFF.font_size + 1) * 8,	//글자높이 , 글자너비
			usePFF.direction,											//출력 각도
			0,													//기준 선에서의 각도
			FW_NORMAL,											//글자 굵기
			FALSE,												//Italic 적용 여부
			FALSE,												//밑줄 적용 여부
			FALSE,												//취소선 적용 여부
			DEFAULT_CHARSET,									//문자셋 종류
			OUT_DEFAULT_PRECIS,									//출력정밀도
			CLIP_CHARACTER_PRECIS,								//클리핑정밀도
			DEFAULT_QUALITY,									//출력문자품질
			DEFAULT_PITCH | FF_SWISS,							//글꼴Pitch
			usePFF.fontStr);
		pOldFont = pDC->SelectObject(&font);
		pDC->SetTextColor(usePFF.pen_color);
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (usePFF.useFontCheck == FALSE) {
		font.CreateFont((0 + 1) * 16, (0 + 1) * 8,	//글자높이 , 글자너비
			HORIZ_DIR,											//출력 각도
			0,													//기준 선에서의 각도
			FW_NORMAL,											//글자 굵기
			FALSE,												//Italic 적용 여부
			FALSE,												//밑줄 적용 여부
			FALSE,												//취소선 적용 여부
			DEFAULT_CHARSET,									//문자셋 종류
			OUT_DEFAULT_PRECIS,									//출력정밀도
			CLIP_CHARACTER_PRECIS,								//클리핑정밀도
			DEFAULT_QUALITY,									//출력문자품질
			DEFAULT_PITCH | FF_SWISS,							//글꼴Pitch
			getFont_name(pDC,TRIPLEX_FONT));
		pOldFont = pDC->SelectObject(&font);
		pDC->SetTextColor(usePFF.pen_color);
		pDC->SetBkMode(TRANSPARENT);
	}

	pDC->TextOutW(x, y, text);

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
	if (fontCheck == TRUE) {
		DeleteObject(font);
	}

//	initialized_usePFF();

}

void CGraphicMFCKDYView::circle(CDC *pDC,int x, int y, int radius)
{
	// pen, fill
	BOOL penCheck = FALSE, fillCheck = FALSE;
	CPen pen, * pOldPen;
	CBrush brush, * pOldBrush;
	LOGBRUSH lb;
	DWORD pstyle;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	if (usePFF.useFillCheck == TRUE) {
		lb.lbHatch = usePFF.pattern;
		lb.lbColor = usePFF.fill_color;
		if (usePFF.pattern == MFC_SOLID_FILL)
			lb.lbStyle = BS_SOLID;
		else if (usePFF.pattern == MFC_EMPTY_FILL)
			lb.lbStyle = BS_HOLLOW;
		else
			lb.lbStyle = BS_HATCHED;

		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	else if (usePFF.useFillCheck == FALSE) {
		lb.lbHatch = NULL;
		lb.lbColor = changeBookColorToMFCColor(BLACK);
		lb.lbStyle = -1;
		brush.CreateBrushIndirect(&lb);
		pOldBrush = pDC->SelectObject(&brush);
		fillCheck = TRUE;
	}
	
	int leftTopX = x-radius;
	int leftTopY = y+radius;
	int rightBottomX = x+radius;
	int rightBottomY = y-radius;

//	double diagonal_value = diagonal(radius, radius);
	setarccoords(leftTopX, leftTopY, rightBottomX, rightBottomY);
	pDC->Ellipse(leftTopX,leftTopY,rightBottomX,rightBottomY);

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
	if (fillCheck == TRUE) {
		DeleteObject(brush);
	}

}

double diagonal(double a, double b) {
	//빗변구하기
	double result = 0.0;
	result = sqrt(pow(a,2)+pow(b,2));
	return result;
}

//using fill style count
int i_count = 0;
int j_count = 0;
BOOL usingCount = FALSE;

void initialize_fill_style_i_count(){
	i_count = 0;
}

void initialize_fill_style_j_count() {
	j_count = 0;
}

void initialize_fill_style_usingCount() {
	usingCount = FALSE;
}


std::vector<FILL_POINT> CGraphicMFCKDYView::setting_pattern(int leftTopX, int leftTopY, int rightBottomX, int rightBottomY)
{
	//bkPoint는 배경색인 부분의 rectangle 좌표만 return한다.
	std::vector<FILL_POINT> bkPoint;
	FILL_POINT fill_point;
	int width = rightBottomX - leftTopX;
	int height = rightBottomY - leftTopY;
	int defaultDivideValue = 50;
	BOOL randomCount = FALSE;
	int fill_leftTopX = leftTopX, fill_leftTopY = leftTopY, fill_rightBottomX, fill_rightBottomY;

	/*
	switch (fill_PatternData.pattern) {
	case EMPTY_FILL:
		usingCount = FALSE;
		break;
	case SOLID_FILL:
		usingCount = FALSE;
		break;
	case WIDE_DOT_FILL:
		usingCount = TRUE;
		break;
	case CLOSE_DOT_FILL:
		usingCount = TRUE;
		randomCount = TRUE;
	default:
		usingCount = FALSE;
		break;
	}
	*/

	if ((width > defaultDivideValue && height > defaultDivideValue) &&
		(usingCount != TRUE) && fill_PatternData.pattern != SOLID_FILL) {
		//한 면을 50개 단위로 나누어 각 부분들에 대한 색칠 여부를 책정해야하므로 각 면의 길이는 무조건 16이상이어야 한다.

		int one_fifty_width = floor(width / defaultDivideValue);
		int one_fifty_height = floor(height / defaultDivideValue);

		fill_rightBottomX = leftTopX + one_fifty_width;
		fill_rightBottomY = leftTopY + one_fifty_height;

		for (int i = 0; i < defaultDivideValue; i++) {
			for (int j = 0; j < defaultDivideValue; j++) {
				if (/*return_checkFillStyle(i, j, fill_PatternData.pattern, defaultDivideValue)*/TRUE) {
					fill_point.leftTopX = fill_leftTopX;
					fill_point.leftTopY = fill_leftTopY;
					fill_point.rightBottomX = fill_rightBottomX;
					fill_point.rightBottomY = fill_rightBottomY;
					bkPoint.push_back(fill_point);
				}
				fill_leftTopX += one_fifty_width;
				fill_rightBottomX = fill_leftTopX + one_fifty_width;
				//만약 fill_rightBottomX가 rightBottomX보다 크면
				//최대값(rightBottomX)을 fill_rightBottomX로 대입한다.
				if (fill_rightBottomX > rightBottomX)
					fill_rightBottomX = rightBottomX;
			}
			fill_leftTopY += one_fifty_height;
			fill_rightBottomY = fill_leftTopY + one_fifty_height;
			//만약 fill_rightBottomY가 rightBottomY보다 크면
			//최대값(rightBottomY)을 fill_rightBottomY로 대입한다.
			if (fill_rightBottomY > rightBottomY)
				fill_rightBottomY = rightBottomY;

			fill_leftTopX = leftTopX;
			//				fill_rightBottomX = leftTopX + one_sixteen_width;
			fill_rightBottomX = leftTopX + one_fifty_width;
		}
		/*
		switch (fill_PatternData.pattern) {
		case EMPTY_FILL:
			//배경색으로 채운다. 테두리만 나타냄
			//16등분의 각 끝만 채운다.
			//bkPoint size = 196
			for (int i = 0; i < 50; i++) {
				for (int j = 0; j < 50; j++) {
					if (return_checkFillStyle(i,j, fill_PatternData.pattern)) {
						fill_point.leftTopX = fill_leftTopX;
						fill_point.leftTopY = fill_leftTopY;
						fill_point.rightBottomX = fill_rightBottomX;
						fill_point.rightBottomY = fill_rightBottomY;
						bkPoint.push_back(fill_point);
					}
					fill_leftTopX += one_fifty_width;
					fill_rightBottomX = fill_leftTopX + one_fifty_width;
					//만약 fill_rightBottomX가 rightBottomX보다 크면
					//최대값(rightBottomX)을 fill_rightBottomX로 대입한다.
					if (fill_rightBottomX > rightBottomX)
						fill_rightBottomX = rightBottomX;
				}
				fill_leftTopY += one_fifty_height;
				fill_rightBottomY = fill_leftTopY + one_fifty_height;
				//만약 fill_rightBottomY가 rightBottomY보다 크면
				//최대값(rightBottomY)을 fill_rightBottomY로 대입한다.
				if (fill_rightBottomY > rightBottomY)
					fill_rightBottomY = rightBottomY;

				fill_leftTopX = leftTopX;
//				fill_rightBottomX = leftTopX + one_sixteen_width;
				fill_rightBottomX = leftTopX + one_fifty_width;
			}
			return bkPoint;
			break;
		case SOLID_FILL:
			return bkPoint;
			break;
		case LINE_FILL:

			break;
		case LTSLASH_FILL:
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 16; j++) {
					if (return_checkFillStyle(i, j, fill_PatternData.pattern)) {
						fill_point.leftTopX = fill_leftTopX;
						fill_point.leftTopY = fill_leftTopY;
						fill_point.rightBottomX = fill_rightBottomX;
						fill_point.rightBottomY = fill_rightBottomY;
						bkPoint.push_back(fill_point);
					}
					fill_leftTopX += one_fifty_width;
					fill_rightBottomX = fill_leftTopX + one_fifty_width;
					//만약 fill_rightBottomX가 rightBottomX보다 크면
					//최대값(rightBottomX)을 fill_rightBottomX로 대입한다.
					if (fill_rightBottomX > rightBottomX)
						fill_rightBottomX = rightBottomX;
				}
				fill_leftTopY += one_fifty_height;
				fill_rightBottomY = fill_leftTopY + one_fifty_height;
				//만약 fill_rightBottomY가 rightBottomY보다 크면
				//최대값(rightBottomY)을 fill_rightBottomY로 대입한다.
				if (fill_rightBottomY > rightBottomY)
					fill_rightBottomY = rightBottomY;

				fill_leftTopX = leftTopX;
				//				fill_rightBottomX = leftTopX + one_sixteen_width;
				fill_rightBottomX = leftTopX + one_fifty_width;
			}
			return bkPoint;
			break;
			break;
		case SLASH_FILL:

			break;
		case BKSLASH_FILL:

			break;
		case LTBKSLASH_FILL:

			break;
		case HATCH_FILL:

			break;
		case XHATCH_FILL:

			break;
		case INTERLEAVE_FILL:

			break;
		case WIDE_DOT_FILL:

			break;
		case CLOSE_DOT_FILL:

			break;
		case USER_FILL:
			//특수 케이스
			break;
		}
	}
	*/
	}
	else if (usingCount == TRUE && randomCount == TRUE) {
		
	}
	else if (fill_PatternData.pattern == SOLID_FILL) {
		return bkPoint;
	}
	else {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				fill_point.leftTopX = 0;
				fill_point.leftTopY = 0;
				if (i == 0 || i == height - 1) {
					fill_point.leftTopX = leftTopX + j;
					fill_point.leftTopY = leftTopY + i;
					fill_point.rightBottomX = 0;
					fill_point.rightBottomY = 0;
				}
				else {
					if (j == 0 || j == width - 1) {
						fill_point.leftTopX = leftTopX + j;
						fill_point.leftTopY = leftTopY + i;
						fill_point.rightBottomX = 0;
						fill_point.rightBottomY = 0;
					}
					else {
						if (i % 2 == 0) {
							if (j % 2 == 0) {
								fill_point.leftTopX = leftTopX + j;
								fill_point.leftTopY = leftTopY + i;
								fill_point.rightBottomX = 0;
								fill_point.rightBottomY = 0;
							}
						}
						else {
							if (j % 2 != 0) {
								fill_point.leftTopX = leftTopX + j;
								fill_point.leftTopY = leftTopY + i;
								fill_point.rightBottomX = 0;
								fill_point.rightBottomY = 0;
							}
						}
					}
				}
				if (fill_point.leftTopX != 0 || fill_point.leftTopY != 0) {
					bkPoint.push_back(fill_point);
				}
				else {
					if(leftTopX == 0 && leftTopY == 0)
						bkPoint.push_back(fill_point);
				}
			}
		}
	}
	initialize_fill_style_i_count();
	initialize_fill_style_j_count();
	initialize_fill_style_usingCount();
	return bkPoint;
}

/*
BOOL return_checkFillStyle(int i, int j,int pattern,int maxCount)
{
	//배경색으로 칠하는 좌표(i,j)에 부합될때 TRUE를 반환한다.
	BOOL check = FALSE;
	int i_plus = 1;
	switch (pattern) {
	case EMPTY_FILL:
		if ((i == 0 || i == 49)) {
			return FALSE;
		}
		else{
			//i is 1 ~ 48
			if ((j == 0) || (j == (maxCount - 1)))
				return FALSE;
			else
				return TRUE;
		}

		break;
	case SOLID_FILL:
		return TRUE;
		break;
	case LINE_FILL:
		//횡선?
		if ((i == 0 || i == (maxCount-1))) {
			check = FALSE;
		}
		else {
			if ((j == 0 || j == (maxCount - 1)))
				check = FALSE;
			else {
				if (i % 2 == 0)
					check = FALSE;
				else
					check = TRUE;
			}
		}
		return check;

		break;
	case LTSLASH_FILL:
		if ((i == 0 || i == (maxCount - 1))) {
			check = FALSE;
		}
		else {
			if (j == 0) {
				check = FALSE;
			}
			else if (j == (maxCount - 1)) {
				check = FALSE;
				i_count++;
			}
			else {
				if (j_count == (3 - i_count))
					check = FALSE;
				else
					check = TRUE;
				j_count++;
			}
		}
		if (j_count > 3) {
			initialize_fill_style_j_count();
		}
		
		if (i_count > 3)
			initialize_fill_style_i_count();

		return check;
		break;
	case SLASH_FILL:
		if ((i == 0 || i == (maxCount - 1))) {
			check = FALSE;
		}
		else {
			if (j == 0) {
				check = FALSE;
			}
			else if (j == (maxCount - 1)) {
				check = FALSE;
				i_count++;
			}
			else {
				if (j_count == (3 - i_count) || j_count == (2-i_count))
					check = FALSE;
				else
					check = TRUE;

				if (i_count == 3) {
					if (j_count == 3) {
						check = FALSE;
					}
				}
				j_count++;
			}
		}
		if (j_count > 3) {
			initialize_fill_style_j_count();
		}

		if (i_count > 3)
			initialize_fill_style_i_count();

		return check;
		break;
	case BKSLASH_FILL:
		if ((i == 0 || i == (maxCount - 1))) {
			check = FALSE;
		}
		else {
			if (j == 0) {
				check = FALSE;
			}
			else if (j == (maxCount - 1)) {
				check = FALSE;
				i_count++;
			}
			else {
				if (j_count == (i_count ) ||
					j_count == (1 + i_count))
					check = FALSE;
				else
					check = TRUE;

				if (i_count == 3) {
					if (j_count == 0) {
						check = FALSE;
					}
				}
				j_count++;
			}
		}
		if (j_count > 3) {
			initialize_fill_style_j_count();
		}

		if (i_count > 3)
			initialize_fill_style_i_count();

		return check;
		break;
	case LTBKSLASH_FILL:
		if ((i == 0 || i == (maxCount - 1))) {
			check = FALSE;
		}
		else {
			if (j == 0) {
				check = FALSE;
			}
			else if (j == (maxCount - 1)) {
				check = FALSE;
				i_count++;
			}
			else {
				if (j_count == i_count)
					check = FALSE;
				else
					check = TRUE;
				j_count++;
			}
		}
		if (j_count > 3) {
			initialize_fill_style_j_count();
		}

		if (i_count > 3)
			initialize_fill_style_i_count();

		return check;
		break;
	case HATCH_FILL:
		//바둑판 모양
		if ((i == 0 || i == (maxCount - 1))) {
			check = FALSE;
		}
		else {
			if (j == 0) {
				check = FALSE;
			}
			else if (j == (maxCount - 1)) {
				check = FALSE;
				i_count++;
			}
			else {
				if ((j_count == 0 || j_count == 3) && (i_count == 1 || i_count == 4))
					check = TRUE;
				else
					check = FALSE;
				j_count++;
			}
		}
		if (j_count > 3) {
			initialize_fill_style_j_count();
		}

		if (i_count > 3)
			initialize_fill_style_i_count();

		return check;

		break;
	case XHATCH_FILL:
		//체스판 모양
		if ((i == 0 || i == (maxCount - 1))) {
			check = FALSE;
		}
		else {
			if (j == 0 || j== (maxCount - 1)) {
				check = FALSE;
				if (j == (maxCount - 1))
					i_count++;
			}
			else {
				int k = 0;
				if (i_count == 0 || i_count == 1) {
					if (j_count == 0 || j_count == 1)
						check = FALSE;
					else
						check = TRUE;
				}
				else {
					if (j_count == 0 || j_count == 1)
						check = TRUE;
					else
						check = FALSE;
				}
				j_count++;
			}
		}
		if (j_count > 3) {
			initialize_fill_style_j_count();
		}

		if (i_count > 3)
			initialize_fill_style_i_count();

		return check;
		break;
	case INTERLEAVE_FILL:

		break;
	case WIDE_DOT_FILL:
		if ((i == 0 || i == (maxCount - 1))) {
			check = FALSE;
		}
		else {
			if (j == 0 || j == (maxCount - 1)) {
				check = FALSE;
				if (j == (maxCount - 1))
					i_count++;
			}
			else {
				int k = 0;
				if (i_count == 0 || i_count == 2) {
					switch (j_count)
					{
					case 0:
						check = TRUE;
						break;
					case 1:
						check = FALSE;
						break;
					case 2:
						check = TRUE;
						break;
					case 3:
						check = FALSE;
						break;
					default:
						check = FALSE;
						break;
					}
				}
				else {
					switch (j_count)
					{
					case 0:
						check = FALSE;
						break;
					case 1:
						check = TRUE;
						break;
					case 2:
						check = FALSE;
						break;
					case 3:
						check = TRUE;
						break;
					default:
						check = FALSE;
						break;
					}
				}
				j_count++;
			}
		}
		if (j_count > 3) {
			initialize_fill_style_j_count();
		}

		if (i_count > 3)
			initialize_fill_style_i_count();

		return check;
		break;
	case CLOSE_DOT_FILL:

		break;
	case USER_FILL:
		//특수 케이스
		break;
	}
}
*/
void CGraphicMFCKDYView::initialize_fill_pattern()
{
	if (fill_PatternData.checkUse) {
		fill_PatternData.checkUse = 0;
		fill_PatternData.pattern = EMPTY_FILL;
		fill_PatternData.color = RGB(0, 0, 0);
	}
}

double getRadian(int num) {
	return num * (PI / 180);
}

// CGraphicMFCKDYView printing

BOOL CGraphicMFCKDYView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicMFCKDYView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicMFCKDYView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGraphicMFCKDYView diagnostics

#ifdef _DEBUG
void CGraphicMFCKDYView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicMFCKDYView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicMFCKDYDoc* CGraphicMFCKDYView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicMFCKDYDoc)));
	return (CGraphicMFCKDYDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicMFCKDYView message handlers

BOOL CGraphicMFCKDYView::OnEraseBkgnd(CDC* pDC,int color)
{
	// TODO: Add your message handler code here and/or call default
//	return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

BOOL CGraphicMFCKDYView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	
		return CView::OnEraseBkgnd(pDC);
//	return TRUE;
}

HBRUSH CGraphicMFCKDYView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor,int color)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);

	int colorNum = changeBookColorToMFCColor(color);
	pDC->SetBkColor(colorNum);
	
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
//	return hbr;
	return (HBRUSH)::GetStockObject(NULL_BRUSH);
}

BOOL CGraphicMFCKDYView::checkingExistColorSetting()
{
	BOOL check = FALSE;
	if (penData.checkUse == TRUE)
		check = TRUE;
	else if (fill_PatternData.checkUse == TRUE)
		check = TRUE;
	else if (bkData.checkUse == TRUE)
		check = TRUE;
	else
		check = FALSE;

	return check;
}

void CGraphicMFCKDYView::initialized_usePFF()
{
	if (usePFF.usePenCheck == TRUE) {
		usePFF.usePenCheck = FALSE;
		usePFF.pen_color = RGB(0, 0, 0);
		usePFF.pen_nWidth = NORM_WIDTH;
		usePFF.pen_style = PS_SOLID;
	}
	if (usePFF.useFillCheck == TRUE) {
		usePFF.useFillCheck = FALSE;
		usePFF.fill_color = RGB(0, 0, 0);
		usePFF.pattern = 0;
	}
	if (usePFF.useFontCheck == TRUE) {
		usePFF.useFontCheck = FALSE;
		usePFF.font = TRIPLEX_FONT;
		usePFF.direction = HORIZ_DIR;
		usePFF.font_size = 0;
	}

	//최초 실행
	if (usePFF.usePenCheck != TRUE && usePFF.usePenCheck != FALSE) {
//		usePFF.usePenCheck = FALSE;
//		usePFF.useFillCheck = FALSE;
//		usePFF.useFontCheck = FALSE;

		usePFF.pen_color = RGB(0, 0, 0);
		usePFF.pen_nWidth = NORM_WIDTH;
		usePFF.pen_style = PS_SOLID;
		
		usePFF.font = TRIPLEX_FONT;
		usePFF.direction = HORIZ_DIR;
		usePFF.upattern = 0;
		usePFF.font_size = 0;

		usePFF.fill_color = RGB(0, 0, 0);
		usePFF.pattern = 0;
	}
}

int changeBookPatternToMFCPattern(int pattern)
{
	/*
	int return_pattern;
	switch (pattern) {
	case EMPTY_FILL:
		return_pattern = 0;
		break;
	case SOLID_FILL:
		return_pattern;
	}

	return return_pattern;
	*/
	return 0;
}

void CGraphicMFCKDYView::lineto(CDC* pDC, int endX, int endY)
{
	// pen
	BOOL penCheck = FALSE;
	CPen pen, * pOldPen;
	if (usePFF.usePenCheck == TRUE) {
		pen.CreatePen(usePFF.pen_style, usePFF.pen_nWidth, usePFF.pen_color);
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}
	else if (usePFF.usePenCheck == FALSE) {
		pen.CreatePen(PS_SOLID, NORM_WIDTH, changeBookColorToMFCColor(BLACK));
		pOldPen = pDC->SelectObject(&pen);
		penCheck = TRUE;
	}

	pDC->LineTo(endX, endY);

	if (penCheck == TRUE) {
		DeleteObject(pen);
	}
}
