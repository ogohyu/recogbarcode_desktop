// BinarizationDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "BinarizationDlg.h"
#include "afxdialogex.h"

#include "DibGeometry.h"
#include "DibSegment.h"


// CBinarizationDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBinarizationDlg, CDialogEx)

CBinarizationDlg::CBinarizationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BINARIZATION, pParent)
	, m_nThreshold(128)
{

}

CBinarizationDlg::~CBinarizationDlg()
{
}

void CBinarizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_THRESHOLD_SLIDER, m_sliderThreshold);
	DDX_Text(pDX, IDC_THRESHOLD_EDIT, m_nThreshold);
}


BEGIN_MESSAGE_MAP(CBinarizationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_THRESHOLD_EDIT, &CBinarizationDlg::OnEnChangeThresholdEdit)
END_MESSAGE_MAP()


void CBinarizationDlg::SetImage(CDib& dib)
{
	m_DibSrc = dib;
}


void CBinarizationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CPaintDC dc2(GetDlgItem(IDC_IMAGE_WND));
	m_DibRes.Draw(dc2.m_hDC);
}


BOOL CBinarizationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 슬라이더 컨트롤을 초기화한다.
	m_sliderThreshold.SetRange(0, 255);
	m_sliderThreshold.SetTicFreq(32);
	m_sliderThreshold.SetPageSize(32);
	m_sliderThreshold.SetPos(m_nThreshold);

	// 픽쳐 컨트롤의 크기를 구한다. 
	CWnd* pImageWnd = GetDlgItem(IDC_IMAGE_WND);

	CRect rect;
	pImageWnd->GetClientRect(rect);

	// 픽쳐 컨트롤의 크기에 맞게 입력 영상의 복사본의 크기를 조절한다.
	DibResizeNearest(m_DibSrc, rect.Width(), rect.Height());

	// 이진화된 결과를 보여줄 영상을 생성한다.
	m_DibRes = m_DibSrc;
	DibBinarization(m_DibRes, m_nThreshold);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBinarizationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// 슬라이드바이서 발생한 WM_HSCROLL 메시지인 경우 처리
	if (m_sliderThreshold.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderThreshold.GetPos();
		m_nThreshold = nPos;
		UpdateData(FALSE);

		// 현재 설정된 임계값을 이용하여 미리보기 영상의 이진화를 수행한다.
		m_DibRes = m_DibSrc;
		DibBinarization(m_DibRes, m_nThreshold);
		Invalidate(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBinarizationDlg::OnEnChangeThresholdEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정하고  마스크에 OR 연산하여 설정된
	// ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출해야만
	// 해당 알림 메시지를 보냅니다.

	// 에디트 컨트롤에서 글자가 바뀐 경우, 슬라이더 컨트롤의 위치를 조절한다.
	UpdateData(TRUE);
	m_sliderThreshold.SetPos(m_nThreshold);

	// 현재 설정된 임계값을 이용하여 미리보기 영상의 이진화를 수행한다.
	m_DibRes = m_DibSrc;
	DibBinarization(m_DibRes, m_nThreshold);
	Invalidate(FALSE);
}
