// SelfChatDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//ADD
#include "ClientSocket.h"
#include "Pchat.h"
//ADD


// CSelfChatDlg 对话框
class CSelfChatDlg : public CDialog
{
// 构造
public:
//ADD
	CClientSocket *m_pSocket;
	void UpdateUser();                //更新用户列表
	BOOL GetMsgFromRoom();            //接收聊天室数据 
	~CSelfChatDlg();
//ADD
	CSelfChatDlg(CWnd* pParent = NULL);	// 标准构造函数
	
// 对话框数据
	enum { IDD = IDD_SELFCHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;                //用户名
	CIPAddressCtrl ServerIP;          //IP地址控件
	CListBox m_UserList;              //用户列表控件
	CEdit m_MessageList;              //编辑框控件（消息列表）
	CString m_strMessage;             //m_MessageList关联变量
	afx_msg void OnEnter();           //进入按钮消息响应按钮（连接服务器）
	CEdit m_port;                     //编辑框 控件（端口）
	CString strport;                  //ServerPort关联变量
	afx_msg void OnQuit();            //离开按钮消息响应函数（断开连接）
	afx_msg void OnSend();            //发送消息按钮响应函数
	CEdit m_EditWords;                //编辑框控件（消息发送）
	CEdit m_Usr;                      //编辑框控件（用户名）
	CButton m_Enter;                  //进入按钮（连接）
	CButton m_Quit;                   //离开按钮（断开连接）
	CButton m_Send;                   //发送消息按钮
	CButton m_Refresh;                //刷新按钮
	CButton m_Exit;                   //退出按钮
	afx_msg void OnRefresh();         //刷新按钮响应函数
	afx_msg void OnBnClickedButton5();    //关于对话框弹出按钮响应函数 
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
