#pragma once

#ifndef _HTTP_H_
#define _HTTP_H_

#include <afxinet.h>
#include <windows.h>  
#include <string>  
using namespace std;

BOOL Download(const CString& strFileURLInServer,	//�������ļ���URL
	const CString & strFileLocalFullPath);			//��ŵ����ص�·��

#endif // _HTTP_H_
