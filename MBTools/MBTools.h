
// MBTools.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#define HOST	_T("http://mbt.20cn.com")
#define POST	_T("/cgi-bin/u.pl")
#define DOWN	_T("/cgi-bin/d.pl")
#define ADB		_T("D:\\Program Files\\Microvirt\\MEmu\\adb.exe")
#define CURL	_T("D:\\curl.exe")
#define MYPATH	_T("D:\\MBTools\\")

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
