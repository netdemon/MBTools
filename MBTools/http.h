#pragma once

#ifndef _HTTP_H_
#define _HTTP_H_

#include <afxinet.h>
#include <windows.h>  
#include <string>  
using namespace std;

BOOL Download(const CString& strFileURLInServer,	//待下载文件的URL
	const CString & strFileLocalFullPath);			//存放到本地的路径

#endif // _HTTP_H_
