// HarrisDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RecogBarcode.h"
#include "HarrisDlg.h"
#include "afxdialogex.h"


// CHarrisDlg 대화 상자입니다.

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


// CHarrisDlg 메시지 처리기입니다.
