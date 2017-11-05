
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

	POINT ptsPlafon[4] = { { 0, 500 },{ 500, 500 },{ 450, 450 },{ 50, 450 } };
	POINT ptsLevaStrana[4] = { { 0, 500 },{ 50, 450 },{ 50, 50 },{ 0, 0 } };
	POINT ptsPatos[4] = { { 0, 0 },{ 50, 50 },{ 450, 50 },{ 500, 0 } };
	POINT ptsDesnaStrana[4] = { { 500, 0 },{ 450, 50 },{ 450, 450 },{ 500, 500 } };
	POINT ptsVrata[4] = { {455, 45}, {455, 400}, {490, 430}, {490, 10} };
	POINT ptsStranaOrmara[4] = { {70, 400}, {85, 380}, {85, 50}, {70, 30} };

	//gornja vrata ormara koordinate (400 ukupna visina => 40, 390, 55, 200

	CBrush okerCetka(RGB(255, 192, 128));
	CBrush tamnijaOkerCetka(RGB(195, 147, 98));
	CBrush braon(RGB(132, 99, 66));
	CBrush narandzasta(RGB(234, 155, 3));

	CPen okerPen(PS_SOLID, 0.9, RGB(99, 39, 23));
	CPen *defaultPen = pDC->SelectObject(&okerPen);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(500, 500);
	pDC->SetViewportExt(rect.right, -rect.bottom);
	pDC->SetWindowOrg(0, 500);

	//SOBA

	pDC->Polygon(ptsPlafon, 4);
	
	CBrush *staraCetka = pDC->SelectObject(&okerCetka);
	pDC->Rectangle(50, 50, 450, 450);
	
	pDC->SelectObject(&tamnijaOkerCetka);
	pDC->Polygon(ptsLevaStrana, 4);
	pDC->Polygon(ptsDesnaStrana, 4);

	pDC->SelectStockObject(LTGRAY_BRUSH);
	pDC->Polygon(ptsPatos, 4);

	//VRATA
	pDC->SelectObject(&braon);
	pDC->Polygon(ptsVrata, 4);
	pDC->SelectObject(&narandzasta);
	//pDC->Ellipse(480, 198, 488, 213);
	pDC->Ellipse(475, 203, 485, 216);
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Ellipse(482, 185, 484, 195);

	//IKEIN ORMAR
	pDC->SelectObject(&braon);
	pDC->Rectangle(30, 30, 70, 400);
	pDC->Polygon(ptsStranaOrmara, 4);
	pDC->Rectangle(33, 390, 50, 160);
	pDC->Rectangle(50, 390, 67, 160);
	pDC->Rectangle(33, 40, 67, 90);
	pDC->Rectangle(33, 100, 67, 150);
	pDC->SelectObject(&narandzasta);
	pDC->Ellipse(43, 265, 48, 272);
	pDC->Ellipse(52, 265, 57, 272);
	pDC->Ellipse(47, 60, 53, 69);
	pDC->Ellipse(47, 120, 53, 129);

	//Inventar
	pDC->SelectStockObject(LTGRAY_BRUSH);
	CrtajInventar(pDC);

	/*CPen braonOlovka(PS_SOLID, 2, RGB(61, 13, 2));
	CPen* defaultPen = pDC->SelectObject(&braonOlovka);
	
	CBrush braonCetka(RGB(132, 99, 66));*/


	/*CrtajSobu(pDC, rect);
	pDC->SelectStockObject(LTGRAY_BRUSH);
	CrtajInventar(pDC);

	CBrush* defaultCetka = pDC->SelectObject(&braonCetka);
	CrtajRegal(pDC, rect);*/
}

//Funkcije za iscrtavanje lab vezbe

//ROOM DRAWING
void CGrafikalab1View::CrtajSobu(CDC* pDC, CRect rect)
{
	POINT ptsPlafon[4]     =  { { 0, 0 }, 
							    { rect.Width(), 0 }, 
							    { rect.Width() - 75, 75 }, 
							    { 75, 75 } };

	POINT ptsLevaStrana[4] =  { { 0, 0 }, 
							    {75, 75}, 
							    {75, rect.Height() - 75}, 
							    {0, rect.Height()} };
	
	POINT ptsDesnaStrana[4] = { {rect.Width() - 75, 75}, 
								{rect.Width(), 0}, 
								{rect.Width(), rect.Height()}, 
								{rect.Width() - 75, rect.Height() - 75 } };

	POINT ptsPatos[4]       = { {0, rect.Height() },
								{75, rect.Height() - 75}, 
								{rect.Width() - 75, rect.Height() - 75 },
								{rect.Width(), rect.Height() } };
	
	pDC->Polygon(ptsPlafon, 4);
	CBrush okerCetka(RGB(255, 192, 128));
	CBrush tamnaOkerCetka(RGB(195, 147, 98));
	CBrush* staraCetka = pDC->SelectObject(&okerCetka);
	pDC->Rectangle(75, 75, rect.Width() - 75, rect.Height() - 75);
	pDC->SelectObject(&tamnaOkerCetka);
	pDC->Polygon(ptsLevaStrana, 4);
	pDC->Polygon(ptsDesnaStrana, 4);
	pDC->SelectStockObject(LTGRAY_BRUSH);
	pDC->Polygon(ptsPatos, 4);

	pDC->SelectObject(&staraCetka);
	okerCetka.DeleteObject();
	tamnaOkerCetka.DeleteObject();
}

//DRAWING PLAKAR (:D)
void CGrafikalab1View::CrtajRegal(CDC* pDC, CRect rect)
{
	POINT ptsDesnaStranaRegala[4] = { {170, 120}, 
									  {210, 160}, 
									  {210, rect.Height() - 75}, 
									  {170, rect.Height() - 35} };

	pDC->Rectangle(35, 120, 170, rect.Height() - 35);
	pDC->Polygon(ptsDesnaStranaRegala, 4);
	pDC->Rectangle(45, 135, 100, rect.Height() - 200);
	pDC->Rectangle(101, 135, 160, rect.Height() - 200);
	CBrush narandzasta(RGB(237, 156, 0));
	CBrush* staraCetka = pDC->SelectObject(&narandzasta);
	pDC->Ellipse(82, (int)((rect.Height() - 200) - 135) / 2 + 120, 95, (int)((rect.Height() - 200) - 135) / 2 + 135);
}

//DRAWING INVENTORY
void CGrafikalab1View::CrtajInventar(CDC* pDC)
{
	pDC->RoundRect(10, 490, 40, 430, 10, 10);
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
	CString strMessage;

	strMessage.Format(_T("(x, y) = %d %d"), point.x, point.y);

	AfxMessageBox(strMessage, MB_OK);

	CView::OnLButtonDown(nFlags, point);
}

void CGrafikalab1View::OnMouseMove(UINT nFlags, CPoint point)
{

	CString strMessage;

	strMessage.Format(_T("(x, y) = %d %d"), point.x, point.y);

	AfxMessageBox(strMessage, MB_OK);

	CView::OnMouseMove(nFlags, point);
}
