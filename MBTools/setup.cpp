// setup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MBTools.h"
#include "setup.h"
#include "afxdialogex.h"


// setup �Ի���

IMPLEMENT_DYNAMIC(CMBToolsSet, CDialogEx)

CMBToolsSet::CMBToolsSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SETUP, pParent)
{

	EnableAutomation();

}

CMBToolsSet::~CMBToolsSet()
{
}

void CMBToolsSet::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CMBToolsSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMBToolsSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMBToolsSet::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CMBToolsSet::OnEnChangeEdit1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMBToolsSet, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_Isetup ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {67235B79-BFA0-4D7B-82D5-B51F0E9499E3}
static const IID IID_Isetup =
{ 0x67235B79, 0xBFA0, 0x4D7B, { 0x82, 0xD5, 0xB5, 0x1F, 0xE, 0x94, 0x99, 0xE3 } };

BEGIN_INTERFACE_MAP(CMBToolsSet, CDialogEx)
	INTERFACE_PART(CMBToolsSet, IID_Isetup, Dispatch)
END_INTERFACE_MAP()


// setup ��Ϣ�������


void CMBToolsSet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	CStdioFile file;
	GetDlgItemText(IDC_EDIT1,str);
	//дKEY�ļ�
	file.Open(KEYFILE, CFile::modeCreate | CFile::modeReadWrite);
	file.WriteString(str);
	file.Close();
	CDialogEx::OnOK();
}


void CMBToolsSet::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
