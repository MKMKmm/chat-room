#pragma once

// CServerSocket ����Ŀ��

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
//ADD
	CPtrList connectList;                     //�ͻ����׽�������
//ADD
	virtual void OnAccept(int nErrorCode);    //���տͻ�������
};


