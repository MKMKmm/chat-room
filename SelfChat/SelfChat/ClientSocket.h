#pragma once

// CClientSocket 命令目标
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
	CString m_strName;                //用户名
	void GetDlg(CSelfChatDlg *dlg);
//ADD
	virtual void OnReceive(int nErrorCode);   //接收数据

	Pchat *m_Pchat;
};


