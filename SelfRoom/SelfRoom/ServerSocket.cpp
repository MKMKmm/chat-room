// ServerSocket.cpp : ʵ���ļ�
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


// CServerSocket ��Ա����

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
//ADD
	CClientSocket *clientSocket = new CClientSocket(&connectList);
	Accept(*clientSocket);
	//clientSocket->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	clientSocket->m_dlgServer = (CSelfRoomDlg *)::AfxGetMainWnd();

	connectList.AddTail(clientSocket);
//ADD

	CSocket::OnAccept(nErrorCode);
}
