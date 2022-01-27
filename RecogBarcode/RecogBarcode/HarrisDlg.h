#pragma once


// CHarrisDlg 대화 상자입니다.

class CHarrisDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHarrisDlg)

public:
	CHarrisDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHarrisDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HARRIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nThreshold;
};
