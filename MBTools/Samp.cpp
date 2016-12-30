#include "stdafx.h"

/*

//ANSI转UTF8
void ANSItoUTF8(CString &strAnsi)
{
//获取转换为宽字节后需要的缓冲区大小，创建宽字节缓冲区，936为简体中文GB2312代码页
UINT nLen = MultiByteToWideChar(936,NULL,strAnsi,-1,NULL,NULL);
WCHAR *wszBuffer = new WCHAR[nLen+1];
nLen = MultiByteToWideChar(936,NULL,strAnsi,-1,wszBuffer,nLen);
wszBuffer[nLen] = 0;
//获取转为UTF8多字节后需要的缓冲区大小，创建多字节缓冲区
nLen = WideCharToMultiByte(CP_UTF8,NULL,wszBuffer,-1,NULL,NULL,NULL,NULL);
CHAR *szBuffer = new CHAR[nLen+1];
nLen = WideCharToMultiByte(CP_UTF8,NULL,wszBuffer,-1,szBuffer,nLen,NULL,NULL);
szBuffer[nLen] = 0;

strAnsi = szBuffer;
//内存清理
delete []wszBuffer;
delete []szBuffer;
}


//UTF8转ANSI
void UTF8toANSI(CString &strUTF8)
{
//获取转换为多字节后需要的缓冲区大小，创建多字节缓冲区
UINT nLen = MultiByteToWideChar(CP_UTF8,NULL,strUTF8,-1,NULL,NULL);
WCHAR *wszBuffer = new WCHAR[nLen+1];
nLen = MultiByteToWideChar(CP_UTF8,NULL,strUTF8,-1,wszBuffer,nLen);
wszBuffer[nLen] = 0;

nLen = WideCharToMultiByte(936,NULL,wszBuffer,-1,NULL,NULL,NULL,NULL);
CHAR *szBuffer = new CHAR[nLen+1];
nLen = WideCharToMultiByte(936,NULL,wszBuffer,-1,szBuffer,nLen,NULL,NULL);
szBuffer[nLen] = 0;

strUTF8 = szBuffer;
//清理内存
delete []szBuffer;
delete []wszBuffer;
}



//
unicode的环境下，写中文到文件，会出现乱码。

解决方法下面两个函数。

EncodeToUTF8  写入的时候调用

UTF8ToEncode 读取的时候调用

MultiByteToWideChar WideCharToMultiByte 实现原理就是这两个函数。 不知到哪位仁兄写的。

char* EncodeToUTF8(const char* mbcsStr)
{
wchar_t*  wideStr;
char*   utf8Str;
int   charLen;

charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
wideStr = (wchar_t*) malloc(sizeof(wchar_t)*charLen);
MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen);

charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);

utf8Str = (char*) malloc(charLen);

WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);

free(wideStr);
return utf8Str;

}
char* UTF8ToEncode(const char* mbcsStr)
{
wchar_t*  wideStr;
char*   unicodeStr;
int   charLen;

charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
wideStr = (wchar_t*) malloc(sizeof(wchar_t)*charLen);
MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, wideStr, charLen);

charLen =WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
unicodeStr = (char*)malloc(charLen);
WideCharToMultiByte(CP_ACP, 0, wideStr, -1, unicodeStr, charLen, NULL, NULL);

free(wideStr);
return unicodeStr;
}



int i = GetTempPath(MAX_PATH - 1, sztempdirectory);
if (sztempdirectory[i - 1] != '\\')
{
lstrcat(sztempdirectory, "\\");
}
lstrcat(sztempdirectory, "dh\\");



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



if (!PathFileExists(path)) {
CreateDirectory("D:\\pic", NULL);
}
else {
CFileFind file;
BOOL res = file.FindFile(path + "\\*.*");
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
}
DeleteFile("D:\\piclist");
Download(picurl + "list", "D:\\piclist");
DeleteFile("D:\\title");
Download(picurl + "title", "D:\\title");



CStdioFile file;
CString strLine;
CString title;

//发送图片到模拟器
CString a = " -s ";
CString acction = " push D:\\pic /sdcard/tencent/MicroMsg/WeiXin";
CString cmd;
CString Msg;

msgbox.ReplaceSel("\r\n正在上图:");
for (int i = 0; i < vmnum; i++) {
Msg.Format(" %d", i + 1);
msgbox.ReplaceSel(Msg);
cmd = a + vmlist[i] + acction;
//AfxMessageBox(cmd);
ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
XSleep(500);
}
acction = " shell am broadcast -a android.intent.action.MEDIA_MOUNTED -d file:///sdcard/";
for (int i = 0; i < vmnum; i++) {
cmd = a + vmlist[i] + acction;
//AfxMessageBox(cmd);
ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
XSleep(500);
}

//发送脚本到模拟器
acction = " push D:\\PutPicSH /sdcard/MBTools/putpic";
msgbox.ReplaceSel("\r\n生成指令:");
for (int i = 0; i < vmnum; i++) {
Msg.Format(" %d", i + 1);
msgbox.ReplaceSel(Msg);
cmd = a + vmlist[i] + acction;
//AfxMessageBox(cmd);
ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
XSleep(500);
}

msgbox.ReplaceSel("\r\n发送指令:");
acction = " shell /sdcard/MBTools/putpic";
for (int i = 0; i < vmnum; i++) {
Msg.Format(" %d", i + 1);
msgbox.ReplaceSel(Msg);
cmd = a + vmlist[i] + acction;
//AfxMessageBox(cmd);
ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
XSleep(1000);
}

msgbox.ReplaceSel("\r\n等待点击:");
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

msgbox.ReplaceSel("\r\n发送文本!");
acction = " shell am broadcast -a ADB_INPUT_TEXT --es msg ";
ANSItoUTF8(title);
acction += title;
for (int i = 0; i < vmnum; i++) {
Msg.Format(" %d", i + 1);
msgbox.ReplaceSel(Msg);
cmd = a + vmlist[i] + acction;
//AfxMessageBox(cmd);
ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
XSleep(1000);
}
msgbox.ReplaceSel("\r\n点击发送!");
acction = " shell input tap 321 50";
for (int i = 0; i < vmnum; i++) {
Msg.Format(" %d", i + 1);
msgbox.ReplaceSel(Msg);
cmd = a + vmlist[i] + acction;
//AfxMessageBox(cmd);
ShellExecute(NULL, "open", ADB, cmd, "", SW_HIDE);
XSleep(2000);
}

msgbox.ReplaceSel("\r\n操作完成!");


* 将一个字符的Unicode(UCS-2和UCS-4)编码转换成UTF-8编码.
*
* 参数:
*    unic     字符的Unicode编码值
*    pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
*    outsize  pOutput缓冲的大小
*
* 返回值:
*    返回转换后的字符的UTF8编码所占的字节数, 如果出错则返回 0 .
*
* 注意:
*     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
*        字节序分为大端(Big Endian)和小端(Little Endian)两种;
*        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
*     2. 请保证 pOutput 缓冲区有最少有 6 字节的空间大小!

int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,
	int outSize)
{
	assert(pOutput != NULL);
	assert(outSize >= 6);

	if (unic <= 0x0000007F)
	{
		// * U-00000000 - U-0000007F:  0xxxxxxx
		*pOutput = (unic & 0x7F);
		return 1;
	}
	else if (unic >= 0x00000080 && unic <= 0x000007FF)
	{
		// * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
		*(pOutput + 1) = (unic & 0x3F) | 0x80;
		*pOutput = ((unic >> 6) & 0x1F) | 0xC0;
		return 2;
	}
	else if (unic >= 0x00000800 && unic <= 0x0000FFFF)
	{
		// * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
		*(pOutput + 2) = (unic & 0x3F) | 0x80;
		*(pOutput + 1) = ((unic >> 6) & 0x3F) | 0x80;
		*pOutput = ((unic >> 12) & 0x0F) | 0xE0;
		return 3;
	}
	else if (unic >= 0x00010000 && unic <= 0x001FFFFF)
	{
		// * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		*(pOutput + 3) = (unic & 0x3F) | 0x80;
		*(pOutput + 2) = ((unic >> 6) & 0x3F) | 0x80;
		*(pOutput + 1) = ((unic >> 12) & 0x3F) | 0x80;
		*pOutput = ((unic >> 18) & 0x07) | 0xF0;
		return 4;
	}
	else if (unic >= 0x00200000 && unic <= 0x03FFFFFF)
	{
		// * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		*(pOutput + 4) = (unic & 0x3F) | 0x80;
		*(pOutput + 3) = ((unic >> 6) & 0x3F) | 0x80;
		*(pOutput + 2) = ((unic >> 12) & 0x3F) | 0x80;
		*(pOutput + 1) = ((unic >> 18) & 0x3F) | 0x80;
		*pOutput = ((unic >> 24) & 0x03) | 0xF8;
		return 5;
	}
	else if (unic >= 0x04000000 && unic <= 0x7FFFFFFF)
	{
		// * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		*(pOutput + 5) = (unic & 0x3F) | 0x80;
		*(pOutput + 4) = ((unic >> 6) & 0x3F) | 0x80;
		*(pOutput + 3) = ((unic >> 12) & 0x3F) | 0x80;
		*(pOutput + 2) = ((unic >> 18) & 0x3F) | 0x80;
		*(pOutput + 1) = ((unic >> 24) & 0x3F) | 0x80;
		*pOutput = ((unic >> 30) & 0x01) | 0xFC;
		return 6;
	}

	return 0;
}


* 将一个字符的UTF8编码转换成Unicode(UCS-2和UCS-4)编码.
*
* 参数:
*    pInput      指向输入缓冲区, 以UTF-8编码
*    Unic        指向输出缓冲区, 其保存的数据即是Unicode编码值,
*                类型为unsigned long .
*
* 返回值:
*    成功则返回该字符的UTF8编码所占用的字节数; 失败则返回0.
*
* 注意:
*     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
*        字节序分为大端(Big Endian)和小端(Little Endian)两种;
*        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)

int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
	assert(pInput != NULL && Unic != NULL);

	// b1 表示UTF-8编码的pInput中的高字节, b2 表示次高字节, ...
	char b1, b2, b3, b4, b5, b6;

	*Unic = 0x0; // 把 *Unic 初始化为全零
	int utfbytes = enc_get_utf8_size(pInput);
	unsigned char *pOutput = (unsigned char *)Unic;

	switch (utfbytes)
	{
	case 0:
		*pOutput = *pInput;
		utfbytes += 1;
		break;
	case 2:
		b1 = *pInput;
		b2 = *(pInput + 1);
		if ((b2 & 0xE0) != 0x80)
			return 0;
		*pOutput = (b1 << 6) + (b2 & 0x3F);
		*(pOutput + 1) = (b1 >> 2) & 0x07;
		break;
	case 3:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b2 << 6) + (b3 & 0x3F);
		*(pOutput + 1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
		break;
	case 4:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		b4 = *(pInput + 3);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
			|| ((b4 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b3 << 6) + (b4 & 0x3F);
		*(pOutput + 1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
		*(pOutput + 2) = ((b1 << 2) & 0x1C) + ((b2 >> 4) & 0x03);
		break;
	case 5:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		b4 = *(pInput + 3);
		b5 = *(pInput + 4);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
			|| ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b4 << 6) + (b5 & 0x3F);
		*(pOutput + 1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
		*(pOutput + 2) = (b2 << 2) + ((b3 >> 4) & 0x03);
		*(pOutput + 3) = (b1 << 6);
		break;
	case 6:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		b4 = *(pInput + 3);
		b5 = *(pInput + 4);
		b6 = *(pInput + 5);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
			|| ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
			|| ((b6 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b5 << 6) + (b6 & 0x3F);
		*(pOutput + 1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
		*(pOutput + 2) = (b3 << 2) + ((b4 >> 4) & 0x03);
		*(pOutput + 3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
		break;
	default:
		return 0;
		break;
	}

	return utfbytes;
}

int enc_get_utf8_size(const unsigned char* pInput)
{
	int i = 0, ret = 0;

	if (NULL == pInput)
		return 0;
	for (i = 0; i<8; i++)
	{
		if (((*pInput)&(0x80 >> i)))
			ret++;
		else
			break;
	}
	return ret;
}








*/



