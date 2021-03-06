
// RecogBarcodeDoc.cpp: CRecogBarcodeDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "RecogBarcode.h"
#endif

#include "RecogBarcodeDoc.h"
#include "ArithmeticDlg.h"
#include "BinarizationDlg.h"
#include "BrightnessDlg.h"
#include "ColorCombineDlg.h"
#include "ContrastDlg.h"
#include "CropDlg.h"
#include "Decode.h"
#include "Dib.h"
#include "DibColor.h"
#include "DibEnhancement.h"
#include "DibFilter.h"
#include "DibGeometry.h"
#include "DibSegment.h"
#include "FileNewDlg.h"
#include "GammaCorrectionDlg.h"
#include "GaussianDlg.h"
#include "HarrisDlg.h"
#include "HistogramDlg.h"
#include "ResizeDlg.h"
#include "RotateDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRecogBarcodeDoc

IMPLEMENT_DYNCREATE(CRecogBarcodeDoc, CDocument)

BEGIN_MESSAGE_MAP(CRecogBarcodeDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CRecogBarcodeDoc::OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, &CRecogBarcodeDoc::OnEditCopy)
	ON_COMMAND(ID_IMAGE_INVERSE, &CRecogBarcodeDoc::OnImageInverse)
	ON_COMMAND(ID_IMAGE_BRIGHTNESS, &CRecogBarcodeDoc::OnImageBrightness)
	ON_COMMAND(ID_IMAGE_CONTRAST, &CRecogBarcodeDoc::OnImageContrast)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CRecogBarcodeDoc::OnGammaCorrection)
	ON_COMMAND(ID_VIEW_HISTOGRAM, &CRecogBarcodeDoc::OnViewHistogram)
	ON_COMMAND(ID_HISTO_EQUALIZE, &CRecogBarcodeDoc::OnHistoEqualize)
	ON_COMMAND(ID_IMAGE_ARITHMETIC, &CRecogBarcodeDoc::OnImageArithmetic)
	ON_COMMAND(ID_BITPLANE_SLICING, &CRecogBarcodeDoc::OnBitplaneSlicing)
	ON_COMMAND(ID_FILTER_LAPLACIAN, &CRecogBarcodeDoc::OnFilterLaplacian)
	ON_COMMAND(ID_FILTER_UNSHARP_MASK, &CRecogBarcodeDoc::OnFilterUnsharpMask)
	ON_COMMAND(ID_FILTER_MEAN, &CRecogBarcodeDoc::OnFilterMean)
	ON_COMMAND(ID_FILTER_WEIGHTED_MEAN, &CRecogBarcodeDoc::OnFilterWeightedMean)
	ON_COMMAND(ID_FILTER_GAUSSIAN, &CRecogBarcodeDoc::OnFilterGaussian)
	ON_COMMAND(ID_IMAGE_RESIZE, &CRecogBarcodeDoc::OnImageResize)
	ON_COMMAND(ID_IMAGE_ROTATE, &CRecogBarcodeDoc::OnImageRotate)
	ON_COMMAND(ID_EDGE_ROBERTS, &CRecogBarcodeDoc::OnEdgeRoberts)
	ON_COMMAND(ID_EDGE_PREWITT, &CRecogBarcodeDoc::OnEdgePrewitt)
	ON_COMMAND(ID_EDGE_SOBEL, &CRecogBarcodeDoc::OnEdgeSobel)
	ON_COMMAND(ID_HOUGH_LINE, &CRecogBarcodeDoc::OnHoughLine)
	ON_COMMAND(ID_HARRIS_CORNER, &CRecogBarcodeDoc::OnHarrisCorner)
	ON_COMMAND(ID_COLOR_GRAYSCALE, &CRecogBarcodeDoc::OnColorGrayscale)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GRAYSCALE, &CRecogBarcodeDoc::OnUpdateColorGrayscale)
	ON_COMMAND(ID_COLOR_SPLIT_RGB, &CRecogBarcodeDoc::OnColorSplitRgb)
	ON_UPDATE_COMMAND_UI(ID_COLOR_SPLIT_RGB, &CRecogBarcodeDoc::OnUpdateColorSplitRgb)
	ON_COMMAND(ID_COLOR_SPLIT_HSI, &CRecogBarcodeDoc::OnColorSplitHsi)
	ON_UPDATE_COMMAND_UI(ID_COLOR_SPLIT_HSI, &CRecogBarcodeDoc::OnUpdateColorSplitHsi)
	ON_COMMAND(ID_COLOR_SPLIT_YUV, &CRecogBarcodeDoc::OnColorSplitYuv)
	ON_UPDATE_COMMAND_UI(ID_COLOR_SPLIT_YUV, &CRecogBarcodeDoc::OnUpdateColorSplitYuv)
	ON_COMMAND(ID_COLOR_COMBINE_RGB, &CRecogBarcodeDoc::OnColorCombineRgb)
	ON_COMMAND(ID_COLOR_COMBINE_HSI, &CRecogBarcodeDoc::OnColorCombineHsi)
	ON_COMMAND(ID_COLOR_COMBINE_YUV, &CRecogBarcodeDoc::OnColorCombineYuv)
	ON_COMMAND(ID_COLOR_EDGE, &CRecogBarcodeDoc::OnColorEdge)
	ON_UPDATE_COMMAND_UI(ID_COLOR_EDGE, &CRecogBarcodeDoc::OnUpdateColorEdge)
	ON_COMMAND(ID_COLOR_EQUALIZE, &CRecogBarcodeDoc::OnColorEqualize)
	ON_UPDATE_COMMAND_UI(ID_COLOR_EQUALIZE, &CRecogBarcodeDoc::OnUpdateColorEqualize)
	ON_COMMAND(ID_SEGMENT_BINARIZATION, &CRecogBarcodeDoc::OnSegmentBinarization)
	ON_COMMAND(ID_SEGMENT_ITERATIVE, &CRecogBarcodeDoc::OnSegmentIterative)
	ON_COMMAND(ID_CONTOUR_TRACING, &CRecogBarcodeDoc::OnContourTracing)
	ON_COMMAND(ID_SEGMENT_CROP, &CRecogBarcodeDoc::OnSegmentCrop)
	ON_COMMAND(ID_PREPRO_HYUNDAIDP, &CRecogBarcodeDoc::OnPreproHyundaidp)
	ON_COMMAND(ID_PREPRO_SAVEZONE, &CRecogBarcodeDoc::OnPreproSavezone)
END_MESSAGE_MAP()


// CRecogBarcodeDoc 생성/소멸

CRecogBarcodeDoc::CRecogBarcodeDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CRecogBarcodeDoc::~CRecogBarcodeDoc()
{
}

BOOL CRecogBarcodeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	BOOL bSuccess = TRUE;
	if (theApp.m_pNewDib == NULL)
	{
		CFileNewDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_nType == 0)
				bSuccess = m_Dib.CreateGrayImage(dlg.m_nWidth, dlg.m_nHeight);
			else
				bSuccess = m_Dib.CreateRGBImage(dlg.m_nWidth, dlg.m_nHeight);
		}
		else
		{
			bSuccess = FALSE;
		}
	}
	else
	{
		m_Dib.Copy(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}

	return bSuccess;
}




// CRecogBarcodeDoc serialization

void CRecogBarcodeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CRecogBarcodeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CRecogBarcodeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRecogBarcodeDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CRecogBarcodeDoc 진단

#ifdef _DEBUG
void CRecogBarcodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRecogBarcodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRecogBarcodeDoc 명령


BOOL CRecogBarcodeDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return m_Dib.Load(lpszPathName);
}


BOOL CRecogBarcodeDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return m_Dib.Save(lpszPathName);
}


void CRecogBarcodeDoc::OnWindowDuplicate()
{
	AfxNewImage(m_Dib);
}


void CRecogBarcodeDoc::OnEditCopy()
{
	if (m_Dib.IsValid())
		m_Dib.CopyToClipboard();
}


void CRecogBarcodeDoc::OnImageInverse()
{
	CDib dib = m_Dib;
	DibInverse(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnImageBrightness()
{
	CBrightnessDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibBrightness(dib, dlg.m_nBrightness);
		AfxNewImage(dib);
	}
}


void CRecogBarcodeDoc::OnImageContrast()
{
	CContrastDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibContrast(dib, dlg.m_nContrast);
		AfxNewImage(dib);
	}
}


void CRecogBarcodeDoc::OnGammaCorrection()
{
	CGammaCorrectionDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibGammaCorrection(dib, dlg.m_fGamma);
		AfxNewImage(dib);
	}
}

void CRecogBarcodeDoc::OnViewHistogram()
{
	CHistogramDlg dlg;
	dlg.SetImage(m_Dib);
	dlg.DoModal();
}


void CRecogBarcodeDoc::OnHistoEqualize()
{
	CDib dib = m_Dib;
	DibHistEqual(dib);
	AfxNewImage(dib);
}

void CRecogBarcodeDoc::OnImageArithmetic()
{
	CArithmeticDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CRecogBarcodeDoc* pDoc1 = (CRecogBarcodeDoc*)dlg.m_pDoc1;
		CRecogBarcodeDoc* pDoc2 = (CRecogBarcodeDoc*)dlg.m_pDoc2;

		CDib dib;
		BOOL ret = FALSE;

		switch (dlg.m_nFunction)
		{
		case 0: ret = DibAdd(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 1: ret = DibSub(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 2: ret = DibAve(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 3: ret = DibDif(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 4: ret = DibAND(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		case 5: ret = DibOR(pDoc1->m_Dib, pDoc2->m_Dib, dib); break;
		}

		if (ret)
			AfxNewImage(dib);
		else
			AfxMessageBox(_T("영상의 크기가 다릅니다!"));
	}
}

void CRecogBarcodeDoc::OnBitplaneSlicing()
{
	register int i;

	int w = m_Dib.GetWidth();
	int h = m_Dib.GetHeight();

	CDib dib;
	dib.CreateGrayImage(w, h);

	for (i = 0; i < 8; i++)
	{
		DibBitPlane(m_Dib, i, dib);
		AfxNewImage(dib);
	}
}

void CRecogBarcodeDoc::OnFilterMean()
{
	CDib dib = m_Dib;
	DibFilterMean(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnFilterWeightedMean()
{
	CDib dib = m_Dib;
	DibFilterWeightedMean(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnFilterGaussian()
{
	CGaussianDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibFilterGaussian(dib, dlg.m_fSigma);
		AfxNewImage(dib);
	}
}


void CRecogBarcodeDoc::OnFilterLaplacian()
{
	CDib dib = m_Dib;
	DibFilterLaplacian(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnFilterUnsharpMask()
{
	CDib dib = m_Dib;
	DibFilterUnsharpMask(dib);
	AfxNewImage(dib);
}

void CRecogBarcodeDoc::OnImageResize()
{
	CResizeDlg dlg;
	dlg.m_nOldWidth = m_Dib.GetWidth();
	dlg.m_nOldHeight = m_Dib.GetHeight();
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		switch (dlg.m_nInterpolation)
		{
		case 0: DibResizeNearest(dib, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		case 1: DibResizeBilinear(dib, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		case 2: DibResizeCubic(dib, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		}

		AfxNewImage(dib);
	}
}


void CRecogBarcodeDoc::OnImageRotate()
{
	CRotateDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		switch (dlg.m_nRotate)
		{
		case 0:DibRotate90(dib); break;
		case 1:DibRotate180(dib); break;
		case 2:DibRotate270(dib); break;
		case 3:DibRotate(dib, dlg.m_fAngle); break;
		}

		AfxNewImage(dib);
	}
}


void CRecogBarcodeDoc::OnEdgeRoberts()
{
	CDib dib = m_Dib;
	DibEdgeRoberts(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnEdgePrewitt()
{
	CDib dib = m_Dib;
	DibEdgePrewitt(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnEdgeSobel()
{
	CDib dib = m_Dib;
	DibEdgeSobel(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnHoughLine()
{
	CDib dib = m_Dib;
	LineParam line = DibHoughLine(dib);
	DibDrawLine(dib, line, 255);

	AfxNewImage(dib);

	CString str;
	str.Format(_T("허프 변환 결과 : \n\nrho = %lf, ang = %lf"), line.rho, line.ang);
	AfxMessageBox(str);
}


void CRecogBarcodeDoc::OnHarrisCorner()
{
	CHarrisDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CornerPoints cp;
		cp = DibHarrisCorner(m_Dib, dlg.m_nThreshold);

		CDib dib = m_Dib;
		BYTE** ptr = dib.GetPtr();

		int i, x, y;
		for (i = 0; i < cp.num; i++)
		{
			x = cp.x[i];
			y = cp.y[i];

			ptr[y - 1][x - 1] = ptr[y - 1][x] = ptr[y - 1][x + 1] = 0;
			ptr[y][x - 1] = ptr[y][x] = ptr[y][x + 1] = 0;
			ptr[y + 1][x - 1] = ptr[y + 1][x] = ptr[y + 1][x + 1] = 0;
		}
		AfxNewImage(dib);
	}
}


void CRecogBarcodeDoc::OnColorGrayscale()
{
	CDib dib = m_Dib;
	DibGrayscale(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnUpdateColorGrayscale(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CRecogBarcodeDoc::OnColorSplitRgb()
{
	CDib dibR, dibG, dibB;
	DibColorSplitRGB(m_Dib, dibR, dibG, dibB);

	AfxNewImage(dibR);
	AfxNewImage(dibG);
	AfxNewImage(dibB);
}


void CRecogBarcodeDoc::OnUpdateColorSplitRgb(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CRecogBarcodeDoc::OnColorSplitHsi()
{
	CDib dibH, dibS, dibI;
	DibColorSplitHSI(m_Dib, dibH, dibS, dibI);

	AfxNewImage(dibH);
	AfxNewImage(dibS);
	AfxNewImage(dibI);
}


void CRecogBarcodeDoc::OnUpdateColorSplitHsi(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CRecogBarcodeDoc::OnColorSplitYuv()
{
	CDib dibY, dibU, dibV;
	DibColorSplitYUV(m_Dib, dibY, dibU, dibV);

	AfxNewImage(dibY);
	AfxNewImage(dibU);
	AfxNewImage(dibV);
}


void CRecogBarcodeDoc::OnUpdateColorSplitYuv(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CRecogBarcodeDoc::OnColorCombineRgb()
{
	CColorCombineDlg dlg;
	dlg.m_strColorSpace.Format(_T("RGB 색상 평면 합치기"));
	if (dlg.DoModal() == IDOK)
	{
		CRecogBarcodeDoc* pDoc1 = (CRecogBarcodeDoc*)dlg.m_pDoc1;
		CRecogBarcodeDoc* pDoc2 = (CRecogBarcodeDoc*)dlg.m_pDoc2;
		CRecogBarcodeDoc* pDoc3 = (CRecogBarcodeDoc*)dlg.m_pDoc3;

		CDib dib;
		BOOL ret;

		ret = DibColorCombineRGB(pDoc1->m_Dib, pDoc2->m_Dib, pDoc3->m_Dib, dib);

		if (ret)
			AfxNewImage(dib);
		else
			AfxMessageBox(_T("영상의 크기가 다릅니다!"));
	}
}


void CRecogBarcodeDoc::OnColorCombineHsi()
{
	CColorCombineDlg dlg;
	dlg.m_strColorSpace.Format(_T("HSI 색상 평면 합치기"));
	if (dlg.DoModal() == IDOK)
	{
		CRecogBarcodeDoc* pDoc1 = (CRecogBarcodeDoc*)dlg.m_pDoc1;
		CRecogBarcodeDoc* pDoc2 = (CRecogBarcodeDoc*)dlg.m_pDoc2;
		CRecogBarcodeDoc* pDoc3 = (CRecogBarcodeDoc*)dlg.m_pDoc3;

		CDib dib;
		BOOL ret;

		ret = DibColorCombineHSI(pDoc1->m_Dib, pDoc2->m_Dib, pDoc3->m_Dib, dib);

		if (ret)
			AfxNewImage(dib);
		else
			AfxMessageBox(_T("영상의 크기가 다릅니다!"));
	}
}


void CRecogBarcodeDoc::OnColorCombineYuv()
{
	CColorCombineDlg dlg;
	dlg.m_strColorSpace.Format(_T("YUV 색상 평면 합치기"));
	if (dlg.DoModal() == IDOK)
	{
		CRecogBarcodeDoc* pDoc1 = (CRecogBarcodeDoc*)dlg.m_pDoc1;
		CRecogBarcodeDoc* pDoc2 = (CRecogBarcodeDoc*)dlg.m_pDoc2;
		CRecogBarcodeDoc* pDoc3 = (CRecogBarcodeDoc*)dlg.m_pDoc3;

		CDib dib;
		BOOL ret;

		ret = DibColorCombineYUV(pDoc1->m_Dib, pDoc2->m_Dib, pDoc3->m_Dib, dib);

		if (ret)
			AfxNewImage(dib);
		else
			AfxMessageBox(_T("영상의 크기가 다릅니다!"));
	}
}


void CRecogBarcodeDoc::OnColorEdge()
{
	CDib dib = m_Dib;
	DibColorEdge(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnUpdateColorEdge(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CRecogBarcodeDoc::OnColorEqualize()
{
	CDib dib = m_Dib;
	DibColorHistEqual(dib);
	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnUpdateColorEqualize(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CRecogBarcodeDoc::OnSegmentBinarization()
{
	CBinarizationDlg dlg;
	dlg.SetImage(m_Dib);
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibBinarization(dib, dlg.m_nThreshold);
		AfxNewImage(dib);
	}
}


void CRecogBarcodeDoc::OnSegmentIterative()
{
	CDib dib = m_Dib;
	int th = DibBinarizationIterative(dib);
	DibBinarization(dib, th);
	AfxNewImage(dib);

	CString str;
	str.Format(_T("Threshold = %d"), th);
	AfxMessageBox(str);
}


void CRecogBarcodeDoc::OnContourTracing()
{
	ContourPoints cp = DibContourTracing(m_Dib);

	register int i;

	int w = m_Dib.GetWidth();
	int h = m_Dib.GetHeight();

	CDib dib;
	dib.CreateGrayImage(w, h, 0);
	BYTE** ptr = dib.GetPtr();

	for (i = 0; i < cp.num; i++)
		ptr[cp.y[i]][cp.x[i]] = 255;

	AfxNewImage(dib);
}


void CRecogBarcodeDoc::OnSegmentCrop()
{
	CCropDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CDib dib = m_Dib;
		DibCrop(dib, dlg.m_nStartX, dlg.m_nStartY, dlg.m_nEndX, dlg.m_nEndY);
		AfxNewImage(dib);
	}
}


void CRecogBarcodeDoc::OnPreproHyundaidp()
{
	CDib dib = m_Dib;
	register int i = 0;

	DibGrayscale(dib); //GrayScale

	{
		CDib cpy = dib;
		DibEdgePrewitt(cpy); // Prewitt

		double ang = 0.0;
		{
			LineParam line = DibHoughLine(cpy); //Hough

			if (line.ang > 90) ang = line.ang - 180.0; //angle 검출
		}
		DibRotate(dib, ang); //rotate
	}

	{
		CDib cpy = dib;

		int th = DibBinarizationIterative(cpy);
		DibBinarization(cpy, th); //Binarization

		ContourPoints cp = DibContourTracing(cpy); //ContourTracing

		long startX = cp.x[0], startY = cp.y[0], endX = 0, endY = 0;
		for (i = 0; i < cp.num; i++)
		{
			if (startX > cp.x[i]) startX = cp.x[i];
			if (startY > cp.y[i]) startY = cp.y[i];
			if (endX < cp.x[i]) endX = cp.x[i];
			if (endY < cp.y[i]) endY = cp.y[i];
		}

		DibCrop(dib, startX, startY, endX, endY); //crop
	}
	
	int w = dib.GetWidth();
	int h = dib.GetHeight();
	DibResizeBilinear(dib, w * 2, h); //resize 가로두배
	
	DibResizeBilinear(dib, 2420, 540); //resize 일정하게크롭하기위해
	
	
	CropHyundaiDP(dib); //Barcode Crop

	DibHistEqual(dib); //histEqual 이진화쉽게
	AfxNewImage(dib);

	DibBinarization(dib, 100); //Binarization Threshold 100
	DibSort(dib); //바코드 깔끔하게
	
	AfxNewImage(dib);
	
	CString numSNR = DCHyundaiDP(dib); //바코드 디코딩
	AfxMessageBox(numSNR);
}


void CRecogBarcodeDoc::OnPreproSavezone()
{
	CDib dib = m_Dib;
	register int i = 0;

	DibGrayscale(dib); //GrayScale

	{
		CDib cpy = dib;
		DibEdgePrewitt(cpy); // Prewitt

		double ang = 0.0;
		{
			LineParam line = DibHoughLine(cpy); //Hough

			if (line.ang > 90) ang = line.ang - 180.0; //angle 검출
		}
		DibRotate(dib, ang); //rotate
	}

	{
		CDib cpy = dib;

		int th = DibBinarizationIterative(cpy);
		DibBinarization(cpy, th); //Binarization

		ContourPoints cp = DibContourTracing(cpy); //ContourTracing

		long startX = cp.x[0], startY = cp.y[0], endX = 0, endY = 0;
		for (i = 0; i < cp.num; i++)
		{
			if (startX > cp.x[i]) startX = cp.x[i];
			if (startY > cp.y[i]) startY = cp.y[i];
			if (endX < cp.x[i]) endX = cp.x[i];
			if (endY < cp.y[i]) endY = cp.y[i];
		}

		DibCrop(dib, startX, startY, endX, endY); //crop
	}
	
	int w = dib.GetWidth();
	int h = dib.GetHeight();
	DibResizeBilinear(dib, w * 2, h); //resize 가로 세로 두배

	DibResizeBilinear(dib, 2320, 540); //resize 일정한 크기로
									   
	CropSavezone(dib); //Barcode Crop
	
	DibHistEqual(dib); //histEqual
	AfxNewImage(dib);
				   
	DibBinarization(dib, 100); //Binarization Threshold 100
	DibSort(dib); //바코드 깔끔하게
	
	AfxNewImage(dib);

	CString numSNR = DCSavezone(dib); //바코드 디코딩
	AfxMessageBox(numSNR);
}
