#pragma once

// CClientSocket ����Ŀ��
//ADD
#include "Pchat.h"
class CSelfChatDlg;
//ADD

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
//ADD
	CSelfChatDlg *chatDlg;
	CString m_strName;                //�û���
	void GetDlg(CSelfChatDlg *dlg);
//ADD
	virtual void OnReceive(int nErrorCode);   //��������

	Pchat *m_Pchat;
};


