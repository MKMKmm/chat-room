// SelfChat.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSelfChatApp:
// �йش����ʵ�֣������ SelfChat.cpp
//

class CSelfChatApp : public CWinApp
{
public:
//ADD
	CString m_strName;
//ADD
	CSelfChatApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSelfChatApp theApp;