
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
#define ADB		_T("D:\\ADB\\adb.exe")
#define CURL	_T("D:\\curl.exe")
#define MYPATH	_T("D:\\MBTools\\")
#define TIMERAF	1
#define TIMERPP 2
#define TIMERRR 3
#define AFTIME	60*60000
#define PPTIME	40*60000
#define RRTIME	28*60000



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
