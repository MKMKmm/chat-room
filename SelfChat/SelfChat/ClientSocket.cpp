// ClientSocket.cpp : ʵ���ļ�
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
        // ɾ����ģ̬�Ի������   
        delete m_Pchat;   
    }   
}


// CClientSocket ��Ա����

void CClientSocket::GetDlg(CSelfChatDlg *dlg)            //��ô��ڽ����ָ��
{
	    chatDlg = dlg;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
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
                   // ������ģ̬�Ի���ʵ��   
                   m_Pchat = new Pchat();   
		           m_Pchat->GetDlg(chatDlg);
                   m_Pchat->Create(IDD_DIALOG3, chatDlg); 
					// ��ʾ��ģ̬�Ի���   
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
