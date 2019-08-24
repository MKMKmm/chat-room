//ADD
#include "SelfRoomDlg.h"
//ADD
#pragma once

// CClientSocket 命令目标

class CClientSocket : public CSocket
{
//ADD
public:
	CPtrList *clist;                   //其它客户端套接字链表
	CSelfRoomDlg *m_dlgServer;   
//ADD
public:
	CClientSocket();
//ADD
	CClientSocket(CPtrList *list);
//ADD
	virtual ~CClientSocket();
//ADD
public:
	CString m_strName;                          //昵称
//ADD
//	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);        //关闭套接字
	virtual void OnReceive(int nErrorCode);      //接收数据
};


