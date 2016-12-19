#pragma once

#ifndef _HTTP_H_
#define _HTTP_H_

#include <afxinet.h>
#include <windows.h>  
#include <string>  
using namespace std;

typedef struct FileInfo
{
	DWORD  nFileLen;
	DWORD  nFileHighLen;
	LPSTR FileBuf;
}FileInfo, *pFileInfo;

BOOL Download(const CString& strFileURLInServer,	//�������ļ���URL
	const CString & strFileLocalFullPath);			//��ŵ����ص�·��

#endif // _HTTP_H_
