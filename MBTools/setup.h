#pragma once


// setup 对话框

class CMBToolsSet : public CDialogEx
{
	DECLARE_DYNAMIC(CMBToolsSet)

public:
	CMBToolsSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMBToolsSet();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedOk();
//	afx_msg void OnEnChangeEdit1();
};
