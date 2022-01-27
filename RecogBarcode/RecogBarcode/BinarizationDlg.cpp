// BinarizationDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "BinarizationDlg.h"
#include "afxdialogex.h"

#include "DibGeometry.h"
#include "DibSegment.h"


// CBinarizationDlg ��ȭ �����Դϴ�.

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
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CPaintDC dc2(GetDlgItem(IDC_IMAGE_WND));
	m_DibRes.Draw(dc2.m_hDC);
}


BOOL CBinarizationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �����̴� ��Ʈ���� �ʱ�ȭ�Ѵ�.
	m_sliderThreshold.SetRange(0, 255);
	m_sliderThreshold.SetTicFreq(32);
	m_sliderThreshold.SetPageSize(32);
	m_sliderThreshold.SetPos(m_nThreshold);

	// ���� ��Ʈ���� ũ�⸦ ���Ѵ�. 
	CWnd* pImageWnd = GetDlgItem(IDC_IMAGE_WND);

	CRect rect;
	pImageWnd->GetClientRect(rect);

	// ���� ��Ʈ���� ũ�⿡ �°� �Է� ������ ���纻�� ũ�⸦ �����Ѵ�.
	DibResizeNearest(m_DibSrc, rect.Width(), rect.Height());

	// ����ȭ�� ����� ������ ������ �����Ѵ�.
	m_DibRes = m_DibSrc;
	DibBinarization(m_DibRes, m_nThreshold);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CBinarizationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// �����̵���̼� �߻��� WM_HSCROLL �޽����� ��� ó��
	if (m_sliderThreshold.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderThreshold.GetPos();
		m_nThreshold = nPos;
		UpdateData(FALSE);

		// ���� ������ �Ӱ谪�� �̿��Ͽ� �̸����� ������ ����ȭ�� �����Ѵ�.
		m_DibRes = m_DibSrc;
		DibBinarization(m_DibRes, m_nThreshold);
		Invalidate(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBinarizationDlg::OnEnChangeThresholdEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� �������ϰ�  ����ũ�� OR �����Ͽ� ������
	// ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ���ؾ߸�
	// �ش� �˸� �޽����� �����ϴ�.

	// ����Ʈ ��Ʈ�ѿ��� ���ڰ� �ٲ� ���, �����̴� ��Ʈ���� ��ġ�� �����Ѵ�.
	UpdateData(TRUE);
	m_sliderThreshold.SetPos(m_nThreshold);

	// ���� ������ �Ӱ谪�� �̿��Ͽ� �̸����� ������ ����ȭ�� �����Ѵ�.
	m_DibRes = m_DibSrc;
	DibBinarization(m_DibRes, m_nThreshold);
	Invalidate(FALSE);
}
