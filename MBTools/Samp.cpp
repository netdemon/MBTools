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
//获取剪贴板文本内容
std_string GetClipBoardText(HWND hWnd)
{
ASSERT(hWnd);
std_string ClipBoardText;
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
//char command[1024];    //长达1K的命令行，够用了吧
//strcpy(command, "Cmd.exe /C ");
//strcat(command, EXECDOSCMD);
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
//CStringArray mv;
//mv.SetSize(0, 1);
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

/////////////////////////////////////////////////////////////////////////////////////

CStdioFile file_r, file_w;
file_w.Open(_T("D:\\vmlist"), CFile::modeCreate | CFile::modeReadWrite);//如果文件事先不存在的话，就需要CFile::modeCreate，否则就不需要。
file_w.WriteString(bf);
file_w.Close();
Sleep(200);

file_r.Open(_T("D:\\1.txt"), CFile::modeRead);
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

*/