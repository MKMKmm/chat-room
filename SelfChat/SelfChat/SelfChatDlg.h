// SelfChatDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//ADD
#include "ClientSocket.h"
#include "Pchat.h"
//ADD


// CSelfChatDlg �Ի���
class CSelfChatDlg : public CDialog
{
// ����
public:
//ADD
	CClientSocket *m_pSocket;
	void UpdateUser();                //�����û��б�
	BOOL GetMsgFromRoom();            //�������������� 
	~CSelfChatDlg();
//ADD
	CSelfChatDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_SELFCHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;                //�û���
	CIPAddressCtrl ServerIP;          //IP��ַ�ؼ�
	CListBox m_UserList;              //�û��б�ؼ�
	CEdit m_MessageList;              //�༭��ؼ�����Ϣ�б�
	CString m_strMessage;             //m_MessageList��������
	afx_msg void OnEnter();           //���밴ť��Ϣ��Ӧ��ť�����ӷ�������
	CEdit m_port;                     //�༭�� �ؼ����˿ڣ�
	CString strport;                  //ServerPort��������
	afx_msg void OnQuit();            //�뿪��ť��Ϣ��Ӧ�������Ͽ����ӣ�
	afx_msg void OnSend();            //������Ϣ��ť��Ӧ����
	CEdit m_EditWords;                //�༭��ؼ�����Ϣ���ͣ�
	CEdit m_Usr;                      //�༭��ؼ����û�����
	CButton m_Enter;                  //���밴ť�����ӣ�
	CButton m_Quit;                   //�뿪��ť���Ͽ����ӣ�
	CButton m_Send;                   //������Ϣ��ť
	CButton m_Refresh;                //ˢ�°�ť
	CButton m_Exit;                   //�˳���ť
	afx_msg void OnRefresh();         //ˢ�°�ť��Ӧ����
	afx_msg void OnBnClickedButton5();    //���ڶԻ��򵯳���ť��Ӧ���� 
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedfilechoice();
	afx_msg void OnBnClickedplay();
	afx_msg void OnBnClickedpause();
	CSliderCtrl m_slider;
	afx_msg void OnLbnDblclkList1();
public:
	Pchat *m_Pchat;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
