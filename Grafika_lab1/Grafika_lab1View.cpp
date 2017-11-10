
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

	pDC->SetMapMode(MM_ANISOTROPIC);
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
