
// Grafika_lab1View.h : interface of the CGrafikalab1View class
//

#pragma once


class CGrafikalab1View : public CView
{
protected: // create from serialization only
	CGrafikalab1View();
	DECLARE_DYNCREATE(CGrafikalab1View)

// Attributes
public:
	CGrafikalab1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

#pragma region funkcije
	virtual void CrtajSobu(CDC* pDC);
	virtual void CrtajRegal(CDC* pDC);
	virtual void CrtajInventar(CDC* pDC);
	virtual void CrtajZavesu(CDC* pDC);
	virtual void CrtajProzor(CDC* pDC);
	virtual void CrtajGarnisnu(CDC* pDC);
	virtual void CrtajVrata(CDC* pDC);
	virtual void IscrtajKljuc(CDC* pDC);

	virtual void CrtajOtvorenRegal(CDC* pDC);
	virtual void CrtajKljucUInventaru(CDC* pDC);
	virtual void CrtajOtvorenaVrata(CDC* pDC);


	//2. LAB VEZBA
	virtual void CrtajSat(CDC* pDC);
	virtual void PrimeniTransformaciju(CDC* pDC, FLOAT cx, FLOAT cy, FLOAT rx, FLOAT ry, FLOAT alpha, XFORM* xOldForm);

#pragma endregion funkcije

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGrafikalab1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

private:
	BOOL m_hit;
	BOOL kljucKliknuto;
	BOOL vrataKliknuto;
	CRect vrata_rect;
	CRect levaVratanca;
	CRect kljuc;
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Grafika_lab1View.cpp
inline CGrafikalab1Doc* CGrafikalab1View::GetDocument() const
   { return reinterpret_cast<CGrafikalab1Doc*>(m_pDocument); }
#endif

