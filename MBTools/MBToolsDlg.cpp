
// MBToolsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MBTools.h"
#include "MBToolsDlg.h"
#include "afxdialogex.h"
#include "xsleep.h"
#include "http.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMBToolsDlg �Ի���

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
END_MESSAGE_MAP()


// CMBToolsDlg ��Ϣ�������

BOOL CMBToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	SetDlgItemText(IDC_BUTTON1, _T("�򿪵����ļ�"));
	SetDlgItemText(IDC_BUTTON2, _T("����������Ȧ"));
	SetDlgItemText(IDC_BUTTON3, _T("����������Ȧ"));
	SetDlgItemText(IDC_BUTTON4, _T("�Զ���Ӻ���"));
	SetDlgItemText(IDC_BUTTON5, _T("ɾ������Ȧһ"));
	SetDlgItemText(IDC_BUTTON6, _T("TESTPOST"));
	SetDlgItemText(IDC_BUTTON7, _T("��ʼ��ģ����"));
	SetDlgItemText(IDC_BUTTON8, _T("�������ͼƬ"));
	SetDlgItemText(IDC_BUTTON9, _T("TEST"));

	vmnum = getVMlist();
	vmNum.Format(_T("%d"), vmnum);
	vmNum = "��ǰģ����������" + vmNum;
	SetDlgItemText(IDC_STATIC, vmNum);
	m_postunit.SetCurSel(2);


	// END�ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMBToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMBToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMBToolsDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CMBToolsDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (edited == 1) { GetDlgItem(IDOK)->EnableWindow(TRUE); };

}



void CMBToolsDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	SetDlgItemText(IDOK, "���ڷ�ͼ");
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	disableall();
	if (edited == 0) {
		return;
	}
	edited = 0;

	SYSTEMTIME systime;
	GetLocalTime(&systime);
	CString Time;
	CString Text;
	Time.Format("%d%d%d%d%d%d%d"
		, systime.wYear, systime.wMonth, systime.wDay
		, systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);
	CString id = Time;
	CString cmd;
	CString Msg;

	GetDlgItemText(IDC_EDIT1, Text);
	Text.Trim();
	Text.TrimRight("\r\n");
	Text.TrimRight('\r');
	Text.TrimRight('\n');
	Text.Replace('\'', ' ');
	Text.Replace("\r\n", "");
	Text.Replace('\r', ' ');
	Text.Replace('\n', ' ');
	Text.Replace(" ", "");
	CString GBText = Text;
	ANSItoUTF8(Text);

	msgbox.SetWindowText("");
	UpdateData(FALSE);

	/*
	acction = " shell am force-stop com.tencent.mm";
	msgbox.ReplaceSel("\r\n�ر�΢��:");
	for (int i = 0; i < vmnum; i++) {
	Msg.Format(" %d", i + 1);
	msgbox.ReplaceSel(Msg);
		cmd = a + vmlist[i] + acction;
		//AfxMessageBox(cmd);
		ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
		XSleep(200);
	}
	acction = " shell am start -n com.tencent.mm/com.tencent.mm.ui.LauncherUI";
	msgbox.ReplaceSel("\r\n����΢��:");
	for (int i = 0; i < vmnum; i++) {
	Msg.Format(" %d", i + 1);
	msgbox.ReplaceSel(Msg);
		cmd = a + vmlist[i] + acction;
		//AfxMessageBox(cmd);
		ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
		XSleep(1000);
	}
	*/

	msgbox.ReplaceSel("\r\n����ָ��:");
	adb_acction(" shell /sdcard/MBTools/putpic", 1000);
	msgbox.ReplaceSel("\r\n�ȴ����:");

#ifdef DEBUG
	int stime = 4000 / vmnum;
#else
	int stime = 40000 / vmnum;
#endif
	for (int i = 0; i < vmnum; i++) {
		Msg.Format(" %d", i + 1);
		msgbox.ReplaceSel(Msg);
		XSleep(stime);
	}
	msgbox.ReplaceSel("\r\n����ͬ��:");

	//ɾ���ļ�
	/*
	CString post = "-d d=Yes";
	post += " ";
	post = post + HOST + POST;
	cmd = post;
	//AfxMessageBox(cmd);
	ShellExecute(NULL, "open", CURL, cmd, "", SW_HIDE);
	XSleep(2000);
	*/

	CString post = "-d id=";
	post += id;
	post += " --data-urlencode t=";
	post += GBText;
	cmd = post + "  " + HOST + POST;
	//AfxMessageBox(cmd);
	ShellExecute(NULL, "open", CURL, cmd, "", SW_HIDE);
	XSleep(2000);
	//�г�D:\pic��һ��һ��POST
	CFileFind file;
	BOOL res = file.FindFile("D:\\pic\\*.jpg");//ָ����mp3��ʽ���ļ�
											   //BOOL res = file.FindFile(ָ�����ļ�·��+"*.mp3")||file.FindFile(ָ�����ļ�·��+"*.m4a");
											   //��ʾͬʱ��mp3��m4a��ʽ���ļ�
	while (res)
	{
		res = file.FindNextFile();
		//��������Ŀ¼
		if (!file.IsDirectory() && !file.IsDots())
		{
			CString m_file = file.GetFilePath();
			//upload file
			CString acction = "-F id=";
			acction += id;
			acction += " -F \"fileToUpload=@";
			CString cmd = acction + m_file + "\" " + HOST + POST;
			CString Msg;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, "open", CURL, cmd, "", SW_HIDE);
			XSleep(500);
			//del file
			////////////////////////////////////////////////////////
		}
	}
	file.Close();

	msgbox.ReplaceSel("\r\n�����ı�!");
	adb_acction(" shell am broadcast -a ADB_INPUT_TEXT --es msg " + Text, 1000);
	msgbox.ReplaceSel("\r\n�������!");
	adb_acction(" shell input tap 321 50", 2000);
	msgbox.ReplaceSel("\r\n�������!");

	SetDlgItemText(IDOK, "ȷ��");
	SetDlgItemText(IDC_BUTTON2, _T("����������Ȧ"));
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	enableall();
	//SetDlgItemText(IDC_BUTTON4, _T("�Զ���Ӻ���"));
	//GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	//theApp.GetMainWnd()->ShowWindow(SW_MINIMIZE);//��С������
	//CDialog::OnOK();
}


void CMBToolsDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}



void CMBToolsDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Msg;
	CString m_path;
	CString btText;
	CString tmp_path = "C:\\tmp";

	CString head = "BEGIN:VCARD\r\nVERSION:3.0\r\nTEL;TYPE=cell:";
	CString food = "END:VCARD\r\n";

	CStdioFile file_r;
	CStdioFile file_w;

	GetDlgItem(IDC_BUTTON1)->GetWindowText(btText);

	if (btText == "�򿪵����ļ�") {

		CFileDialog dlg(TRUE,//TRUE�Ǵ������ļ��Ի���FALSE�򴴽����Ǳ����ļ��Ի��� 
			".txt",//Ĭ�ϵĴ��ļ������� 
			NULL,//Ĭ�ϴ򿪵��ļ��� 
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//��ֻ���ļ� 
			"�ı��ļ�(*.txt)|*.txt|�����ļ� (*.*)|*.*||");//���п��Դ򿪵��ļ����� 

		if (dlg.DoModal() == IDOK)
		{
			m_path = dlg.GetPathName(); //ȡ���ļ�·�� 
			UpdateData(FALSE);
			//���ļ�
			file_r.Open(m_path, CFile::modeRead);
			//���ж�ȡ�ļ�
			//CStdioFile File  = file ;///�������ж��ļ����� 
			CString   strLine;
			row = 1;

			int nogood = 0;
			int nogoodrow = 1;

			while (file_r.ReadString(strLine))   // //��ÿ�ж��Ž�strLine�ַ�����
			{
				//�����ļ��Ƿ���ȷ
				//�ж϶���������
				//ȥ���հ�
				strLine.Trim();
				//ȥ������
				strLine.TrimRight(';');
				if (strLine.GetLength() != 11) {
					nogood = 1;
					nogoodrow = row;
					Msg.Format("�ļ��� %d ���д��������", row);
					AfxMessageBox(Msg);
					break;
				}
				data.Add(strLine);
				row++;
			}
			file_r.Close();
			if (!nogood) {
				msgbox.SetWindowText("");
				SetDlgItemText(IDC_BUTTON1, "��ʼ����");
			}
		}

		//CFileFind fFind;
		//CString adb = "D:\\Program Files\\Microvirt\\MEmu\\adb.exe";
		//if(fFind.FindFile(adb)){AfxMessageBox("����"); }else{AfxMessageBox("������");}

	}
	else {
		// ���Ų���
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		SetDlgItemText(IDC_BUTTON1, "������...");
		if (vmnum == 0) {
			AfxMessageBox("���ش���");
			exit(1);
		}

		CString a = " -s ";
		CString acction = " shell pm clear com.android.providers.contacts";
		CString cmd;

		int a_num = row / vmnum;
		int y = 0;
		int z = 0;

		CString str;
		CString file;
		//�����ļ�
		msgbox.ReplaceSel("�����ļ�:");
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

		//ɾ������
		msgbox.ReplaceSel("\r\nɾ������:");
		for (int i = 0; i < vmnum; i++) {
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);  //DEL
			ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
			XSleep(500);
		}

		//���ƺ���
		msgbox.ReplaceSel("\r\n���ƺ���:");
		for (int i = 0; i < vmnum; i++) {
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
			str.Format("%d", i);
			file = "D:\\dhfile" + str + ".vcf";
			acction = " push ";
			acction += file;
			acction += " /sdcard/contacts.vcf";
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);  //COPY
			ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
			XSleep(500);
		}

		//�������
		msgbox.ReplaceSel("\r\n�������:");
		for (int i = 0; i < vmnum; i++) {
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
			acction = " shell am start -t \"text/x-vcard\" -d \"file:///sdcard/contacts.vcf\" -a android.intent.action.VIEW com.android.contacts";
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
			XSleep(500);
		}

		//���Ž���
		msgbox.ReplaceSel("\r\n���ųɹ�!");
		SetDlgItemText(IDC_BUTTON1, "�򿪵����ļ�");
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}

}


void CMBToolsDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (MessageBox("ȷ������ģ����ͼ��Ϊ��\r\nʹ����һģ�����ֹ��������9��ͼƬ���������ֺ�ȷ��\r\n��Ȼ���ܳ���,û׼�����밴ȡ��������׼����", "׼��������", MB_OKCANCEL) == IDOK) {
		SetDlgItemText(IDC_BUTTON2, "�ȴ��༭����");
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		edited = 0;

		CString ClipBoardText;
		HWND hWnd = GetSafeHwnd();
		ClipBoardText = GetClipBoardText(hWnd);

		msgbox.SetWindowText("");
		msgbox.ReplaceSel("������ͼ:");
		adb_acction(" pull /sdcard/tencent/MicroMsg/WeiXin D:\\pic", 500);
		msgbox.ReplaceSel("\r\n������ͼ:");
		adb_acction(" push D:\\pic /sdcard/tencent/MicroMsg/WeiXin", 500);
		msgbox.ReplaceSel("\r\nˢ��ͼ��:");
		adb_acction(" shell am broadcast -a android.intent.action.MEDIA_MOUNTED -d file:///sdcard/", 500);
		msgbox.SetWindowText(ClipBoardText);
		edited = 1;
	}
	else {
		//AfxMessageBox("Cancel");
		return;
	}
}


void CMBToolsDlg::OnBnClickedButton10()
{
	//ˢ��ģ����
	vmnum = getVMlist();
	vmNum.Format(_T("%d"), vmnum);
	vmNum = "��ǰģ����������" + vmNum;
	SetDlgItemText(IDC_STATIC, vmNum);
}


void CMBToolsDlg::OnBnClickedButton8()
{
	//���ͼƬ
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	msgbox.SetWindowText("");
	msgbox.ReplaceSel("��������:");
	adb_acction(" shell rm \"/sdcard/tencent/MicroMsg/WeiXin/*\"", 1000);
	adb_acction(" shell pm clear com.android.providers.media", 1000);
	msgbox.ReplaceSel("\r\n����ɹ�!");
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
	si.hStdError = hWrite;            //�Ѵ������̵ı�׼��������ض��򵽹ܵ�����
	si.hStdOutput = hWrite;           //�Ѵ������̵ı�׼����ض��򵽹ܵ�����
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//�ؼ����裬CreateProcess�����������������MSDN
	CString adb = ADB;
	adb += " devices";
	if (!CreateProcess(NULL, (LPSTR)(LPCTSTR)adb, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return FALSE;
	}
	CloseHandle(hWrite);
	char buffer[4096] = { 0 };       //��4K�Ŀռ����洢��������ݣ�ֻҪ������ʾ�ļ����ݣ�һ��������ǹ����ˡ�  
	DWORD bytesRead;
	CString bf;
	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
		{
			break;
		}
		//buffer�о���ִ�еĽ�������Ա��浽�ı���Ҳ����ֱ�����  
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
		//AfxMessageBox(bf);
		if (bf.Find(_T("127.0.0.1")) != -1)
		{
			vmlist.Add(bf);
		}
	}
	file_r.Close();
	vmnum = vmlist.GetSize();
	return vmnum;
}


//��ȡ�������ı�����  
CString GetClipBoardText(HWND hWnd)
{
	ASSERT(hWnd);
	CString ClipBoardText;
	//�жϼ���������ݸ�ʽ�Ƿ���Դ���    
	if (!IsClipboardFormatAvailable(CF_TEXT))
		return ClipBoardText;

	//�򿪼����塣            
	if (!::OpenClipboard(hWnd))
		return ClipBoardText;

	//��ȡ����    
	HANDLE hMem = GetClipboardData(CF_TEXT);
	if (hMem != NULL)
	{
		//��ȡ�ַ�����    
		LPSTR lpStr = (LPSTR)GlobalLock(hMem);
		if (lpStr != NULL)
		{
			ClipBoardText = lpStr;
			//�ͷ����ڴ�    
			GlobalUnlock(hMem);
		}
	}
	//�رռ�����          
	CloseClipboard();
	return ClipBoardText;
}


void CMBToolsDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//TEST

}


void CMBToolsDlg::OnBnClickedButton4()
{
	//�Զ�����
	SetDlgItemText(IDC_BUTTON4, "���ڽ��м���");
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	msgbox.SetWindowText("");
	msgbox.ReplaceSel("���ڼ���:");
	adb_acction(" shell /sdcard/MBTools/addfir", 1000);
	msgbox.ReplaceSel("\r\n�������!");
	SetDlgItemText(IDC_BUTTON4, _T("�Զ���Ӻ���"));
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}


void ANSItoUTF8(CString &strAnsi)
{
	//��ȡת��Ϊ���ֽں���Ҫ�Ļ�������С���������ֽڻ�������936Ϊ��������GB2312����ҳ
	UINT nLen = MultiByteToWideChar(CP_ACP, NULL, strAnsi, -1, NULL, NULL);
	WCHAR *wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(CP_ACP, NULL, strAnsi, -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;
	//��ȡתΪUTF8���ֽں���Ҫ�Ļ�������С���������ֽڻ�����
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
	CHAR *szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;
	strAnsi = szBuffer;
	//�ڴ�����
	delete[]wszBuffer;
	delete[]szBuffer;
}


void CMBToolsDlg::OnBnClickedButton5()
{
	//ɾ������Ȧ
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	msgbox.SetWindowText("");
	msgbox.ReplaceSel("����ɾ��:");
	adb_acction(" shell /sdcard/MBTools/delpic", 1000);
	msgbox.ReplaceSel("\r\nɾ���ɹ�!");
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
}


void CMBToolsDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	CFile file_r;
	CFileDialog dlg(TRUE,//TRUE�Ǵ������ļ��Ի���FALSE�򴴽����Ǳ����ļ��Ի���
		".txt",//Ĭ�ϵĴ��ļ�������
		NULL,//Ĭ�ϴ򿪵��ļ���
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//��ֻ���ļ�
		"ͼƬ�ļ�(*.JPG)|*.jpg|�����ļ� (*.*)|*.*||");//���п��Դ򿪵��ļ�����


	if (dlg.DoModal() == IDOK)
	{

		CString m_path = dlg.GetPathName(); //ȡ���ļ�·��
		UpdateData(FALSE);

		CString acction = "-F fileToUpload=@"; // d:\\tmp\\";
		CString cmd;
		CString Msg;
		cmd = acction + m_path + " " + HOST + POST;
		AfxMessageBox(cmd);
		XSleep(100);
		ShellExecute(NULL, "open", CURL, cmd, "", SW_HIDE);

	}
	*/

	//�г�D:\pic��һ��һ��POST
	CFileFind file;
	BOOL res = file.FindFile("D:\\pic\\*.jpg");//ָ����mp3��ʽ���ļ�
											 //BOOL res = file.FindFile(ָ�����ļ�·��+"*.mp3")||file.FindFile(ָ�����ļ�·��+"*.m4a");
											 //��ʾͬʱ��mp3��m4a��ʽ���ļ�
	while (res)
	{
		res = file.FindNextFile();
		//��������Ŀ¼
		if (!file.IsDirectory() && !file.IsDots())
		{
			CString m_file = file.GetFilePath();
			//upload file
			CString acction = "-F \"fileToUpload=@"; // d:\\tmp\\";
			CString cmd;
			CString Msg;
			cmd = acction + m_file + "\" " + HOST + POST;
			AfxMessageBox(cmd);
			XSleep(100);
			ShellExecute(NULL, "open", CURL, cmd, "", SW_HIDE);

		}
	}
	file.Close();
}


void CMBToolsDlg::OnBnClickedButton3()
{
	//����������Ȧ
	disableall();
	m_postunit.EnableWindow(FALSE);
	msgbox.EnableWindow(FALSE);
	msgbox.SetWindowText("");
	msgbox.ReplaceSel("������ͼ:");
	//int unitnum = m_postunit.GetCurSel();
	//unitnum += 1;

	CString sNum;
	GetDlgItem(IDC_COMBO2)->GetWindowText(sNum);
	CString path = "D:\\pic";
	CString geturl = HOST;
	geturl += DOWN;
	geturl += "?n=";

	CString picurl = HOST;
	picurl += "/pic/";

	if (!PathFileExists(path)) {
		CreateDirectory("D:\\pic", NULL);
	}
	Download(geturl + sNum, "D:\\last");
	XSleep(3000);
	CStdioFile last;
	CString id;
	if (!last.Open("D:\\last", CFile::modeRead)) {
		AfxMessageBox("�����˴���");
		return;
	}
	else {
		while (last.ReadString(id))
		{
			id.Trim();
			CString idpath = path + "\\" + id;
			CreateDirectory(idpath, NULL);
			Download(picurl + id + "/list", idpath + "\\piclist");
			Download(picurl + id + "/title", idpath + "\\title");
			XSleep(500);
			CStdioFile file;
			CString strLine;
			if (!file.Open(idpath + "\\piclist", CFile::modeRead)) {
				AfxMessageBox("�����˴���");
				return;
			}
			else {
				while (file.ReadString(strLine))
				{
					strLine.Trim();
					//����ͼƬ
					Download(picurl + id + "/" + strLine, idpath + "\\" + strLine);
				}
			}
			file.Close();
			//����
			//����ͼƬ��ģ����
			adb_acction(" push " + idpath + " /sdcard/tencent/MicroMsg/WeiXin", 1000);
			adb_acction(" shell am broadcast -a android.intent.action.MEDIA_MOUNTED -d file:///sdcard/", 2000);
			msgbox.ReplaceSel("\r\n����ָ��:");
			adb_acction(" shell /sdcard/MBTools/putpic", 1000);
			msgbox.ReplaceSel("\r\n�ȴ����:");
#ifdef DEBUG
			int stime = 4000 / vmnum;
#else
			int stime = 40000 / vmnum;
#endif
			CString Msg;
			for (int i = 0; i < vmnum; i++) {
				Msg.Format(" %d", i + 1);
				msgbox.ReplaceSel(Msg);
				XSleep(stime);
			}
			msgbox.ReplaceSel("\r\n�����ı�!");
			CString title;
			file.Open(idpath + "\\title", CFile::modeRead);
			while (file.ReadString(strLine))
			{
				strLine.Trim();
				title += strLine;
			}
			file.Close();
			ANSItoUTF8(title);
			adb_acction(" shell am broadcast -a ADB_INPUT_TEXT --es msg  " + title, 1000);
			msgbox.ReplaceSel("\r\n�������!");
			adb_acction(" shell input tap 321 50", 2000);
			//���ģ����ͼƬFor���
			msgbox.ReplaceSel("\r\n����ͼƬ!");
			adb_acction(" shell rm \"/sdcard/tencent/MicroMsg/WeiXin/*\"", 1000);
			adb_acction(" shell pm clear com.android.providers.media", 1000);
			//END����
			XSleep(5000);
		}
	}
	last.Close();
	msgbox.ReplaceSel("\r\n�������!");
	enableall();
	msgbox.EnableWindow(TRUE);
	m_postunit.EnableWindow(TRUE);
}

void CMBToolsDlg::OnBnClickedButton7()
{
	//��ʼ��ģ����
	disableall();
	msgbox.SetWindowText("");
	msgbox.ReplaceSel("���ڽ���:");
	adb_acction(" shell rm \"/sdcard/tencent/MicroMsg/WeiXin/*\"", 500);
	adb_acction(" shell pm clear com.android.providers.media", 500);
	adb_acction(" push D:\\PutPicSH /sdcard/MBTools/putpic", 500);
	adb_acction(" push D:\\AddFirSH /sdcard/MBTools/addfir", 500);
	adb_acction(" push D:\\DelPicSH /sdcard/MBTools/delpic", 500);
	msgbox.ReplaceSel("\r\n��ʼ�����!");
	enableall();
}


void CMBToolsDlg::OnBnClickedButton11()
{
	//������������
	CString Text;
	CString cmd;
	CString acction = " shell am broadcast -a ADB_INPUT_TEXT --es msg ";

	GetDlgItemText(IDC_EDIT1, Text);
	ANSItoUTF8(Text);
	acction += Text;
	for (int i = 0; i < vmnum; i++) {
		cmd = " -s " + vmlist[i] + acction;
		ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
		XSleep(250);
		//cmd = " -s " + vmlist[i] + " shell input keyevent 66";
		cmd = " -s " + vmlist[i] + " shell input tap 330 410";
		ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
	}
	msgbox.SetWindowText("");
	UpdateData(false);
	GetDlgItem(IDC_EDIT1)->SetFocus();
}


void CMBToolsDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//GetDlgItemText(IDC_COMBO1, Text);
	//msgbox.SetWindowText(Text);
	//UpdateData(false);
	//GetDlgItem(IDC_EDIT1)->SetFocus();
}


void CMBToolsDlg::OnBnClickedButton12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	msgbox.SetWindowText("");
	UpdateData(false);
	GetDlgItem(IDC_EDIT1)->SetFocus();
}


void CMBToolsDlg::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		msg.Format(" %d", i + 1);
		msgbox.ReplaceSel(msg);
		cmd = " -s " + vmlist[i] + " " + acction;
		//AfxMessageBox(cmd);
		ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
		XSleep(sleeptime);
	}
}
