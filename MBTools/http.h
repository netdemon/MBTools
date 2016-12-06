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

BOOL Download(const CString& strFileURLInServer, //�������ļ���URL
	const CString & strFileLocalFullPath);//��ŵ����ص�·��
BOOL UploadFile(LPCTSTR strURL, //��������ϴ�������ҳ���URL
	LPCTSTR strLocalFileName);  //���ϴ��ı����ļ�·��

BOOL Upload(string& FilePath, string& ServerName, string& ObjectName, string& HTTPBoundary, INTERNET_PORT &nPort);
#endif // _HTTP_H_
