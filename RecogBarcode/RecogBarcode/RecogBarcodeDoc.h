
// RecogBarcodeDoc.h: CRecogBarcodeDoc 클래스의 인터페이스
//


#pragma once
#include "Dib.h"


class CRecogBarcodeDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CRecogBarcodeDoc();
	DECLARE_DYNCREATE(CRecogBarcodeDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CRecogBarcodeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// 이미지 객체
	CDib m_Dib;
	// 파일 불러오기 & 저장하기
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnWindowDuplicate();
	afx_msg void OnEditCopy();
	afx_msg void OnImageInverse();
	afx_msg void OnImageBrightness();
	afx_msg void OnImageContrast();
	afx_msg void OnGammaCorrection();
	afx_msg void OnViewHistogram();
	afx_msg void OnHistoEqualize();
	afx_msg void OnImageArithmetic();
	afx_msg void OnBitplaneSlicing();
	afx_msg void OnFilterLaplacian();
	afx_msg void OnFilterUnsharpMask();
	afx_msg void OnFilterMean();
	afx_msg void OnFilterWeightedMean();
	afx_msg void OnFilterGaussian();
	afx_msg void OnImageResize();
	afx_msg void OnImageRotate();
	afx_msg void OnEdgeRoberts();
	afx_msg void OnEdgePrewitt();
	afx_msg void OnEdgeSobel();
	afx_msg void OnHoughLine();
	afx_msg void OnHarrisCorner();
	afx_msg void OnColorGrayscale();
	afx_msg void OnUpdateColorGrayscale(CCmdUI *pCmdUI);
	afx_msg void OnColorSplitRgb();
	afx_msg void OnUpdateColorSplitRgb(CCmdUI *pCmdUI);
	afx_msg void OnColorSplitHsi();
	afx_msg void OnUpdateColorSplitHsi(CCmdUI *pCmdUI);
	afx_msg void OnColorSplitYuv();
	afx_msg void OnUpdateColorSplitYuv(CCmdUI *pCmdUI);
	afx_msg void OnColorCombineRgb();
	afx_msg void OnColorCombineHsi();
	afx_msg void OnColorCombineYuv();
	afx_msg void OnColorEdge();
	afx_msg void OnUpdateColorEdge(CCmdUI *pCmdUI);
	afx_msg void OnColorEqualize();
	afx_msg void OnUpdateColorEqualize(CCmdUI *pCmdUI);
	afx_msg void OnSegmentBinarization();
	afx_msg void OnSegmentIterative();
	afx_msg void OnContourTracing();
	afx_msg void OnSegmentCrop();
	afx_msg void OnPreproHyundaidp();
	afx_msg void OnPreproSavezone();
};
