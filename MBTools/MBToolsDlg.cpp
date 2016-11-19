
// MBToolsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MBTools.h"
#include "MBToolsDlg.h"
#include "afxdialogex.h"

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
	SetDlgItemText(IDC_BUTTON2, _T("�Զ�������Ȧ"));
	SetDlgItemText(IDC_BUTTON4, _T("�Զ���Ӻ���"));
	SetDlgItemText(IDC_BUTTON8, _T("�������ͼƬ"));
	SetDlgItemText(IDC_BUTTON9, _T("TEST"));

	vmnum = getVMlist();
	vmNum.Format(_T("%d"), vmnum);
	vmNum = "��ǰģ����������" + vmNum;
	SetDlgItemText(IDC_STATIC, vmNum);


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
	theApp.GetMainWnd()->ShowWindow(SW_MINIMIZE);//��С������
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
		//AfxMessageBox("���Ų�����ʼ");
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		SetDlgItemText(IDC_BUTTON1, "������...");

		if (vmnum == 0) {
			AfxMessageBox("���ش���");
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
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);  //DEL
			ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
			Sleep(100);
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);

		}

		//���ƺ���
		msgbox.ReplaceSel("\r\n���ƺ���:");
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

		//�������
		msgbox.ReplaceSel("\r\n�������:");
		for (int i = 0; i < vmnum; i++) {
			acction = " shell am start -t \"text/x-vcard\" -d \"file:///sdcard/contacts.vcf\" -a android.intent.action.VIEW com.android.contacts";
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
			Sleep(100);
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
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
		//AfxMessageBox("OK");
		//�����Ѵ�΢��ͼƬ������  adb pull /sdcard/tencent/MicroMsg/WeiXin D:\\pic
		SetDlgItemText(IDC_BUTTON2, "�ȴ��༭����");
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		edited = 0;

		if (vmnum == 0) {
			AfxMessageBox("���ش���");
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
		msgbox.ReplaceSel("������ͼ:");
		for (int i = 0; i < vmnum; i++) {
			cmd = a + vmlist[i] + acction;
			//AfxMessageBox(cmd);
			ShellExecute(NULL, "open", adb, cmd, "", SW_HIDE);
			Sleep(100);
			Msg.Format(" %d", i + 1);
			msgbox.ReplaceSel(Msg);
		}
		//msgbox.ReplaceSel("\r\n�������!");

		acction = " push D:\\pic /sdcard/tencent/MicroMsg/WeiXin";
		msgbox.ReplaceSel("\r\n������ͼ:");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vmnum = getVMlist();
	vmNum.Format(_T("%d"), vmnum);
	vmNum = "��ǰģ����������" + vmNum;
	SetDlgItemText(IDC_STATIC, vmNum);
}


void CMBToolsDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);


	if (vmnum == 0) {
		AfxMessageBox("���ش���");
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
	msgbox.ReplaceSel("��������:");
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
	if (!CreateProcess(NULL, "D:\\Program Files\\Microvirt\\MEmu\\adb.exe devices", NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return FALSE;
	}
	CloseHandle(hWrite);
	char buffer[65536] = { 0 };       //��4K�Ŀռ����洢��������ݣ�ֻҪ������ʾ�ļ����ݣ�һ��������ǹ����ˡ�  
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
	file_w.Open(_T("D:\\vmlist"), CFile::modeCreate | CFile::modeReadWrite);//����ļ����Ȳ����ڵĻ�������ҪCFile::modeCreate������Ͳ���Ҫ��
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
	CString ClipBoardText;
	HWND hWnd = GetSafeHwnd();
	ClipBoardText = GetClipBoardText(hWnd);
	AfxMessageBox(ClipBoardText);

}
