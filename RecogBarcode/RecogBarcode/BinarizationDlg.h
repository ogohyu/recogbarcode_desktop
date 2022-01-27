#pragma once
#include "afxcmn.h"
#include "Dib.h"


// CBinarizationDlg ��ȭ �����Դϴ�.

class CBinarizationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBinarizationDlg)

public:
	CBinarizationDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBinarizationDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINARIZATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderThreshold;
	int m_nThreshold;

	CDib m_DibSrc;
	CDib m_DibRes;

public:
	void SetImage(CDib& dib);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeThresholdEdit();
};
