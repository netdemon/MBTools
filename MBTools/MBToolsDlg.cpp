
// MBToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MBTools.h"
#include "MBToolsDlg.h"
#include "afxdialogex.h"
#include "xsleep.h"
#include "http.h"
#include "setup.h"


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
	DDX_Control(pDX, IDC_COMBO2, m_postunit);
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
	ON_BN_CLICKED(IDC_BUTTON4, &CMBToolsDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMBToolsDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMBToolsDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &CMBToolsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CMBToolsDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON11, &CMBToolsDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CMBToolsDlg::OnBnClickedButton12)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMBToolsDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMBToolsDlg::OnCbnSelchangeCombo2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON13, &CMBToolsDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CMBToolsDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CMBToolsDlg::OnBnClickedButton15)
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
	SetDlgItemText(IDC_BUTTON2, _T("主机发朋友圈"));
	SetDlgItemText(IDC_BUTTON3, _T("副机发朋友圈"));
	SetDlgItemText(IDC_BUTTON4, _T("自动添加好友"));
	SetDlgItemText(IDC_BUTTON5, _T("删除朋友圈一"));
	SetDlgItemText(IDC_BUTTON6, _T("安装支持程序"));
	SetDlgItemText(IDC_BUTTON7, _T("初始化模拟器"));
	SetDlgItemText(IDC_BUTTON8, _T("清除所有图片"));
	SetDlgItemText(IDC_BUTTON9, _T("清除通信录"));

	vmnum = getVMlist();
	vmNum.Format(_T("%d"), vmnum);
	vmNum = _T("当前模拟器数量：") + vmNum;
	SetDlgItemText(IDC_STATIC, vmNum);
	m_postunit.SetCurSel(0);
	SetTimer(TIMERRR, RRTIME, NULL);//启动刷新定时器

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
	if (vmnum == 0) {
		AfxMessageBox(_T("严重错误"));
		exit(1);
	}

	SetDlgItemText(IDOK, _T("正在发图"));
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	msgbox.EnableWindow(FALSE);
	disableall();
	if (edited == 0) {
		return;
	}
	edited = 0;

	SYSTEMTIME systime;
	GetLocalTime(&systime);
	CString Time;
	CString Text;
	Time.Format(_T("%d%d%d%d%d%d%d")
		, systime.wYear, systime.wMonth, systime.wDay
		, systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);
	CString id = Time;
	CString cmd;
	CString Msg;

	GetDlgItemText(IDC_EDIT1, Text);
	Text.Trim();
	Text.TrimRight(_T("\r\n"));
	Text.TrimRight(_T('\r'));
	Text.TrimRight(_T('\n'));
	Text.Replace(_T('\''), _T(' '));
	Text.Replace(_T("\r\n"), _T(""));
	Text.Replace(_T('\r'), _T(' '));
	Text.Replace(_T('\n'), _T(' '));
	Text.Replace(_T(" "), _T(""));
	CString UTF8_Text = Text;
	CString ANSI_Text = Text;
	//ANSItoUTF8(Text);
	UnicodeToANSI(ANSI_Text);
	UnicodeToUTF8(UTF8_Text);
	msgbox.SetWindowText(_T(""));
	//UpdateData(FALSE);

	/*
	acction = " shell am force-stop com.tencent.mm";
	msgbox.ReplaceSel("\r\n关闭微信:");
	for (int i = 0; i < vmnum; i++) {
	Msg.Format(" %d", i + 1);
	msgbox.ReplaceSel(Msg);
		cmd = a + vmlist[i] + acction;
		//AfxMessageBox(cmd);
		ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
		XSleep(200);
	}
	acction = " shell am start -n com.tencent.mm/com.tencent.mm.ui.LauncherUI";
	msgbox.ReplaceSel("\r\n开启微信:");
	for (int i = 0; i < vmnum; i++) {
	Msg.Format(" %d", i + 1);
	msgbox.ReplaceSel(Msg);
		cmd = a + vmlist[i] + acction;
		//AfxMessageBox(cmd);
		ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
		XSleep(1000);
	}
	*/

	/*  2017
	msgbox.ReplaceSel(_T("发送指令:"));
	adb_acction(_T(" shell /sdcard/MBTools/putpic"), 1000);
	msgbox.ReplaceSel(_T("\r\n等待点击:"));

#ifdef DEBUG
	int stime = 4000 / vmnum;
#else
	int stime = 40000 / vmnum;
#endif
	for (int i = 0; i < vmnum; i++) {
		Msg.Format(_T(" %d"), i + 1);
		msgbox.ReplaceSel(Msg);
		XSleep(stime);
	}
	*/
	msgbox.ReplaceSel(_T("\r\n服务同步:"));

	//删除文件
	/*
	CString post = "-d d=Yes";
	post += " ";
	post = post + HOST + POST;
	cmd = post;
	//AfxMessageBox(cmd);
	ShellExecute(NULL, "open", CURL, cmd, "", SW_HIDE);
	XSleep(2000);
	*/

	CString post = _T("-d id=");
	post += id;
	post += _T(" --data-urlencode t=");
	post += ANSI_Text;
	cmd = post + _T("  ") + HOST + POST;
	//AfxMessageBox(cmd);
	ShellExecute(NULL, _T("open"), CURL, cmd, _T(""), SW_HIDE);
	XSleep(2000);
	//列出D:\pic，一个一个POST
	CFileFind file;
	BOOL res = file.FindFile(_T("D:\\pic\\*.jpg"));//指定找mp3格式的文件
											   //BOOL res = file.FindFile(指定的文夹路径+"*.mp3")||file.FindFile(指定的文夹路径+"*.m4a");
	while (res)
	{
		res = file.FindNextFile();
		//不遍历子目录
		if (!file.IsDirectory() && !file.IsDots())
		{
			CString m_file = file.GetFilePath();
			//upload file
			CString acction = _T("-F id=");
			acction += id;
			acction += _T(" -F \"fileToUpload=@");
			CString cmd = acction + m_file + _T("\" ") + HOST + POST;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, _T("open"), CURL, cmd, _T(""), SW_HIDE);
			XSleep(1500);
			//DeleteFile(m_file);
		}
	}
	file.Close();

	/*  2017
	msgbox.ReplaceSel(_T("\r\n发送文本!"));
	adb_acction(_T(" shell am broadcast -a ADB_INPUT_TEXT --es msg ") + UTF8_Text, 1000);
	msgbox.ReplaceSel(_T("\r\n点击发送!"));
	adb_acction(_T(" shell input tap 321 50"), 2000);
	msgbox.ReplaceSel(_T("\r\n操作完成!"));
	adb_acction(_T(" shell input tap 24 48"), 2000);
	adb_acction(_T(" shell input tap 40 400"), 2000);
	*/

	msgbox.ReplaceSel(_T("\r\n操作完成!"));
	SetDlgItemText(IDOK, _T("确定"));
	SetDlgItemText(IDC_BUTTON2, _T("主机发朋友圈"));
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	msgbox.EnableWindow(TRUE);
	enableall();
	//SetDlgItemText(IDC_BUTTON4, _T("自动添加好友"));
	//GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	//theApp.GetMainWnd()->ShowWindow(SW_MINIMIZE);//最小化窗口
	//CDialog::OnOK();
}


void CMBToolsDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(TIMERAF);
	KillTimer(TIMERPP);
	KillTimer(TIMERRR);
	CDialog::OnCancel();
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

	if (btText == _T("打开导号文件")) {

		CFileDialog dlg(TRUE,//TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框 
			_T(".txt"),//默认的打开文件的类型 
			NULL,//默认打开的文件名 
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//打开只读文件 
			_T("文本文件(*.txt)|*.txt|所有文件 (*.*)|*.*||"));//所有可以打开的文件类型 

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
				data.Add(strLine);
				row++;
			}
			file_r.Close();
			if (!nogood) {
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
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		SetDlgItemText(IDC_BUTTON1, _T("导号中..."));
		if (vmnum == 0) {
			AfxMessageBox(_T("严重错误"));
			exit(1);
		}

		CString a = _T(" -s ");
		CString acction = _T(" shell pm clear com.android.providers.contacts");
		CString cmd;

		int a_num = row / vmnum;
		int y = 0;
		int z = 0;

		CString str;
		CString file;
		//生成文件
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
			Msg.Format(_T(" %d"), i + 1);
			msgbox.ReplaceSel(Msg);
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);  //DEL
			//ShellExecute(NULL, _T("open"), ADB, cmd, _T(""), SW_HIDE);
			//XSleep(500);
		}

		//复制号码
		msgbox.ReplaceSel(_T("\r\n复制号码:"));
		for (int i = 0; i < vmnum; i++) {
			Msg.Format(_T(" %d"), i + 1);
			msgbox.ReplaceSel(Msg);
			str.Format(_T("%d"), i);
			file = _T("D:\\dhfile") + str + _T(".vcf");
			acction = _T(" push ");
			acction += file;
			acction += _T(" /sdcard/contacts.vcf");
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);  //COPY
			ShellExecute(NULL, _T("open"), ADB, cmd, _T(""), SW_HIDE);
			XSleep(500);
		}

		//导入号码
		msgbox.ReplaceSel(_T("\r\n导入号码:"));
		for (int i = 0; i < vmnum; i++) {
			Msg.Format(_T(" %d"), i + 1);
			msgbox.ReplaceSel(Msg);
			//acction = _T(" shell am start -t \"text/x-vcard\" -d \"file:///sdcard/contacts.vcf\" -a android.intent.action.VIEW com.android.contacts");
			acction = _T(" shell am start -t \"text/x-vcard\" -d \"file:///sdcard/contacts.vcf\" -a android.intent.action.VIEW");
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, _T("open"), ADB, cmd, _T(""), SW_HIDE);
			XSleep(500);
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
	if (MessageBox(_T("确保所有模拟器图库为空\r\n使用任一模拟器手工保存最多9张图片并复制文字后按确定\r\n不然可能出错,没准备好请按取消并重新准备好"), _T("准备好了吗？"), MB_OKCANCEL) == IDOK) {
		SetDlgItemText(IDC_BUTTON2, _T("等待编辑文字"));
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		msgbox.EnableWindow(FALSE);
		edited = 0;

		CString ClipBoardText;
		HWND hWnd = GetSafeHwnd();
		ClipBoardText = GetClipBoardText(hWnd);

		CString path = _T("D:\\pic");
		msgbox.SetWindowText(_T(""));
		msgbox.ReplaceSel(_T("正在下图:"));
		//clean d:\\pic
		CFileFind file;
		BOOL res = file.FindFile(_T("D:\\pic\\*.jpg"));
		//BOOL res = file.FindFile(指定的文夹路径+"*.mp3")||file.FindFile(指定的文夹路径+"*.m4a");
		while (res)
		{
			res = file.FindNextFile();
			//不遍历子目录
			if (!file.IsDirectory() && !file.IsDots())
			{
				CString m_file = file.GetFilePath();
				DeleteFile(m_file);
			}
		}
		file.Close();
		adb_acction(_T(" pull /sdcard/tencent/MicroMsg/WeiXin ") + path, 500);
		//msgbox.ReplaceSel(_T("\r\n正在上图:"));
		//adb_acction(_T(" push ") + path + _T(" /sdcard/tencent/MicroMsg/WeiXin"), 1500);
		//msgbox.ReplaceSel(_T("\r\n刷新图库:"));
		//adb_acction(_T(" shell am broadcast -a android.intent.action.MEDIA_MOUNTED -d file:///sdcard/tencent/MicroMsg/WeiXin/"), 1500);
		msgbox.SetWindowText(ClipBoardText);
		msgbox.EnableWindow(TRUE);
		edited = 1;
	}
	else {
		//AfxMessageBox("Cancel");
		return;
	}
}


void CMBToolsDlg::OnBnClickedButton10()
{
	//刷新模拟器
	vmnum = getVMlist();
	vmNum.Format(_T("%d"), vmnum);
	vmNum = _T("当前模拟器数量：") + vmNum;
	SetDlgItemText(IDC_STATIC, vmNum);
}


void CMBToolsDlg::OnBnClickedButton8()
{
	//清除图片
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	msgbox.SetWindowText(_T(""));
	msgbox.ReplaceSel(_T("正在清理:"));
	adb_acction(_T(" shell rm \"/sdcard/tencent/MicroMsg/WeiXin/*\""), 100);
	adb_acction(_T(" shell rm \"/sdcard/vxt/*\""), 100);
	adb_acction(_T(" shell pm clear com.android.providers.media"), 100);
	msgbox.ReplaceSel(_T("\r\n清理成功!"));
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
	TCHAR cmd[MAX_PATH] = _T("D:\\ADB\\adb.exe devices");
	if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return FALSE;
	}
	CloseHandle(hWrite);
	char buffer[4096] = {0};       //用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。  
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
	file_w.Open(_T("D:\\vmlist"), CFile::modeCreate | CFile::modeReadWrite);
	file_w.WriteString(bf);
	file_w.Close();
	XSleep(200);

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
		/* 模拟器
		if (bf.Find(_T("127")) != -1)
		{
			vmlist.Add(bf);
		}
		*/
		BOOL bIsDigit = TRUE;
		for (int i = 0; i < 14; i++)
		{
			if (0 == isdigit(bf.GetAt(i)))
			{
				bIsDigit = FALSE;
				break;
			}
		}
		if (bIsDigit) {
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
	//清除联系人
	GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
	msgbox.SetWindowText(_T(""));
	msgbox.ReplaceSel(_T("正在清理:"));
	adb_acction(_T(" shell pm clear com.android.providers.contacts"), 200);
	msgbox.ReplaceSel(_T("\r\n清理成功!"));
	GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
	//SetTimer(TIMERAF, AFTIME, NULL);//启动定时器
	//SetTimer(TIMERPP, PPTIME, NULL);//启动定时器
}


void CMBToolsDlg::OnBnClickedButton4()
{
	//自动加人
	CString btText;
	GetDlgItem(IDC_BUTTON4)->GetWindowText(btText);
	if (btText == _T("自动添加好友")) {
		SetDlgItemText(IDC_BUTTON4, _T("正在进行加人"));
		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
		msgbox.SetWindowText(_T(""));
		msgbox.ReplaceSel(_T("正在加人:"));
		adb_acction(_T(" shell sh /sdcard/MBTools/addfir"), 1000);
		msgbox.ReplaceSel(_T("\r\n操作完成! 后台自动加人已启动"));
		SetDlgItemText(IDC_BUTTON4, _T("停止自动添加"));
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		//SetTimeOn;
		SetTimer(TIMERAF, AFTIME, NULL);//启动定时器
	}
	else {
		//SetTimeOff；
		KillTimer(TIMERAF);
		SetDlgItemText(IDC_BUTTON4, _T("自动添加好友"));
	}
}


void ANSItoUTF8(char* &strAnsi)
{
	//获取转换为宽字节后需要的缓冲区大小，创建宽字节缓冲区，936为简体中文GB2312代码页
	UINT nLen = MultiByteToWideChar(CP_ACP, NULL, strAnsi, -1, NULL, NULL);
	WCHAR *wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(CP_ACP, NULL, strAnsi, -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;
	//获取转为UTF8多字节后需要的缓冲区大小，创建多字节缓冲区
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
	CHAR *szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;
	strAnsi = szBuffer;
	//内存清理
	delete[]wszBuffer;
	delete[]szBuffer;
}

void ANSItoUnicode(CString &str)
{
	UINT nLen = MultiByteToWideChar(CP_ACP, NULL, (LPCSTR)(LPCWSTR)str, -1, NULL, NULL);
	WCHAR *wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(CP_ACP, NULL, (LPCSTR)(LPCWSTR)str, -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;
	str = wszBuffer;
	//内存清理
	delete[]wszBuffer;
}


void UnicodeToANSI(CString &str)
{
	UINT nLen = WideCharToMultiByte(CP_ACP, NULL, str, -1, NULL, NULL, NULL, NULL);
	CHAR *szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(CP_ACP, NULL, str, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;
	str = szBuffer;
	//内存清理
	delete[]szBuffer;
}


void UnicodeToUTF8(CString &str)
{
	int nLen = WideCharToMultiByte(CP_UTF8, NULL, str, -1, NULL, NULL, NULL, NULL);
	CHAR *szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(CP_UTF8, NULL, str, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;
	str = szBuffer;
	//内存清理
	delete[]szBuffer;
}


void UTF8ToUnicode(CString &str)
{
	UINT nLen = MultiByteToWideChar(CP_UTF8, NULL, (LPCSTR)(LPCWSTR)str, -1, NULL, NULL);
	WCHAR *wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(CP_UTF8, NULL, (LPCSTR)(LPCWSTR)str, -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;
	str = wszBuffer;
	//内存清理
	delete[]wszBuffer;
}


char * Uto8(const wchar_t* str)
{
	char* result;
	int textlen;
	textlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	result = (char *)malloc((textlen + 1) * sizeof(char));
	memset(result, 0, sizeof(char) * (textlen + 1));
	WideCharToMultiByte(CP_UTF8, 0, str, -1, result, textlen, NULL, NULL);
	return result;
}


void CMBToolsDlg::OnBnClickedButton5()
{
	//删除朋友圈
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	msgbox.SetWindowText(_T(""));
	msgbox.ReplaceSel(_T("正在删除:"));
	adb_acction(_T(" shell sh /sdcard/MBTools/delpic"), 100);
	msgbox.ReplaceSel(_T("\r\n删除成功!"));
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
}


void CMBToolsDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//adb_acction(_T(" shell svc power stayon usb"), 200);
	adb_acction(_T(" install d:\\keyboardservice-debug.apk"), 200);
	adb_acction(_T(" install d:\\weixin656android1020.apk"), 200);
}


void CMBToolsDlg::OnBnClickedButton3()
{
	//副机发朋友圈
	if (vmnum == 0) {
		AfxMessageBox(_T("严重错误"));
		exit(1);
	}
	disableall();

	//adb_acction(_T(" shell am broadcast -a android.intent.action.MEDIA_MOUNTED -d file://sdcard/"), 200);

	m_postunit.EnableWindow(FALSE);
	msgbox.EnableWindow(FALSE);
	msgbox.SetWindowText(_T(""));
	msgbox.ReplaceSel(_T("\r\n正在下图:"));
	//int unitnum = m_postunit.GetCurSel();
	//unitnum += 1;

	CString sNum;
	GetDlgItem(IDC_COMBO2)->GetWindowText(sNum);
	CString path = _T("D:\\pic");
	CString geturl = HOST;
	geturl += DOWN;
	geturl += _T("?n=");

	CString picurl = HOST;
	picurl += _T("/pic/");

	if (!PathFileExists(path)) {
		CreateDirectory(_T("D:\\pic"), NULL);
	}
	Download(geturl + sNum, _T("D:\\last"));
	XSleep(3000);
	CStdioFile last;
	CString id;
	if (!last.Open(_T("D:\\last"), CFile::modeRead)) {
		AfxMessageBox(_T("发生了错误"));
		return;
	}
	else {
		while (last.ReadString(id))
		{
			id.Trim();
			CString idpath = path + _T("\\") + id;
			CreateDirectory(idpath, NULL);
			Download(picurl + id + _T("/list"), idpath + _T("\\piclist"));
			Download(picurl + id + _T("/title"), idpath + _T("\\title"));
			XSleep(500);
			CStdioFile file;
			CString strLine;
			if (!file.Open(idpath + _T("\\piclist"), CFile::modeRead)) {
				AfxMessageBox(_T("发生了错误"));
				return;
			}
			else {
				while (file.ReadString(strLine))
				{
					strLine.Trim();
					//下载图片
					Download(picurl + id + _T("/") + strLine, idpath + _T("\\") + strLine);
				}
			}
			file.Close();
			msgbox.ReplaceSel(_T("清理图片!"));
			adb_acction(_T(" shell rm \"/sdcard/tencent/MicroMsg/WeiXin/*\""), 100);
			adb_acction(_T(" shell pm clear com.android.providers.media"), 100);
			XSleep(3000);
			//发送图片到模拟器
			msgbox.ReplaceSel(_T("\r\n正在上图:"));
			adb_acction(_T(" push ") + idpath + _T(" /sdcard/tencent/MicroMsg/WeiXin"), 200); //1000
			XSleep(2000); //
			adb_acction(_T(" shell am broadcast -a android.intent.action.MEDIA_MOUNTED -d file://sdcard/"), 4000); //2000
			//adb_acction(_T(" shell am broadcast -a android.intent.action.MEDIA_MOUNTED -d file:///sdcard/tencent/MicroMsg/WeiXin/"), 2000);
			XSleep(20000); //
			msgbox.ReplaceSel(_T("\r\n发送指令:"));
			adb_acction(_T(" shell sh /sdcard/MBTools/putpic"), 100); //
			msgbox.ReplaceSel(_T("\r\n等待文字:"));
#ifdef DEBUG
			int stime = 4000 / vmnum;
#else
			int stime = 40000 / vmnum;  //4000
#endif
			CString Msg;
			for (int i = 0; i < vmnum; i++) {
				Msg.Format(_T(" %d"), i + 1);
				msgbox.ReplaceSel(Msg);
				XSleep(stime);
			}
			msgbox.ReplaceSel(_T("\r\n发送文本!"));
			adb_acction(_T(" shell ime set com.android.adbkeyboard/.AdbIME"), 100);
			CString title;
			char ansi_title[4096] = { 0 };
			CFile mfile;
			mfile.Open(idpath + _T("\\title"), CFile::modeRead);
			mfile.Read(ansi_title, 4096);
			mfile.Close();
			//USES_CONVERSION;
			//char* utf8_title = T2A(title.GetBuffer(0));
			//title.ReleaseBuffer();
			title = ansi_title;
			//AfxMessageBox(title);
			UnicodeToUTF8(title);
			adb_acction(_T(" shell am broadcast -a ADB_INPUT_TEXT --es msg  ") + title, 100);
			XSleep(1000);
			msgbox.ReplaceSel(_T("\r\n点击发送!"));
			adb_acction(_T(" shell input tap 420 64"), 200); //2000
			XSleep(2000);
			//msgbox.ReplaceSel(_T("\r\n清理图片!"));
			//adb_acction(_T(" shell rm \"/sdcard/tencent/MicroMsg/WeiXin/*\""), 1000);
			//adb_acction(_T(" shell pm clear com.android.providers.media"), 1000);
			adb_acction(_T(" shell input tap 32 64"), 100); //微信返回
			XSleep(1000);
			adb_acction(_T(" shell input tap 70 820"), 100); //微信界面
			msgbox.ReplaceSel(_T("\r\n发送完成，等待下轮!"));
			adb_acction(_T(" shell ime set com.aliyun.mobile.ime/.AImeService"), 100);
			//XSleep(3000);
		}
	}
	last.Close();
	msgbox.ReplaceSel(_T("\r\n操作完成!"));
	//adb_acction(_T(" shell ime set com.aliyun.mobile.ime/.AImeService"), 100);
	enableall();
	msgbox.EnableWindow(TRUE);
	m_postunit.EnableWindow(TRUE);
}

void CMBToolsDlg::OnBnClickedButton7()
{
	//初始化模拟器
	disableall();
	msgbox.SetWindowText(_T(""));
	msgbox.ReplaceSel(_T("正在进行:"));
	adb_acction(_T(" shell rm \"/sdcard/tencent/MicroMsg/WeiXin/*\""), 100);
	//adb_acction(_T(" shell rm \"/sdcard/vxt/*\""), 500);
	//adb_acction(_T(" shell pm clear com.android.providers.media"), 500);
	adb_acction(_T(" push D:\\PutPicSH /sdcard/MBTools/putpic"), 100);
	adb_acction(_T(" push D:\\AddFirSH /sdcard/MBTools/addfir"), 100);
	adb_acction(_T(" push D:\\DelPicSH /sdcard/MBTools/delpic"), 100);
	msgbox.ReplaceSel(_T("\r\n初始化完成!"));
	enableall();
}

/*
void CMBToolsDlg::OnBnClickedButton11()
{
	//发送聊天内容
	CString Text;
	CString cmd;
	CString acction = _T(" shell am broadcast -a ADB_INPUT_TEXT --es msg ");

	GetDlgItemText(IDC_EDIT1, Text);
	char* buf = NULL;
	buf = Uto8(Text);
	//UnicodeToUTF8(Text);
	acction += buf;
	for (int i = 0; i < vmnum; i++) {
		cmd = _T(" -s ") + vmlist[i] + acction;
		ShellExecute(NULL, _T("open"), ADB, cmd, _T(""), SW_HIDE);
		//XSleep(250);
		//cmd = _T(" -s ") + vmlist[i] + _T(" shell input keyevent 66");
		cmd = _T(" -s ") + vmlist[i] + _T(" shell input tap 330 410");
		ShellExecute(NULL, _T("open"), ADB, cmd, _T(""), SW_HIDE);
	}
	msgbox.SetWindowText(_T(""));
	UpdateData(false);
	GetDlgItem(IDC_EDIT1)->SetFocus();
}
*/
void CMBToolsDlg::OnBnClickedButton11()
{
	//发送命令
	CString Text;
	CString cmd;
	GetDlgItemText(IDC_EDIT1, Text);
	char* buf = NULL;
	cmd = _T(" shell ") + Text;
	adb_acction(cmd, 100);
	msgbox.SetWindowText(_T(""));
	UpdateData(false);
	GetDlgItem(IDC_EDIT1)->SetFocus();
}

void CMBToolsDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//GetDlgItemText(IDC_COMBO1, Text);
	//msgbox.SetWindowText(Text);
	//UpdateData(false);
	//GetDlgItem(IDC_EDIT1)->SetFocus();
}


void CMBToolsDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	msgbox.SetWindowText(_T(""));
	UpdateData(false);
	GetDlgItem(IDC_EDIT1)->SetFocus();
}


void CMBToolsDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMBToolsDlg::disableall()
{
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(FALSE);
}


void CMBToolsDlg::enableall()
{
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(TRUE);
}


void CMBToolsDlg::adb_acction(CString acction, int sleeptime)
{
	CString cmd;
	CString msg;
	for (int i = 0; i < vmnum; i++) {
		msg.Format(_T(" %d"), i + 1);
		msgbox.ReplaceSel(msg);
		cmd = _T(" -s ") + vmlist[i] + _T(" ") + acction;
		//AfxMessageBox(cmd);
		ShellExecute(NULL, _T("open"), ADB, cmd, _T(""), SW_HIDE);
		XSleep(sleeptime);
	}
}


void CMBToolsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)
	{
	case TIMERAF:
	{
		//AfxMessageBox(_T("定时器加友!"));
		SetDlgItemText(IDC_BUTTON4, _T("正在进行加人"));
		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
		msgbox.SetWindowText(_T(""));
		msgbox.ReplaceSel(_T("正在加人:"));
		adb_acction(_T(" shell sh /sdcard/MBTools/addfir"), 100);
		msgbox.ReplaceSel(_T("\r\n操作完成!"));
		SetDlgItemText(IDC_BUTTON4, _T("停止自动添加"));
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		break;
	}
	case TIMERPP:
	{
		AfxMessageBox(_T("定时器发图!"));
		break;
	}
	case TIMERRR:
	{
		adb_acction(_T(" shell input swipe 240 00 240 80"), 100);
		break;
	}
	default:
		break;
	}

	CDialog::OnTimer(nIDEvent);
}


void CMBToolsDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码 320
	//声音控制
	CString btText;
	GetDlgItem(IDC_BUTTON13)->GetWindowText(btText);
	if (btText == _T("关闭声音 320")) {
		SetDlgItemText(IDC_BUTTON13, _T("开启声音 320"));
		adb_acction(_T(" shell am start -W com.android.settings"), 250);
		adb_acction(_T(" shell input tap 240 780"), 200);
		adb_acction(_T(" shell input tap 240 170"), 200);
		adb_acction(_T(" shell input tap 240 725"), 200);
		adb_acction(_T(" shell am start -W com.tencent.mm/com.tencent.mm.ui.LauncherUI"), 500);
	}
	else {
		SetDlgItemText(IDC_BUTTON13, _T("关闭声音 320"));
		adb_acction(_T(" shell am start -W com.android.settings"), 250);
		adb_acction(_T(" shell input tap 240 780"), 200);
		adb_acction(_T(" shell input tap 240 170"), 200);
		adb_acction(_T(" shell input tap 240 660"), 200);
		adb_acction(_T(" shell am start -W com.tencent.mm/com.tencent.mm.ui.LauncherUI"), 500);
	}
}

/*
void CMBToolsDlg::OnBnClickedButton13()  310
{
// TODO: 在此添加控件通知处理程序代码
//声音控制
CString btText;
GetDlgItem(IDC_BUTTON13)->GetWindowText(btText);
if (btText == _T("关闭声音")) {
SetDlgItemText(IDC_BUTTON13, _T("开启声音"));
adb_acction(_T(" shell am start -W com.android.settings"), 2000);
adb_acction(_T(" shell input tap 240 680"), 1000);
adb_acction(_T(" shell input tap 240 170"), 1000);
adb_acction(_T(" shell input tap 240 280"), 1000);
adb_acction(_T(" shell am start -W com.tencent.mm/com.tencent.mm.ui.LauncherUI"), 1000);
}
else {
SetDlgItemText(IDC_BUTTON13, _T("关闭声音"));
adb_acction(_T(" shell am start -W com.android.settings"), 2000);
adb_acction(_T(" shell input tap 240 680"), 1000);
adb_acction(_T(" shell input tap 240 170"), 1000);
adb_acction(_T(" shell input tap 240 194"), 1000);
adb_acction(_T(" shell am start -W com.tencent.mm/com.tencent.mm.ui.LauncherUI"), 1000);
}
}
*/


void CMBToolsDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码 310
	CString btText;
	GetDlgItem(IDC_BUTTON14)->GetWindowText(btText);
	if (btText == _T("关闭声音 310")) {
		SetDlgItemText(IDC_BUTTON14, _T("开启声音 310"));
		adb_acction(_T(" shell am start -W com.android.settings"), 100);
		adb_acction(_T(" shell input tap 240 680"), 100);
		adb_acction(_T(" shell input tap 240 170"), 100);
		adb_acction(_T(" shell input tap 240 280"), 100);
		adb_acction(_T(" shell am start -W com.tencent.mm/com.tencent.mm.ui.LauncherUI"), 100);
	}
	else {
		SetDlgItemText(IDC_BUTTON14, _T("关闭声音 310"));
		adb_acction(_T(" shell am start -W com.android.settings"), 100);
		adb_acction(_T(" shell input tap 240 680"), 100);
		adb_acction(_T(" shell input tap 240 170"), 100);
		adb_acction(_T(" shell input tap 240 194"), 100);
		adb_acction(_T(" shell am start -W com.tencent.mm/com.tencent.mm.ui.LauncherUI"), 100);
	}
}


void CMBToolsDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	CMBToolsSet setupdlg;
	setupdlg.DoModal();
}
