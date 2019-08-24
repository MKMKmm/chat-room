// SelfRoomDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//ADD
class CServerSocket;
class CClientSocket;
//ADD
// CSelfRoomDlg �Ի���
class CSelfRoomDlg : public CDialog
{
// ����
public:
	CSelfRoomDlg(CWnd* pParent = NULL);	// ��׼���캯��
//ADD
	CServerSocket *m_pSocket;                         //�������׽���
	CClientSocket *clientSocket;                      //�ͻ����׽���
	void UpdateUser(CClientSocket *pSocket);          //�����û��б�
//ADD

// �Ի�������
	enum { IDD = IDD_SELFROOM_DIALOG };

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
	CString m_strName;              //�ǳ�
	CListBox m_UserList;            //�û��б�ؼ�
	CIPAddressCtrl ServerIP;        //IP��ַ�ؼ�
	CEdit ServerPort;               //�༭��ؼ����˿ڣ�
	CString sPort;                  //ServerPort��������
	CString m_history;              //��ʷ��Ϣ����
	afx_msg void OnStart();         //��ʼ������ť��Ϣ��Ӧ����
	CEdit m_MessageList;            //�༭��ؼ�����Ϣ�б�
	afx_msg void OnStop();          //ֹͣ������ť��Ϣ��Ӧ����
	CEdit m_Admin;                  //�༭��ؼ�������Ա�ǳƣ�
	CButton m_Start;                //��ʼ������ť
	CButton m_Stop;                 //ֹͣ������ť
	CButton m_Exit;                 //�˳���ť
	afx_msg void OnBnClickedButton3();     //���ڶԻ��򵯳���ť��Ӧ���� 
	afx_msg void OnBnClickedCancel();
	CString m_send;
	afx_msg void OnBnClickedButton5();
	CEdit m_EditWords;
};
