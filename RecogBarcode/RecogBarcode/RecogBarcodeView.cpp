
// RecogBarcodeView.cpp: CRecogBarcodeView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "RecogBarcode.h"
#endif

#include "MainFrm.h"
#include "RecogBarcodeDoc.h"
#include "RecogBarcodeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRecogBarcodeView

IMPLEMENT_DYNCREATE(CRecogBarcodeView, CScrollView)

BEGIN_MESSAGE_MAP(CRecogBarcodeView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_ZOOM1, &CRecogBarcodeView::OnViewZoom1)
	ON_COMMAND(ID_VIEW_ZOOM2, &CRecogBarcodeView::OnViewZoom2)
	ON_COMMAND(ID_VIEW_ZOOM3, &CRecogBarcodeView::OnViewZoom3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, &CRecogBarcodeView::OnUpdateViewZoom1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, &CRecogBarcodeView::OnUpdateViewZoom2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, &CRecogBarcodeView::OnUpdateViewZoom3)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CRecogBarcodeView 생성/소멸

CRecogBarcodeView::CRecogBarcodeView()
	: m_nZoom(1) // 이미지 배율
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CRecogBarcodeView::~CRecogBarcodeView()
{
}

BOOL CRecogBarcodeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CRecogBarcodeView 그리기

void CRecogBarcodeView::OnDraw(CDC* pDC)
{
	CRecogBarcodeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();
		pDoc->m_Dib.Draw(pDC->m_hDC, 0, 0, w*m_nZoom, h*m_nZoom);
	}
}

void CRecogBarcodeView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizeToFit();
}

void CRecogBarcodeView::SetScrollSizeToFit(void)
{
	CSize sizeTotal;

	CRecogBarcodeDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();

		sizeTotal.cx = w * m_nZoom;
		sizeTotal.cy = h * m_nZoom;
	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 100;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(TRUE);
}

void CRecogBarcodeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRecogBarcodeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRecogBarcodeView 진단

#ifdef _DEBUG
void CRecogBarcodeView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CRecogBarcodeView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CRecogBarcodeDoc* CRecogBarcodeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRecogBarcodeDoc)));
	return (CRecogBarcodeDoc*)m_pDocument;
}
#endif //_DEBUG


// CRecogBarcodeView 메시지 처리기


BOOL CRecogBarcodeView::OnEraseBkgnd(CDC* pDC)
{
	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
	FillOutsideRect(pDC, &br);
	return TRUE;
}


void CRecogBarcodeView::OnViewZoom1()
{
	m_nZoom = 1;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CRecogBarcodeView::OnViewZoom2()
{
	m_nZoom = 2;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CRecogBarcodeView::OnViewZoom3()
{
	m_nZoom = 3;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CRecogBarcodeView::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 1);
}


void CRecogBarcodeView::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 2);
}


void CRecogBarcodeView::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 3);
}


void CRecogBarcodeView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pt = point + GetScrollPosition();
	pt.x /= m_nZoom;
	pt.y /= m_nZoom;
	ShowImageInfo(pt);

	CScrollView::OnMouseMove(nFlags, point);
}

void CRecogBarcodeView::ShowImageInfo(CPoint point)
{
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CRecogBarcodeDoc* pDoc = GetDocument();
	int w = pDoc->m_Dib.GetWidth();
	int h = pDoc->m_Dib.GetHeight();
	int c = pDoc->m_Dib.GetPaletteNums();
	CString strText;

	if (point.x >= 0 && point.y >= 0 && point.x < w && point.y < h)
	{
		strText.Format(_T("(%d, %d)"), point.x, point.y);
		pFrame->m_wndStatusBar.SetPaneText(0, strText);
	}

	if (c == 0)
	{
		strText.Format(_T("w:%d h:%d c:16M"), w, h);
	}
	else
	{
		strText.Format(_T("w:%d h:%d c:%d"), w, h, c);
	}
	pFrame->m_wndStatusBar.SetPaneText(1, strText);
}
