// ArithmeticDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "ArithmeticDlg.h"
#include "afxdialogex.h"
#include "RecogBarcodeDoc.h"


// CArithmeticDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CArithmeticDlg, CDialogEx)

CArithmeticDlg::CArithmeticDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_nFunction(0)
	, m_pDoc1(NULL)
	, m_pDoc2(NULL)
{

}

CArithmeticDlg::~CArithmeticDlg()
{
}

void CArithmeticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IMAGE1, m_comboImage1);
	DDX_Control(pDX, IDC_COMBO_IMAGE2, m_comboImage2);
	DDX_Radio(pDX, IDC_FUNCTION1, m_nFunction);
}


BEGIN_MESSAGE_MAP(CArithmeticDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CArithmeticDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CArithmeticDlg �޽��� ó�����Դϴ�.

BOOL CArithmeticDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �޺� �ڽ��� ���ϵ������� â�� �̸��� ����
	int nIndex = 0;
	CString strTitle;
	CRecogBarcodeApp* pApp = (CRecogBarcodeApp*)AfxGetApp();
	CRecogBarcodeDoc* pDoc = NULL;
	POSITION pos = pApp->m_pImageDocTemplate->GetFirstDocPosition();

	while (pos != NULL)
	{
		pDoc = (CRecogBarcodeDoc*)pApp->m_pImageDocTemplate->GetNextDoc(pos);
		strTitle = pDoc->GetTitle();

		m_comboImage1.InsertString(nIndex, strTitle);
		m_comboImage2.InsertString(nIndex, strTitle);

		m_comboImage1.SetItemDataPtr(nIndex, (void*)pDoc);
		m_comboImage2.SetItemDataPtr(nIndex, (void*)pDoc);

		nIndex++;
	}

	m_comboImage1.SetCurSel(0);
	m_comboImage2.SetCurSel(0);
	if (nIndex > 1) m_comboImage2.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CArithmeticDlg::OnBnClickedOk()
{
	m_pDoc1 = (CRecogBarcodeDoc*)m_comboImage1.GetItemDataPtr(m_comboImage1.GetCurSel());
	m_pDoc2 = (CRecogBarcodeDoc*)m_comboImage2.GetItemDataPtr(m_comboImage2.GetCurSel());

	OnOK();
}
