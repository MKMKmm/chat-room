// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SelfRoom.h"
#include "ServerSocket.h"
//ADD
#include "ClientSocket.h"
//ADD


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	CClientSocket *clientSocket = new CClientSocket(&connectList);
	Accept(*clientSocket);
	//clientSocket->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	clientSocket->m_dlgServer = (CSelfRoomDlg *)::AfxGetMainWnd();

	connectList.AddTail(clientSocket);
//ADD

	CSocket::OnAccept(nErrorCode);
}
