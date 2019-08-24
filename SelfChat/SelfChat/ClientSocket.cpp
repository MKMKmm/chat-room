// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SelfChat.h"
#include "ClientSocket.h"
//ADD
#include "SelfChatDlg.h"
#include "tagHeader.h"
//#include "Pchat.h"
//ADD


// CClientSocket

CClientSocket::CClientSocket()
{
		m_Pchat=NULL;
}

CClientSocket::~CClientSocket()
{       
	if (NULL != m_Pchat)   
    {   
        // 删除非模态对话框对象   
        delete m_Pchat;   
    }   
}


// CClientSocket 成员函数

void CClientSocket::GetDlg(CSelfChatDlg *dlg)            //获得窗口界面的指针
{
	    chatDlg = dlg;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
//ADD
	char buff[sizeof(Header)];
	memset(buff,0,sizeof(buff));
	Receive(buff,sizeof(buff));
	this->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);

	Header *header = (Header*)buff;
	int length = header->len;
	char type = header->type;
	int flag=header->flag;
	if(type == SEND_MESSAGE)
	{
		if(flag==0)
		{
		    chatDlg->GetMsgFromRoom();
		}
		else if(flag==1)
		{
                 //
			if (NULL == m_Pchat)   
                {   
                   // 创建非模态对话框实例   
                   m_Pchat = new Pchat();   
		           m_Pchat->GetDlg(chatDlg);
                   m_Pchat->Create(IDD_DIALOG3, chatDlg); 
					// 显示非模态对话框   
                   m_Pchat->ShowWindow(SW_SHOW);  

                 }   
			  m_Pchat->GetMsgFromRoom();
		}
	}
	if(type == LOGIN_IO)
	{
		//chatDlg->m_UserList.ResetContent();
		chatDlg->UpdateUser();		
	}
//ADD

	CSocket::OnReceive(nErrorCode);
}
