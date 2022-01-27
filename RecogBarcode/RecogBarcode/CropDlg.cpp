// CropDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "CropDlg.h"
#include "afxdialogex.h"


// CCropDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCropDlg, CDialogEx)

CCropDlg::CCropDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CROP, pParent)
	, m_nStartX(0)
	, m_nStartY(0)
	, m_nEndX(0)
	, m_nEndY(0)
{

}

CCropDlg::~CCropDlg()
{
}

void CCropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_START_X, m_nStartX);
	DDX_Text(pDX, IDC_START_Y, m_nStartY);
	DDX_Text(pDX, IDC_END_X, m_nEndX);
	DDX_Text(pDX, IDC_END_Y, m_nEndY);
}


BEGIN_MESSAGE_MAP(CCropDlg, CDialogEx)
END_MESSAGE_MAP()


// CCropDlg �޽��� ó�����Դϴ�.
