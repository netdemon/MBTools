
// MBTools.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#define HOST	_T("http://mbt.20cn.com")
#define POST	_T("/cgi-bin/u.pl")
#define DOWN	_T("/cgi-bin/d.pl")
#define ADB		_T("D:\\Program Files\\Microvirt\\MEmu\\adb.exe")
#define CURL	_T("D:\\curl.exe")
#define MYPATH	_T("D:\\MBTools\\")

// CMBToolsApp: 
// 有关此类的实现，请参阅 MBTools.cpp
//

class CMBToolsApp : public CWinApp
{
public:
	CMBToolsApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMBToolsApp theApp;
