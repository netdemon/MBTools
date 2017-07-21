// setup.cpp : 实现文件
//

#include "stdafx.h"
#include "MBTools.h"
#include "setup.h"
#include "afxdialogex.h"


// setup 对话框

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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

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

// 注意: 我们添加 IID_Isetup 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {67235B79-BFA0-4D7B-82D5-B51F0E9499E3}
static const IID IID_Isetup =
{ 0x67235B79, 0xBFA0, 0x4D7B, { 0x82, 0xD5, 0xB5, 0x1F, 0xE, 0x94, 0x99, 0xE3 } };

BEGIN_INTERFACE_MAP(CMBToolsSet, CDialogEx)
	INTERFACE_PART(CMBToolsSet, IID_Isetup, Dispatch)
END_INTERFACE_MAP()


// setup 消息处理程序


void CMBToolsSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	CStdioFile file;
	GetDlgItemText(IDC_EDIT1,str);
	//写KEY文件
	file.Open(KEYFILE, CFile::modeCreate | CFile::modeReadWrite);
	file.WriteString(str);
	file.Close();
	CDialogEx::OnOK();
}


void CMBToolsSet::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
