// RotateDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "RotateDlg.h"
#include "afxdialogex.h"


// CRotateDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRotateDlg, CDialogEx)

CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ROTATE, pParent)
	, m_nRotate(0)
	, m_fAngle(0)
{

}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_ROTATE1, m_nRotate);
	DDX_Text(pDX, IDC_ANGLE, m_fAngle);
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialogEx)
END_MESSAGE_MAP()


// CRotateDlg �޽��� ó�����Դϴ�.
