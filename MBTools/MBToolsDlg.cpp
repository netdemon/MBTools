
// MBToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MBTools.h"
#include "MBToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMBToolsDlg 对话框



CMBToolsDlg::CMBToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MBTOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMBToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, msgbox);
}

BEGIN_MESSAGE_MAP(CMBToolsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMBToolsDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMBToolsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMBToolsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CMBToolsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMBToolsDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON10, &CMBToolsDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON8, &CMBToolsDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMBToolsDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CMBToolsDlg 消息处理程序

BOOL CMBToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	SetDlgItemText(IDC_BUTTON1, _T("打开导号文件"));
	SetDlgItemText(IDC_BUTTON2, _T("自动发朋友圈"));
	SetDlgItemText(IDC_BUTTON4, _T("自动添加好友"));
	SetDlgItemText(IDC_BUTTON8, _T("清除所有图片"));
	SetDlgItemText(IDC_BUTTON9, _T("TEST"));

	vmnum = getVMlist();
	vmNum.Format(_T("%d"), vmnum);
	vmNum = "当前模拟器数量：" + vmNum;
	SetDlgItemText(IDC_STATIC, vmNum);


	// END在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMBToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMBToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMBToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMBToolsDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMBToolsDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (edited == 1) { GetDlgItem(IDOK)->EnableWindow(TRUE); };

}



void CMBToolsDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	theApp.GetMainWnd()->ShowWindow(SW_MINIMIZE);//最小化窗口
												 //CDialog::OnOK();
}

void CMBToolsDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}



void CMBToolsDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Msg;
	CString m_path;
	CString btText;
	CString tmp_path = "C:\\tmp";

	CString head = "BEGIN:VCARD\r\nVERSION:3.0\r\nTEL;TYPE=cell:";
	CString food = "END:VCARD\r\n";

	CStdioFile file_r;
	CStdioFile file_w;


	GetDlgItem(IDC_BUTTON1)->GetWindowText(btText);

	if (btText == "打开导号文件") {

		CFileDialog dlg(TRUE,//TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框 
			".txt",//默认的打开文件的类型 
			NULL,//默认打开的文件名 
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//打开只读文件 
			"文本文件(*.txt)|*.txt|所有文件 (*.*)|*.*||");//所有可以打开的文件类型 

		if (dlg.DoModal() == IDOK)
		{
			m_path = dlg.GetPathName(); //取出文件路径 
			UpdateData(FALSE);
			//打开文件
			file_r.Open(m_path, CFile::modeRead);
			//逐行读取文件
			//CStdioFile File  = file ;///可以逐行读文件的类 
			CString   strLine;
			row = 1;

			int nogood = 0;
			int nogoodrow = 1;

			while (file_r.ReadString(strLine))   // //将每行都放进strLine字符串里
			{
				//分析文件是否正确
				//判断读出来的字
				//去除空白
				strLine.Trim();
				//去除；号
				strLine.TrimRight(';');
				if (strLine.GetLength() != 11) {
					nogood = 1;
					nogoodrow = row;
					Msg.Format("文件第 %d 行有错，请改正！", row);
					AfxMessageBox(Msg);
					break;
				}
				data.Add(strLine);
				row++;
			}
			file_r.Close();
			if (!nogood) {
				msgbox.SetWindowText("");
				SetDlgItemText(IDC_BUTTON1, "开始导号");
			}
		}

		//CFileFind fFind;
		//CString adb = "D:\\Program Files\\Microvirt\\MEmu\\adb.exe";
		//if(fFind.FindFile(adb)){AfxMessageBox("存在"); }else{AfxMessageBox("不存在");}

	}
	else {
		// 导号操作
		//AfxMessageBox("导号操作开始");
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		SetDlgItemText(IDC_BUTTON1, "导号中...");

		if (vmnum == 0) {
			AfxMessageBox("严重错误");
			exit(1);
		}

		CString adb = "D:\\Program Files\\Microvirt\\MEmu\\adb.exe";
		CString a = " -s ";
		CString acction = " shell pm clear com.android.providers.contacts";
		CString cmd;

		int a_num = row / vmnum;
		int y = 0;
		int z = 0;

		CString str;
		CString file;
		//生成文件
		msgbox.ReplaceSel("生成文件:");
		for (int i = 0; i < vmnum; i++) {
			str.Format("%d", i);
			file = "D:\\dhfile" + str + ".vcf";
			file_w.Open(file, CFile::modeCreate | CFile::modeReadWrite);
			while (z < a_num) {
				CString out = head;
				out = out + data[y];
				out = out + "\r\n";
				out = out + food;
				file_w.WriteString(out);
				y++;
				z++;
			}
			z = 0;
			file_w.Close();
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
		}

		//删除号码
		msgbox.ReplaceSel("\r\n删除号码:");
		for (int i = 0; i < vmnum; i++) {
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);  //DEL
			ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
			Sleep(100);
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);

		}

		//复制号码
		msgbox.ReplaceSel("\r\n复制号码:");
		for (int i = 0; i < vmnum; i++) {
			str.Format("%d", i);
			file = "D:\\dhfile" + str + ".vcf";
			acction = " push ";
			acction += file;
			acction += " /sdcard/contacts.vcf";
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);  //COPY
			ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
			Sleep(100);
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
		}

		//导入号码
		msgbox.ReplaceSel("\r\n导入号码:");
		for (int i = 0; i < vmnum; i++) {
			acction = " shell am start -t \"text/x-vcard\" -d \"file:///sdcard/contacts.vcf\" -a android.intent.action.VIEW com.android.contacts";
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
			Sleep(100);
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
		}

		//导号结束
		msgbox.ReplaceSel("\r\n导号成功!");
		SetDlgItemText(IDC_BUTTON1, "打开导号文件");
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}

}


void CMBToolsDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox("确保所有模拟器图库为空\r\n使用任一模拟器手工保存最多9张图片并复制文字后按确定\r\n不然可能出错,没准备好请按取消并重新准备好", "准备好了吗？", MB_OKCANCEL) == IDOK) {
		//AfxMessageBox("OK");
		//保存已存微信图片到本地  adb pull /sdcard/tencent/MicroMsg/WeiXin D:\\pic
		SetDlgItemText(IDC_BUTTON2, "等待编辑文字");
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		edited = 0;

		if (vmnum == 0) {
			AfxMessageBox("严重错误");
			exit(1);
		}

		CString ClipBoardText;
		HWND hWnd = GetSafeHwnd();
		ClipBoardText = GetClipBoardText(hWnd);

		CString adb = "D:\\Program Files\\Microvirt\\MEmu\\adb.exe";
		CString a = " -s ";
		CString acction = " pull /sdcard/tencent/MicroMsg/WeiXin D:\\pic";
		CString cmd;
		CString Msg;

		msgbox.SetWindowText("");
		msgbox.ReplaceSel("正在下图:");
		for (int i = 0; i < vmnum; i++) {
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
			Sleep(100);
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
		}
		//msgbox.ReplaceSel("\r\n保存完成!");

		acction = " push D:\\pic /sdcard/tencent/MicroMsg/WeiXin";
		msgbox.ReplaceSel("\r\n正在上图:");
		for (int i = 0; i < vmnum; i++) {
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
			Sleep(100);
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
		}

		acction = " shell am broadcast -a android.intent.action.MEDIA_MOUNTED -d file:///sdcard/";
		for (int i = 0; i < vmnum; i++) {
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
			Sleep(100);
		}

		msgbox.SetWindowText(ClipBoardText);
		edited = 1;

		//
	}
	else {
		//AfxMessageBox("Cancel");
	}
}




void CMBToolsDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	vmnum = getVMlist();
	vmNum.Format(_T("%d"), vmnum);
	vmNum = "当前模拟器数量：" + vmNum;
	SetDlgItemText(IDC_STATIC, vmNum);
}


void CMBToolsDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);


	if (vmnum == 0) {
		AfxMessageBox("严重错误");
		exit(1);
	}

	CString adb = "D:\\Program Files\\Microvirt\\MEmu\\adb.exe";
	CString a = " -s ";
	CString acction = " shell pm clear com.android.providers.media";
	CString acction1 = " shell rm \"/sdcard/tencent/MicroMsg/WeiXin/*\"";
	CString cmd;
	CString cmd1;
	CString Msg;

	msgbox.SetWindowText("");
	msgbox.ReplaceSel("正在清理:");
	for (int i = 0; i < vmnum; i++) {
		cmd = a + vmlist[i] + acction;
		cmd1 = a + vmlist[i] + acction1;
		//AfxMessageBox(cmd1);
		ShellExecute(NULL, "open", adb, cmd1, "", SW_HIDE);
		Sleep(100);
		ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
		Sleep(100);
		Msg.Format(" %d", i + 1);
		msgbox.ReplaceSel(Msg);
	}
	msgbox.ReplaceSel("\r\n清理成功!");
	GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE);
}


int CMBToolsDlg::getVMlist() {

	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return FALSE;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;            //把创建进程的标准错误输出重定向到管道输入  
	si.hStdOutput = hWrite;           //把创建进程的标准输出重定向到管道输入  
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//关键步骤，CreateProcess函数参数意义请查阅MSDN  
	if (!CreateProcess(NULL, "D:\\Program Files\\Microvirt\\MEmu\\adb.exe devices", NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return FALSE;
	}
	CloseHandle(hWrite);
	char buffer[65536] = { 0 };       //用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。  
	DWORD bytesRead;
	CString bf;
	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
		{
			break;
		}
		//buffer中就是执行的结果，可以保存到文本，也可以直接输出  
		bf += buffer;
	}
	CloseHandle(hRead);

	CStdioFile file_r, file_w;
	file_w.Open(_T("D:\\vmlist"), CFile::modeCreate | CFile::modeReadWrite);//如果文件事先不存在的话，就需要CFile::modeCreate，否则就不需要。
	file_w.WriteString(bf);
	file_w.Close();
	Sleep(200);

#ifdef DEBUG
	file_r.Open(_T("D:\\1.txt"), CFile::modeRead);
#else
	file_r.Open(_T("D:\\vmlist"), CFile::modeRead);
#endif

	CString   strLine;
	vmnum = 0;
	vmlist.SetSize(0, 1);
	while (file_r.ReadString(strLine))
	{
		CString bf = strLine.Left(15);
		if (bf.Find(_T("127.0.0.1")) != -1)
		{
			vmlist.Add(bf);
		}
	}
	file_r.Close();
	vmnum = vmlist.GetSize();
	return vmnum;
}



//获取剪贴板文本内容  
CString GetClipBoardText(HWND hWnd)
{
	ASSERT(hWnd);
	CString ClipBoardText;
	//判断剪贴板的数据格式是否可以处理。    
	if (!IsClipboardFormatAvailable(CF_TEXT))
		return ClipBoardText;

	//打开剪贴板。            
	if (!::OpenClipboard(hWnd))
		return ClipBoardText;

	//获取数据    
	HANDLE hMem = GetClipboardData(CF_TEXT);
	if (hMem != NULL)
	{
		//获取字符串。    
		LPSTR lpStr = (LPSTR)GlobalLock(hMem);
		if (lpStr != NULL)
		{
			ClipBoardText = lpStr;
			//释放锁内存    
			GlobalUnlock(hMem);
		}
	}
	//关闭剪贴板          
	CloseClipboard();
	return ClipBoardText;
}


void CMBToolsDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ClipBoardText;
	HWND hWnd = GetSafeHwnd();
	ClipBoardText = GetClipBoardText(hWnd);
	AfxMessageBox(ClipBoardText);

}
