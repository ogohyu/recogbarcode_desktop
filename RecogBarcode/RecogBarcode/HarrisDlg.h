#pragma once


// CHarrisDlg ��ȭ �����Դϴ�.

class CHarrisDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHarrisDlg)

public:
	CHarrisDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CHarrisDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HARRIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_nThreshold;
};
