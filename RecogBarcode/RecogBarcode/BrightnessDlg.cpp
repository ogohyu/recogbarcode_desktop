// BrightnessDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "BrightnessDlg.h"
#include "afxdialogex.h"


// CBrightnessDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBrightnessDlg, CDialogEx)

CBrightnessDlg::CBrightnessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BRIGHTNESS, pParent)
	, m_nBrightness(0)
{

}

CBrightnessDlg::~CBrightnessDlg()
{
}

void CBrightnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRIGHTNESS_SLIDER, m_sliderBrightness);
	DDX_Text(pDX, IDC_BRIGHTNESS_EDIT, m_nBrightness);
	DDV_MinMaxInt(pDX, m_nBrightness, -100, 100);
}


BEGIN_MESSAGE_MAP(CBrightnessDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_BRIGHTNESS_EDIT, &CBrightnessDlg::OnEnChangeBrightnessEdit)
END_MESSAGE_MAP()


// CBrightnessDlg 메시지 처리기입니다.


BOOL CBrightnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_sliderBrightness.SetRange(-100, 100);
	m_sliderBrightness.SetTicFreq(20);
	m_sliderBrightness.SetPageSize(20);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBrightnessDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (m_sliderBrightness.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderBrightness.GetPos();
		m_nBrightness = nPos;
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBrightnessDlg::OnEnChangeBrightnessEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderBrightness.SetPos(m_nBrightness);
}
