#pragma once


// setup �Ի���

class CMBToolsSet : public CDialogEx
{
	DECLARE_DYNAMIC(CMBToolsSet)

public:
	CMBToolsSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMBToolsSet();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedOk();
//	afx_msg void OnEnChangeEdit1();
};
