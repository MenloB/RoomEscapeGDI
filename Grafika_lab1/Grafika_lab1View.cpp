
// Grafika_lab1View.cpp : implementation of the CGrafikalab1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Grafika_lab1.h"
#endif

#include "Grafika_lab1Doc.h"
#include "Grafika_lab1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

// CGrafikalab1View

IMPLEMENT_DYNCREATE(CGrafikalab1View, CView)

BEGIN_MESSAGE_MAP(CGrafikalab1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGrafikalab1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGrafikalab1View construction/destruction

CGrafikalab1View::CGrafikalab1View()
{
	// TODO: add construction code here
	m_hit         = false;
	kljucKliknuto = false;
	vrataKliknuto = false;
	levaVratanca  = CRect(33, 390, 50, 160);
	kljuc         = CRect(34, 180, 49, 161);
}

CGrafikalab1View::~CGrafikalab1View()
{
}

BOOL CGrafikalab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGrafikalab1View drawing

void CGrafikalab1View::OnDraw(CDC* pDC)
{
	CGrafikalab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(&rect);

	CBrush okerCetka(RGB(99, 39, 23));
	CBrush *staraCetka = pDC->SelectObject(&okerCetka);

	//gornja vrata ormara koordinate (400 ukupna visina => 40, 390, 55, 200


	CPen okerPen(PS_SOLID, 0.9, RGB(99, 39, 23));
	CPen *defaultPen = pDC->SelectObject(&okerPen);

	int mapModeOld = pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(500, 500);
	pDC->SetViewportExt(rect.right, -rect.bottom);
	pDC->SetWindowOrg(0, 500);

	//SOBA
	CrtajSobu(pDC);

	//VRATA
	if (kljucKliknuto && vrataKliknuto)
	{
		CrtajOtvorenaVrata(pDC);
	}
	else {
		CrtajVrata(pDC);
	}
	//IKEIN ORMAR
	if (!m_hit)
		CrtajRegal(pDC);
	else
	{
		CrtajOtvorenRegal(pDC);
		//kljuc
		IscrtajKljuc(pDC);
	}

	//Inventar
	pDC->SelectStockObject(LTGRAY_BRUSH);
	CrtajInventar(pDC);

	//garnisna
	CBrush braon(RGB(132, 99, 66));
	pDC->SelectObject(&braon);
	CrtajGarnisnu(pDC);

	//prozor
	CrtajProzor(pDC);

	//zaveZa
	CrtajZavesu(pDC);

	if (kljucKliknuto) //ako je kliknuto na kljuc
	{
		CrtajKljucUInventaru(pDC);
		CrtajOtvorenRegal(pDC);
	}

	pDC->Rectangle(350, 400, 450, 400);

	int mapModePrev = pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(rect.right, rect.bottom);
	pDC->SetViewportExt(rect.right, -rect.bottom);
	pDC->SetWindowOrg(0, rect.bottom);

	//int	nHeight	= 20; // OVO MORA DA SE NAVEDE
	//int nWidth = 0;
	//int nEsc = 0;
	//int nOrient	= 0;
	//int nWeight	= 0;
	//BYTE bItalic = 0;
	//BYTE bUnderline	= 0;
	//BYTE cStrikeOut	= 0;
	//BYTE nCharSet = 0;
	//BYTE nOutPrecision = 0;
	//BYTE nClipPrecision = 0;
	//BYTE nQuality = 0;
	//BYTE nPitchAndFamily = 0;
	//CString	sFaceName =	_T("Arial");

	//CFont font;
	//font.CreateFontW(nHeight, nWidth, nEsc, nOrient, nWeight, bItalic, bUnderline, 
	//	cStrikeOut, nCharSet, nOutPrecision, nClipPrecision, nQuality, nPitchAndFamily, sFaceName);
	//pDC->TextOut(100, 100, "RADI");

	XFORM Xform, XformOld;
	DWORD dw;

	int PrevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	BOOL b = GetWorldTransform(pDC->m_hDC, &XformOld);
	dw = GetLastError();

	Xform.eM11 = (FLOAT) 1.0;
	Xform.eM12 = (FLOAT) 0.0;
	Xform.eM21 = (FLOAT) 0.0;
	Xform.eM22 = (FLOAT) 1.0;
	Xform.eDx = (FLOAT) rect.right - rect.right/3;
	Xform.eDy = (FLOAT) 200;

	b = SetWorldTransform(pDC->m_hDC, &Xform);
	dw = GetLastError();

	//SAT BUDI BOG S NAMA
	CrtajSat(pDC);

	/*b = SetWorldTransform(pDC->m_hDC, &XformOld);
	dw = GetLastError();

	SetGraphicsMode(pDC->m_hDC, PrevMode);*/

	Xform.eM12 = (FLOAT) cos(M_PI_4);
	Xform.eM12 = (FLOAT) sin(M_PI_4);
	Xform.eM21 = (FLOAT) -sin(M_PI_4);
	Xform.eM22 = (FLOAT) cos(M_PI_4);
	Xform.eDx = (FLOAT) 1.0;
	Xform.eDy = (FLOAT) 1.0;

	PrimeniTransformaciju(pDC, 0, 0, 100, 100, (FLOAT) 180, &Xform);

	pDC->SetMapMode(mapModePrev);
	pDC->SetWindowExt(500, 500);
	pDC->SetViewportExt(rect.right, -rect.bottom);
	pDC->SetWindowOrg(0, 500);

	pDC->SelectObject(&staraCetka);
}

//Function for drawing the scene

//Function for drawing a room
void CGrafikalab1View::CrtajSobu(CDC* pDC)
{
	CBrush okerCetka(RGB(255, 192, 128));
	CBrush tamnijaOkerCetka(RGB(195, 147, 98));

	POINT ptsPlafon[4] = { { 0, 500 },{ 500, 500 },{ 450, 450 },{ 50, 450 } };
	POINT ptsLevaStrana[4] = { { 0, 500 },{ 50, 450 },{ 50, 50 },{ 0, 0 } };
	POINT ptsPatos[4] = { { 0, 0 },{ 50, 50 },{ 450, 50 },{ 500, 0 } };
	POINT ptsDesnaStrana[4] = { { 500, 0 },{ 450, 50 },{ 450, 450 },{ 500, 500 } };

	pDC->SelectStockObject(WHITE_BRUSH);
	pDC->Polygon(ptsPlafon, 4);

	CBrush *staraCetka = pDC->SelectObject(&okerCetka);
	pDC->Rectangle(50, 50, 450, 450);

	pDC->SelectObject(&tamnijaOkerCetka);
	pDC->Polygon(ptsLevaStrana, 4);
	pDC->Polygon(ptsDesnaStrana, 4);

	pDC->SelectStockObject(LTGRAY_BRUSH);
	pDC->Polygon(ptsPatos, 4);
}

//Function for closet
void CGrafikalab1View::CrtajRegal(CDC* pDC)
{
	POINT ptsStranaOrmara[4] = { { 70, 400 },{ 85, 380 },{ 85, 50 },{ 70, 30 } };

	CBrush braon(RGB(132, 99, 66));
	CBrush narandzasta(RGB(234, 155, 3));

	pDC->SelectObject(&braon);
	pDC->Rectangle(30, 30, 70, 400);
	pDC->Polygon(ptsStranaOrmara, 4);
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Rectangle(33, 390, 50, 160);
	pDC->SelectObject(&braon);
	pDC->Rectangle(33, 390, 50, 160);
	pDC->Rectangle(50, 390, 67, 160);
	pDC->Rectangle(33, 40, 67, 90);
	pDC->Rectangle(33, 100, 67, 150);
	pDC->SelectObject(&narandzasta);
	pDC->Ellipse(43, 265, 48, 272);
	pDC->Ellipse(52, 265, 57, 272);
	pDC->Ellipse(47, 60, 53, 69);
	pDC->Ellipse(47, 120, 53, 129);
}

//otvoren regal
void CGrafikalab1View::CrtajOtvorenRegal(CDC* pDC)
{
	POINT ptsStranaOrmara[4] = { { 70, 400 },{ 85, 380 },{ 85, 50 },{ 70, 30 } };
	POINT ptsOtvorenaStrana[4] = { {33, 390}, {33, 160}, {20, 150}, {20, 400} };

	CBrush braon(RGB(132, 99, 66));
	CBrush narandzasta(RGB(234, 155, 3));

	pDC->SelectObject(&braon);
	pDC->Rectangle(30, 30, 70, 400);
	pDC->Polygon(ptsStranaOrmara, 4);
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Rectangle(33, 390, 50, 160);
	pDC->SelectObject(&braon);
	pDC->Polygon(ptsOtvorenaStrana, 4);
	pDC->Rectangle(50, 390, 67, 160);
	pDC->Rectangle(33, 40, 67, 90);
	pDC->Rectangle(33, 100, 67, 150);
	pDC->SelectObject(&narandzasta);
	pDC->Ellipse(52, 265, 57, 272);
	pDC->Ellipse(47, 60, 53, 69);
	pDC->Ellipse(47, 120, 53, 129);
}

//Iscrtava metafajl kljuca
void CGrafikalab1View::IscrtajKljuc(CDC* pDC) 
{
	HENHMETAFILE enhacedMetaFile = GetEnhMetaFile(_T("key.emf"));
	PlayEnhMetaFile(pDC->m_hDC, enhacedMetaFile, CRect(34, 180, 49, 161));
}

//Function for inventory
void CGrafikalab1View::CrtajInventar(CDC* pDC)
{
	pDC->RoundRect(10, 490, 40, 430, 10, 10);
}

//Function for path used to draw curtain
void CGrafikalab1View::CrtajZavesu(CDC* pDC)
{
	//zavesa
	pDC->MoveTo(197, 399);

	POINT zavesa[6] = { { 264, 187 },{ 254, 157 },{ 232, 187 },{ 204, 217 },{ 200, 187 },{ 197, 187 } };
	pDC->BeginPath();

	pDC->LineTo(267, 399);
	pDC->LineTo(267, 187);
	pDC->PolyBezierTo(zavesa, 6);
	pDC->LineTo(197, 399);
	pDC->EndPath();
	CBrush zavesaCetka(RGB(249, 254, 160));
	pDC->SelectObject(&zavesaCetka);
	pDC->StrokeAndFillPath();
}

//Function for drawing a window
void CGrafikalab1View::CrtajProzor(CDC* pDC)
{
	//Prozor
	pDC->Rectangle(200, 400, 263, 161);
	CBrush plava(RGB(0, 186, 219));
	pDC->SelectObject(&plava);
	pDC->Rectangle(203, 390, 230, 280);
	pDC->Rectangle(233, 390, 260, 280);
	pDC->Rectangle(203, 277, 230, 167);
	pDC->Rectangle(233, 277, 260, 167);
}

//Function for drawing round rectangle
void CGrafikalab1View::CrtajGarnisnu(CDC* pDC)
{
	//Garnisna
	pDC->RoundRect(190, 400, 273, 420, 15, 15);
}

//Crtaj vrata
void CGrafikalab1View::CrtajVrata(CDC* pDC) {
	
	POINT ptsVrata[4] = { { 455, 45 },{ 455, 400 },{ 490, 430 },{ 490, 10 } };
	
	CBrush braon(RGB(132, 99, 66));
	CBrush narandzasta(RGB(234, 155, 3));
	
	pDC->SelectObject(&braon);
	
	pDC->Polygon(ptsVrata, 4);
	pDC->SelectObject(&narandzasta);
	pDC->Ellipse(475, 203, 482, 213);
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Ellipse(482, 185, 484, 195);
}

void CGrafikalab1View::CrtajKljucUInventaru(CDC* pDC)
{
	HENHMETAFILE kljuc = GetEnhMetaFile(_T("key.emf"));
	PlayEnhMetaFile(pDC->m_hDC, kljuc, CRect(10, 490, 40, 430));
}

void CGrafikalab1View::CrtajOtvorenaVrata(CDC* pDC)
{
	POINT ptsVrata[4] = { { 455, 45 },{ 455, 400 },{ 490, 430 },{ 490, 10 } };

	CBrush braon(RGB(132, 99, 66));
	pDC->SelectObject(&braon);

	pDC->Rectangle(455, 45, 380, 400);
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Polygon(ptsVrata, 4);
}

void CGrafikalab1View::CrtajSat(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	XFORM XformOld, Xform;

	int PrevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	DWORD dw = GetLastError();

	CBrush braon(RGB(132, 99, 66));

	pDC->SelectObject(&braon);
	pDC->RoundRect(0, 130, 60, 0, 10, 10);
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->RoundRect(5, 127, 55, 3, 10, 10);
	CBrush zuta(RGB(242, 190, 19));
	pDC->SelectObject(&zuta);
	//zuti rect za klatno
	pDC->Rectangle(25, 127, 30, 19);
	//elipsa za klatno
	pDC->Ellipse(17, 14, 37, 34); //25 je sredina sata 
	pDC->SelectObject(&braon);
	//glavna elipsa
	pDC->Ellipse(-19, 210, 79, 110);
	pDC->SelectObject(&zuta);
	//zuta elipsa
	pDC->Ellipse(-15, 206, 75, 114);
	pDC->SelectStockObject(WHITE_BRUSH);
	//1. bela elispa
	pDC->Ellipse(1, 190, 59, 130);

	pDC->SelectStockObject(BLACK_PEN);

	for (int i = 0; i < 60; i++)
	{

		BOOL b = GetWorldTransform(pDC->m_hDC, &XformOld);

		Xform.eM11 = (FLOAT)cos(M_PI_2 + i*M_PI / 30.0);
		Xform.eM12 = (FLOAT)sin(M_PI_2 + i*M_PI / 30.0);
		Xform.eM21 = (FLOAT)-sin(M_PI_2 + i*M_PI / 30.0);
		Xform.eM22 = (FLOAT)cos(M_PI_2 + i*M_PI / 30.0);
		Xform.eDx = (FLOAT) 0.0;
		Xform.eDy = (FLOAT) 0.0;

		b = SetWorldTransform(pDC->m_hDC, &Xform);
		dw = GetLastError();

		Xform.eM11 = (FLOAT)1.0;
		Xform.eM12 = (FLOAT)0.0;
		Xform.eM21 = (FLOAT)0.0;
		Xform.eM22 = (FLOAT)1.0;
		Xform.eDx = (FLOAT) rect.right - rect.right / 3 + 30;
		Xform.eDy = (FLOAT) 360;

		b = ModifyWorldTransform(pDC->m_hDC, &Xform, MWT_RIGHTMULTIPLY);
		dw = GetLastError();

		pDC->MoveTo(0, 0);
		pDC->LineTo(0, 30);

		b = SetWorldTransform(pDC->m_hDC, &XformOld);
		dw = GetLastError();

	}

	CPen black2pxPen(PS_SOLID, 2, RGB(0, 0, 0));
	pDC->SelectObject(&black2pxPen);

	for (int i = 0; i < 12; i++)
	{
		BOOL b = GetWorldTransform(pDC->m_hDC, &XformOld);
		dw = GetLastError();

		Xform.eM11 = (FLOAT)cos(M_PI_2 + i * M_PI / 6);
		Xform.eM12 = (FLOAT)sin(M_PI_2 + i * M_PI / 6);
		Xform.eM21 = (FLOAT)-sin(M_PI_2 + i * M_PI / 6);
		Xform.eM22 = (FLOAT)cos(M_PI_2 + i * M_PI / 6);
		Xform.eDx = (FLOAT) 0.0;
		Xform.eDy = (FLOAT) 0.0;

		b = SetWorldTransform(pDC->m_hDC, &Xform);
		dw = GetLastError();

		Xform.eM11 = (FLOAT) 1.0;
		Xform.eM12 = (FLOAT) 0.0;
		Xform.eM21 = (FLOAT) 0.0;
		Xform.eM22 = (FLOAT) 1.0;
		Xform.eDx = (FLOAT)(rect.right - rect.right / 3) + 30;
		Xform.eDy = (FLOAT) 360;

		b = ModifyWorldTransform(pDC->m_hDC, &Xform, MWT_RIGHTMULTIPLY);
		dw = GetLastError();

		pDC->MoveTo(0, 0);
		pDC->LineTo(0, 30);

		b = SetWorldTransform(pDC->m_hDC, &XformOld);
		dw = GetLastError();
	}

	pDC->SelectStockObject(BLACK_PEN);
	pDC->SelectStockObject(WHITE_BRUSH);
	pDC->Ellipse(10, 180, 50, 140);

	//Skaliranje kazaljke
	Xform.eM11 = (FLOAT) 0.3;
	Xform.eM12 = (FLOAT) 0.0;
	Xform.eM21 = (FLOAT) 0.0;
	Xform.eM22 = (FLOAT) 0.3;
	Xform.eDx = (FLOAT) rect.right - 700;
	Xform.eDy = (FLOAT) rect.bottom - 400;

	pDC->ModifyWorldTransform(&Xform, MWT_RIGHTMULTIPLY);
	dw = GetLastError();

	////Pomeranje velike kazaljke
	//Xform.eM11 = (FLOAT) 1.0;
	//Xform.eM12 = (FLOAT) 0.0;
	//Xform.eM21 = (FLOAT) 0.0;
	//Xform.eM22 = (FLOAT) 1.0;
	//Xform.eDx = (FLOAT)rect.right - rect.right / 3 + 60;
	//Xform.eDy = (FLOAT)230;

	//pDC->ModifyWorldTransform(&Xform, MWT_RIGHTMULTIPLY);
	//dw = GetLastError();

	//Rotiranje za 180 stepeni
	/*Xform.eM11 = (FLOAT) cos(M_PI);
	Xform.eM12 = (FLOAT) sin(M_PI);
	Xform.eM21 = (FLOAT) -sin(M_PI);
	Xform.eM22 = (FLOAT) cos(M_PI);
	Xform.eDx = (FLOAT) 0.0;
	Xform.eDy = (FLOAT) 0.0;

	pDC->ModifyWorldTransform(&Xform, MWT_RIGHTMULTIPLY);
	dw = GetLastError();*/

	HENHMETAFILE vKazaljka = GetEnhMetaFile(_T("VelikaKazaljka.emf"));
	PlayEnhMetaFile(pDC->m_hDC, vKazaljka, CRect(0, 100, 18, 215));

	//Skaliranje kazaljke
	Xform.eM11 = (FLOAT) 1;
	Xform.eM12 = (FLOAT) 0.0;
	Xform.eM21 = (FLOAT) 0.0;
	Xform.eM22 = (FLOAT) 1;
	Xform.eDx = (FLOAT) -3;
	Xform.eDy = (FLOAT)rect.bottom - 640;

	pDC->ModifyWorldTransform(&Xform, MWT_RIGHTMULTIPLY);
	dw = GetLastError();

	HENHMETAFILE mKazaljka = GetEnhMetaFile(_T("MalaKazaljka.emf"));
	PlayEnhMetaFile(pDC->m_hDC, mKazaljka, CRect(0, 100, 36, 172));

	pDC->SetGraphicsMode(PrevMode);
}

void CGrafikalab1View::PrimeniTransformaciju(CDC* pDC, FLOAT cx, FLOAT cy, FLOAT rx, FLOAT ry, FLOAT alpha, XFORM* xOldForm)
{
	XFORM XformOld, XformAdditional;

	int PrevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	DWORD dw = GetLastError();

	BOOL b = GetWorldTransform(pDC->m_hDC, &XformOld);

	XformAdditional.eM11 = (FLOAT) 1.0;
	XformAdditional.eM12 = (FLOAT) 0.0;
	XformAdditional.eM21 = (FLOAT) 0.0;
	XformAdditional.eM22 = (FLOAT) 1.0;
	XformAdditional.eDx = (FLOAT) -100.0;
	XformAdditional.eDy = (FLOAT) 1.0;

	pDC->ModifyWorldTransform(xOldForm, MWT_RIGHTMULTIPLY);

	HENHMETAFILE mKazaljka = GetEnhMetaFile(_T("MalaKazaljka.emf"));
	PlayEnhMetaFile(pDC->m_hDC, mKazaljka, CRect(0, 100, 36, 172));
}

// CGrafikalab1View printing


void CGrafikalab1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGrafikalab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGrafikalab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGrafikalab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGrafikalab1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGrafikalab1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGrafikalab1View diagnostics

#ifdef _DEBUG
void CGrafikalab1View::AssertValid() const
{
	CView::AssertValid();
}

void CGrafikalab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrafikalab1Doc* CGrafikalab1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrafikalab1Doc)));
	return (CGrafikalab1Doc*)m_pDocument;
}
#endif //_DEBUG

// CGrafikalab1View message handlers


void CGrafikalab1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CRgn rgn;
	rgn.CreateRectRgn(levaVratanca.left, 
		levaVratanca.top, 
		levaVratanca.right, 
		levaVratanca.bottom);

	CRgn kljucRgn;
	kljucRgn.CreateRectRgn(kljuc.left, kljuc.top, kljuc.right, kljuc.bottom);

	//Rect Region nece da radi pa sam ovako resio problem hit testa

	if (point.x > 90 && point.x < 140)
	{
		if (point.y > 143 && point.y < 438)
		{
			m_hit = true;
			Invalidate();
		}
	}

	/*if (m_hit && kljucRgn.PtInRegion(point))
	{
		AfxMessageBox(_T("Kliknuto na kljuc"), MB_OK);
	}*/

	//region bi trebalo da bude u kvadratu (34, 180, 49, 161)

	if (m_hit && (point.x > 95 && point.x < 130)) //ako je otvoren ormar i ako je kliknuto na kljuc
	{
		if (point.y > 411 && point.y < 434)
		{
			kljucKliknuto = true;
			Invalidate();
		}
	}

	if (kljucKliknuto)
	{
		if (point.x > 1239 && point.x < 1335)
			if (point.y > 129 && point.y < 585)
			{
				vrataKliknuto = true;
				Invalidate();
			}
	}

	/*CString message;
	message.Format(_T("(x, y) = (%d %d)"), point.x, point.y);
	AfxMessageBox(message, MB_OK);*/

	CView::OnLButtonDown(nFlags, point);
}

void CGrafikalab1View::OnMouseMove(UINT nFlags, CPoint point)
{

	CString strMessage;

	strMessage.Format(_T("(x, y) = %d %d"), point.x, point.y);

	AfxMessageBox(strMessage, MB_OK);

	CView::OnMouseMove(nFlags, point);
}


void CGrafikalab1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {
	case 77:
		AfxMessageBox(_T("M"), MB_OK);
		break;
	case 86:
		AfxMessageBox(_T("V"), MB_OK);
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
