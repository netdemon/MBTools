
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
	DDX_Control(pDX, IDC_COMBO1, m_vmnum);
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
	SetDlgItemText(IDC_BUTTON2, _T("清除所有图片"));
	m_vmnum.SetCurSel(0);
	/*
		int i = GetTempPath(MAX_PATH - 1, sztempdirectory);
		if (sztempdirectory[i - 1] != '\\')
		{
			lstrcat(sztempdirectory, "\\");
		}
		lstrcat(sztempdirectory, "dh\\");
	*/
	/*
//#define EXECDOSCMD "dir /?" //可以换成你的命令  
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return FALSE;
	}
	char command[1024];    //长达1K的命令行，够用了吧  
	//strcpy_s(command, "Cmd.exe /C ");
	//strcat_s(command, EXECDOSCMD);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;            //把创建进程的标准错误输出重定向到管道输入  
	si.hStdOutput = hWrite;           //把创建进程的标准输出重定向到管道输入  
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//关键步骤，CreateProcess函数参数意义请查阅MSDN  
	if (!CreateProcess(NULL, _T("D:\\Program Files\\Microvirt\\MEmu\\adb.exe devices"), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return FALSE;
	}
	CloseHandle(hWrite);
	wchar_t buffer[4096] = { 0 };          //用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。  
	DWORD bytesRead;
	CString bf;
	CStringArray mv;
	mv.SetSize(0, 1);
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

	//AfxMessageBox(bf);   //这里是弹出对话框显示  
	//msgbox.ReplaceSel(bf);
	//UpdateData(false);
	//Sleep(200);
	*/
	/////////////////////////////////////////////////////////////////////////////////////

	CStdioFile file_r, file_w;
	//file_w.Open(_T("D:\\vmlist"), CFile::modeCreate | CFile::modeReadWrite);//如果文件事先不存在的话，就需要CFile::modeCreate，否则就不需要。
	//file_w.WriteString(bf);
	//file_w.Close();
	Sleep(200);
	
	file_r.Open(_T("D:\\1.txt"),CFile::modeRead);
	//file_r.Open(_T("D:\\vmlist"), CFile::modeRead);
	//逐行读取文件
	CString   strLine;
	vmnum = 0;
	while (file_r.ReadString(strLine))   // //将每行都放进strLine字符串里
	{
		CString bf = strLine.Left(15);
		if (bf.Find(_T("127.0.0.1")) != -1)
		{
			vmlist.Add(bf);
		}
		//AfxMessageBox(bf);  //执行命令
		//Sleep(100);
	}
	file_r.Close();

	CString vmNum;
	vmnum = vmlist.GetSize();

	vmNum.Format(_T("%d"), vmnum);
	SetDlgItemText(IDC_COMBO1, vmNum);
	
/////////////////////////////////////////////////////////////////////////////////////////





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
}


void CMBToolsDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Msg;
	CString m_path;
	CString btText;
	CString tmp_path = _T("C:\\tmp");

	CString head = _T("BEGIN:VCARD\r\nVERSION:3.0\r\nTEL;TYPE=cell:");
	CString food = _T("END:VCARD\r\n");

	CStdioFile file_r;
	CStdioFile file_w;


	GetDlgItem(IDC_BUTTON1)->GetWindowText(btText);

	if (btText == "打开导号文件") {

		CFileDialog dlg(TRUE,		//TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框 
			_T(".txt"),				//默认的打开文件的类型 
			NULL,					//默认打开的文件名 
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	//打开只读文件 
			_T("文本文件(*.txt)|*.txt|所有文件 (*.*)|*.*||"));	//所有可以打开的文件类型 

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
					Msg.Format(_T("文件第 %d 行有错，请改正！"), row);
					AfxMessageBox(Msg);
					break;
				}
				//Data = Data + head;
				//Data = Data + strLine;
				//Data = Data + "\r\n";
				//Data = Data + food;

				data.Add(strLine);

				//CString out = data.GetAt(row-1);
				//AfxMessageBox(out);

				row++;
			}
			file_r.Close();
			if (!nogood) {
				//Msg.Format("%d",row);
				msgbox.SetWindowText(_T(""));
				SetDlgItemText(IDC_BUTTON1, _T("开始导号"));
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
		SetDlgItemText(IDC_BUTTON1, _T("导号中..."));

		if (vmnum == 0) {
			AfxMessageBox(_T("严重错误"));
			exit(1);
		}

		CString adb = _T("D:\\Program Files\\Microvirt\\MEmu\\adb.exe");
		CString a = _T(" -s ");
		CString acction = _T(" shell pm clear com.android.providers.contacts");
		CString cmd;


		int a_num = row / vmnum;
		int y = 0;
		int z = 0;
		// 生成文件  MessageBox(NULL,data[3],MB_OK);
		CString str;
		CString file;

		msgbox.ReplaceSel(_T("生成文件:"));
		for (int i = 0; i < vmnum; i++) {
			str.Format(_T("%d"), i);
			file = _T("D:\\dhfile") + str + _T(".vcf");
			file_w.Open(file, CFile::modeCreate | CFile::modeReadWrite);
			while (z < a_num) {
				CString out = head;
				out = out + data[y];
				out = out + _T("\r\n");
				out = out + food;
				file_w.WriteString(out);
				y++;
				z++;
			}
			z = 0;
			file_w.Close();
			Msg.Format(_T(" %d"), i + 1);
			msgbox.ReplaceSel(Msg);
		}


		//删除号码
		msgbox.ReplaceSel(_T("\r\n删除号码:"));

		for (int i = 0; i < vmnum; i++) {
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);  //DEL
			ShellExecute(NULL, _T("open"), adb, cmd, _T(""), SW_HIDE);
			Sleep(100);
			Msg.Format(_T(" %d"), i + 1);
			msgbox.ReplaceSel(Msg);

		}



		//复制号码
		msgbox.ReplaceSel( _T("\r\n复制号码:"));
		for (int i = 0; i < vmnum; i++) {
			str.Format(_T("%d"), i);
			file = _T("D:\\dhfile") + str + _T(".vcf");
			acction = " push ";
			acction += file;
			acction += " /sdcard/contacts.vcf";
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);  //COPY
			ShellExecute(NULL, _T("open"), adb, cmd, _T(""), SW_HIDE);
			Sleep(100);
			Msg.Format(_T(" %d"), i + 1);
			msgbox.ReplaceSel(Msg);
		}

		//导入号码

		msgbox.ReplaceSel(_T("\r\n导入号码:"));
		for (int i = 0; i < vmnum; i++) {
			acction = " shell am start -t \"text/x-vcard\" -d \"file:///sdcard/contacts.vcf\" -a android.intent.action.VIEW com.android.contacts";
			cmd = a + vmlist[i] + acction;
			AfxMessageBox(cmd);
			ShellExecute(NULL, _T("open"), adb, cmd, _T(""), SW_SHOW);
			Sleep(100);
			Msg.Format(_T(" %d"), i + 1);
			msgbox.ReplaceSel(Msg);
		}


		//导号结束
		msgbox.ReplaceSel(_T("\r\n导号成功!"));
		SetDlgItemText(IDC_BUTTON1, _T("打开导号文件"));
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);


	}

}


void CMBToolsDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);

	/*
	if (vmnum == 0) {
		AfxMessageBox("严重错误");
		exit(1);
	}

	CString adb = "D:\\Program Files\\Microvirt\\MEmu\\adb.exe";
	CString a = " -s ";
	CString acction = " shell pm clear com.android.providers.media";
	CString cmd;
	CString Msg;

	msgbox.SetWindowText("");
	msgbox.ReplaceSel("正在清理:");
	for (int i = 0; i < vmnum; i++) {
		cmd = a + vmlist[i] + acction;
		//AfxMessageBox(cmd);
		ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
		Sleep(100);
		Msg.Format(" %d", i + 1);
		msgbox.ReplaceSel(Msg);
	}
	msgbox.ReplaceSel("\r\n清理成功!");
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	*/
}


void CMBToolsDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CMBToolsDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


bool CMBToolsDlg::getVMlist() {

	return 1;
}
