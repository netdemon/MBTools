
// MBToolsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	afx_msg int getVMlist();

	CEdit msgbox;

	int vmnum;
	CStringArray vmlist;
	CString vmNum;

	//CString Data;
	//CString Msg;

	int row;
	char sztempdirectory[MAX_PATH];
	CStringArray data;


	afx_msg void OnBnClickedButton10();
};
