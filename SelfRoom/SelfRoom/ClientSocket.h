//ADD
#include "SelfRoomDlg.h"
//ADD
#pragma once

// CClientSocket ����Ŀ��

class CClientSocket : public CSocket
{
//ADD
public:
	CPtrList *clist;                   //�����ͻ����׽�������
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
	CString m_strName;                          //�ǳ�
//ADD
//	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);        //�ر��׽���
	virtual void OnReceive(int nErrorCode);      //��������
};


