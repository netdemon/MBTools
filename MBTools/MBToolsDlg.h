
// MBToolsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <assert.h>


// CMBToolsDlg �Ի���
class CMBToolsDlg : public CDialog
{
	// ����
public:
	CMBToolsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MBTOOLS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

	CEdit msgbox;

	int vmnum;
	CStringArray vmlist;
	CString vmNum;

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
};

CString GetClipBoardText(HWND hWnd);
void ANSItoUTF8(char* &strAnsi);
void ANSItoUnicode(CString &str);
void UnicodeToUTF8(CString &str);
void UnicodeToANSI(CString &str);
void UTF8ToUnicode(CString &str);

char * Uto8(const wchar_t* str);

