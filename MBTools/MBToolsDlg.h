
// MBToolsDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <assert.h>
#include <string>
using namespace std;


// CMBToolsDlg 对话框
class CMBToolsDlg : public CDialog
{
	// 构造
public:
	CMBToolsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MBTOOLS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton8();

	afx_msg int getVMlist();
	afx_msg CString getKey();

	afx_msg void AutoPost();
	afx_msg string GetTitle(CString strFilePath);

	CEdit msgbox;

	int vmnum;
	CStringArray vmlist;
	CString vmNum;
	CString Key;


	//CString Data;
	//CString Msg;

	int row;
	int edited;
	char sztempdirectory[MAX_PATH];
	CStringArray data;

	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton12();
	CComboBox m_postunit;
	afx_msg void OnCbnSelchangeCombo2();
	void disableall();
	void enableall();
	void adb_acction(CString acction, int sleeptime);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
};

CString GetClipBoardText(HWND hWnd);
void ANSItoUTF8(char* &strAnsi);
void ANSItoUnicode(CString &str);
void UnicodeToUTF8(CString &str);
void UnicodeToANSI(CString &str);
void UTF8ToUnicode(CString &str);

char * Uto8(const wchar_t* str);

