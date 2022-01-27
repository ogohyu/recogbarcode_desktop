// HistogramDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "HistogramDlg.h"
#include "afxdialogex.h"

#include "Dib.h"
#include "DibEnhancement.h"


// CHistogramDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialogEx)

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTOGRAM, pParent)
{
	memset(m_Histogram, 0, sizeof(int) * 256);
}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHistogramDlg 메시지 처리기입니다.

void CHistogramDlg::SetImage(CDib& dib)
{
	float histo[256] = { 0.f, };
	DibHistogram(dib, histo);

	register int i;
	float max_value = histo[0];
	for (i = 1; i < 256; i++)
	{
		if (histo[i] > max_value) max_value = histo[i];
	}

	for (i = 0; i < 256; i++)
	{
		m_Histogram[i] = (int)(histo[i] * 100 / max_value);
	}
}


void CHistogramDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	register int i;

	dc.MoveTo(20, 30);
	dc.LineTo(20, 130);
	dc.LineTo(275, 130);
	dc.LineTo(275, 30);

	for (i = 0; i < 256; i++)
	{
		dc.MoveTo(20 + i, 130);
		dc.LineTo(20 + i, 130 - m_Histogram[i]);
	}

	for (i = 0; i < 256; i++)
	{
		dc.SelectStockObject(DC_PEN);
		dc.SetDCPenColor(RGB(i, i, i));

		dc.MoveTo(20 + i, 140);
		dc.LineTo(20 + i, 155);
	}
}
