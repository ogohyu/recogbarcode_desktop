// HarrisDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "HarrisDlg.h"
#include "afxdialogex.h"


// CHarrisDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CHarrisDlg, CDialogEx)

CHarrisDlg::CHarrisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HARRIS, pParent)
	, m_nThreshold(20000)
{

}

CHarrisDlg::~CHarrisDlg()
{
}

void CHarrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_THRESHOLD, m_nThreshold);
}


BEGIN_MESSAGE_MAP(CHarrisDlg, CDialogEx)
END_MESSAGE_MAP()


// CHarrisDlg �޽��� ó�����Դϴ�.
