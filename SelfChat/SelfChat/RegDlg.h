#pragma once


// CRegDlg �Ի���

class CRegDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegDlg)

public:
	CRegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CBrush m_brush;
	DECLARE_MESSAGE_MAP()
public:
	CString m_Sign_Account;
	CString m_Sign_Pass;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
