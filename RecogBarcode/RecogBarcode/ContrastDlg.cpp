// ContrastDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "ContrastDlg.h"
#include "afxdialogex.h"


// CContrastDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CContrastDlg, CDialogEx)

CContrastDlg::CContrastDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONTRAST, pParent)
	, m_nContrast(0)
{

}

CContrastDlg::~CContrastDlg()
{
}

void CContrastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTRAST_SLIDER, m_sliderContrast);
	DDX_Text(pDX, IDC_CONTRAST_EDIT, m_nContrast);
	DDV_MinMaxInt(pDX, m_nContrast, -100, 100);
}


BEGIN_MESSAGE_MAP(CContrastDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_CONTRAST_EDIT, &CContrastDlg::OnEnChangeContrastEdit)
END_MESSAGE_MAP()


// CContrastDlg �޽��� ó�����Դϴ�.


BOOL CContrastDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_sliderContrast.SetRange(-100, 100);
	m_sliderContrast.SetTicFreq(20);
	m_sliderContrast.SetPageSize(20);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CContrastDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (m_sliderContrast.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderContrast.GetPos();
		m_nContrast = nPos;
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CContrastDlg::OnEnChangeContrastEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_sliderContrast.SetPos(m_nContrast);
}
