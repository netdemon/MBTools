#include "stdafx.h"

/*
int i = GetTempPath(MAX_PATH - 1, sztempdirectory);
if (sztempdirectory[i - 1] != '\\')
{
lstrcat(sztempdirectory, "\\");
}
lstrcat(sztempdirectory, "dh\\");
*/

/*
//��ȡ�������ı�����
std_string GetClipBoardText(HWND hWnd)
{
ASSERT(hWnd);
std_string ClipBoardText;
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
*/






/*
//#define EXECDOSCMD "dir /?" //���Ի����������
SECURITY_ATTRIBUTES sa;
HANDLE hRead, hWrite;
sa.nLength = sizeof(SECURITY_ATTRIBUTES);
sa.lpSecurityDescriptor = NULL;
sa.bInheritHandle = TRUE;
if (!CreatePipe(&hRead, &hWrite, &sa, 0))
{
return FALSE;
}
//char command[1024];    //����1K�������У������˰�
//strcpy(command, "Cmd.exe /C ");
//strcat(command, EXECDOSCMD);
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
//CStringArray mv;
//mv.SetSize(0, 1);
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

//AfxMessageBox(bf);   //�����ǵ����Ի�����ʾ
//msgbox.ReplaceSel(bf);
//UpdateData(false);
//Sleep(200);

/////////////////////////////////////////////////////////////////////////////////////

CStdioFile file_r, file_w;
file_w.Open(_T("D:\\vmlist"), CFile::modeCreate | CFile::modeReadWrite);//����ļ����Ȳ����ڵĻ�������ҪCFile::modeCreate������Ͳ���Ҫ��
file_w.WriteString(bf);
file_w.Close();
Sleep(200);

file_r.Open(_T("D:\\1.txt"), CFile::modeRead);
//file_r.Open(_T("D:\\vmlist"), CFile::modeRead);
//���ж�ȡ�ļ�
CString   strLine;
vmnum = 0;
while (file_r.ReadString(strLine))   // //��ÿ�ж��Ž�strLine�ַ�����
{
CString bf = strLine.Left(15);
if (bf.Find(_T("127.0.0.1")) != -1)
{
vmlist.Add(bf);
}
//AfxMessageBox(bf);  //ִ������
//Sleep(100);
}
file_r.Close();

*/