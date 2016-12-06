#pragma once


#ifndef _HTTP_H_
#define _HTTP_H_

#include <afxinet.h>
#include <windows.h>  
#include <string>  
using namespace std;

//#include <stdlib.h>  
//#include <TCHAR.H>  
//#include <Wininet.h>  


typedef struct FileInfo
{
	DWORD  nFileLen;
	DWORD  nFileHighLen;
	LPSTR FileBuf;
}FileInfo, *pFileInfo;

BOOL Download(const CString& strFileURLInServer, //待下载文件的URL
	const CString & strFileLocalFullPath);//存放到本地的路径
BOOL UploadFile(LPCTSTR strURL, //负责接收上传操作的页面的URL
	LPCTSTR strLocalFileName);  //待上传的本地文件路径

BOOL Upload(string& FilePath, string& ServerName, string& ObjectName, string& HTTPBoundary, INTERNET_PORT &nPort);
#endif // _HTTP_H_
