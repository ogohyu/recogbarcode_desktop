// BrightnessDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "BrightnessDlg.h"
#include "afxdialogex.h"


// CBrightnessDlg ��ȭ �����Դϴ�.

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


// CBrightnessDlg �޽��� ó�����Դϴ�.


BOOL CBrightnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_sliderBrightness.SetRange(-100, 100);
	m_sliderBrightness.SetTicFreq(20);
	m_sliderBrightness.SetPageSize(20);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_sliderBrightness.SetPos(m_nBrightness);
}
