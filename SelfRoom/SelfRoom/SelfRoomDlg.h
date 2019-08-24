// SelfRoomDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//ADD
class CServerSocket;
class CClientSocket;
//ADD
// CSelfRoomDlg 对话框
class CSelfRoomDlg : public CDialog
{
// 构造
public:
	CSelfRoomDlg(CWnd* pParent = NULL);	// 标准构造函数
//ADD
	CServerSocket *m_pSocket;                         //服务器套接字
	CClientSocket *clientSocket;                      //客户端套接字
	void UpdateUser(CClientSocket *pSocket);          //更新用户列表
//ADD

// 对话框数据
	enum { IDD = IDD_SELFROOM_DIALOG };

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
	CString m_strName;              //昵称
	CListBox m_UserList;            //用户列表控件
	CIPAddressCtrl ServerIP;        //IP地址控件
	CEdit ServerPort;               //编辑框控件（端口）
	CString sPort;                  //ServerPort关联变量
	CString m_history;              //历史消息数据
	afx_msg void OnStart();         //开始监听按钮消息响应函数
	CEdit m_MessageList;            //编辑框控件（消息列表）
	afx_msg void OnStop();          //停止监听按钮消息响应函数
	CEdit m_Admin;                  //编辑框控件（管理员昵称）
	CButton m_Start;                //开始监听按钮
	CButton m_Stop;                 //停止监听按钮
	CButton m_Exit;                 //退出按钮
	afx_msg void OnBnClickedButton3();     //关于对话框弹出按钮响应函数 
	afx_msg void OnBnClickedCancel();
	CString m_send;
	afx_msg void OnBnClickedButton5();
	CEdit m_EditWords;
};
