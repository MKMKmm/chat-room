// Pchat.cpp : 实现文件
//

#include "stdafx.h"
#include "SelfChat.h"
#include "Pchat.h"
#include "afxdialogex.h"
#include "SelfChatDlg.h"

#include "tagHeader.h"
// Pchat 对话框

IMPLEMENT_DYNAMIC(Pchat, CDialogEx)

Pchat::Pchat(CWnd* pParent /*=NULL*/)
	: CDialog(Pchat::IDD, pParent)
	, m_strMessage(_T(""))
{
	
}
void Pchat::GetDlg(CSelfChatDlg *dlg){
  m_dlg=dlg;
}

Pchat::~Pchat()
{

}

void Pchat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON2, m_MessageList);
	//  DDX_Control(pDX, IDC_EDIT2, m_MessageList);
	DDX_Text(pDX, IDC_EDIT2, m_strMessage);
	//  DDX_Control(pDX, IDC_LIST1, m_MessageList);
	DDX_Control(pDX, IDC_EDIT2, m_EditWords);
	DDX_Control(pDX, IDC_EDIT1, m_MessageList);
}


BEGIN_MESSAGE_MAP(Pchat, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &Pchat::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &Pchat::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &Pchat::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Pchat 消息处理程序




void Pchat::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_MessageList.SetWindowTextA("");
}


void Pchat::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

bool Pchat::GetMsgFromRoom()
{
     char buff[1000];
	memset(buff,0,sizeof(buff));
	m_dlg->m_pSocket->Receive(buff, sizeof(buff));
	m_dlg->m_pSocket->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
	
	CString strTemp = buff;
	strTemp += "\r\n";
	m_MessageList.ReplaceSel(strTemp);
	return TRUE;
}

void Pchat::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码 
	UpdateData();
	if(m_strMessage == "")
	{
		AfxMessageBox("不能发送空消息!");
		m_EditWords.SetFocus();
		return;
	}
	Header head;
	head.type = SEND_MESSAGE;
	head.len = m_strMessage.GetLength();
	head.flag=1;
	m_dlg->m_pSocket->Send((char *)&head,sizeof(Header));

	CTime time = CTime::GetCurrentTime();
	CString t = time.Format("%H:%M:%S");
	CString nikeName = m_dlg->m_strName;
    CString strTemp = t + "  " + nikeName + " 说: " + m_strMessage + "\r\n";
	CString str = nikeName + "   " + t + "\r\n" + "  " + m_strMessage+"\r\n";
	m_MessageList.ReplaceSel(str);

	if(m_dlg->m_pSocket->Send(m_strMessage,m_strMessage.GetLength()))
	{
	    m_strMessage = "";
		UpdateData(FALSE);
		m_EditWords.SetFocus();
		return;
		
	}
	else
	{
		AfxMessageBox("网络传输错误！");		
	}

}


HBRUSH Pchat::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brush;
}


BOOL Pchat::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_brush.CreateSolidBrush(RGB(253,245,230));
	// TODO:  在此添加额外的初始化
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
    SetLayeredWindowAttributes(0,200,LWA_ALPHA);

	  return TRUE; // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
