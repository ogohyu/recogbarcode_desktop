#pragma once
#include "afxcmn.h"


// CBrightnessDlg ��ȭ �����Դϴ�.

class CBrightnessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBrightnessDlg)

public:
	CBrightnessDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBrightnessDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BRIGHTNESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderBrightness;
	// ��� ��ȭ��
	int m_nBrightness;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeBrightnessEdit();
};
