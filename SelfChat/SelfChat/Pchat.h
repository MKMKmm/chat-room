#pragma once
#include "afxwin.h"

class CSelfChatDlg;
// Pchat 对话框

class Pchat : public CDialog
{
	DECLARE_DYNAMIC(Pchat)

public:
	Pchat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Pchat();
	CSelfChatDlg *m_dlg;
	void GetDlg(CSelfChatDlg * dlg);
// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CBrush m_brush;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
//	CButton m_MessageList;
//	CEdit m_MessageList;
	CString m_strMessage;
//	CListBox m_MessageList;
	CEdit m_EditWords;
	bool GetMsgFromRoom();
	CEdit m_MessageList;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
