
// MBTools.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#define HOST	"http://mbt.20cn.com"
#define POST	"/cgi-bin/u.pl"
#define DOWN	"/cgi-bin/d.pl"
#define ADB		"D:\\Program Files\\Microvirt\\MEmu\\adb.exe"
#define CURL	"D:\\curl.exe"
#define MYPATH	"D:\\MBTools\\"

// CMBToolsApp: 
// �йش����ʵ�֣������ MBTools.cpp
//

class CMBToolsApp : public CWinApp
{
public:
	CMBToolsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMBToolsApp theApp;
