
// ChatClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChatClientApp:
// �йش����ʵ�֣������ ChatClient.cpp
//
#define WM_SOCKET	WM_USER+100
class CChatClientApp : public CWinApp
{
public:
	CChatClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChatClientApp theApp;