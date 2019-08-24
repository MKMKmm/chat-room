#pragma once

// CServerSocket 命令目标

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
//ADD
	CPtrList connectList;                     //客户端套接字链表
//ADD
	virtual void OnAccept(int nErrorCode);    //接收客户端连接
};


