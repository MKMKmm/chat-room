// RegDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SelfChat.h"
#include "RegDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"

// CRegDlg 对话框

IMPLEMENT_DYNAMIC(CRegDlg, CDialog)

CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDlg::IDD, pParent)
	, m_Sign_Account(_T(""))
	, m_Sign_Pass(_T(""))
{

}

CRegDlg::~CRegDlg()
{
}

void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Sign_Account);
	DDX_Text(pDX, IDC_EDIT2, m_Sign_Pass);
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CRegDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRegDlg::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRegDlg 消息处理程序


void CRegDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

    CString username;//从文件中读取用户名进行校验，如果输入的用户名在文件已存在则不进行注册
    CString sex;
    bool flag=false;//标记
    char * path="username.txt";//文件路径

    CFile fp;//使用MFC的CFile将数据写入文件
    fp.Open(path,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
    fp.SeekToBegin();//移动文件指针位置至文件头

    CArchive ar(&fp,CArchive::load);//使用CArchive进行读取文件
    UpdateData();//将数据从控件复制到控件变量

    //进行左右空格清除
     m_Sign_Account.TrimLeft();
     m_Sign_Account.TrimRight();

     m_Sign_Pass.TrimLeft();
     m_Sign_Pass.TrimRight();

      //单选框选择并获取其文本
      UINT nID=GetCheckedRadioButton(IDC_RADIO_MAN,IDC_RADIO_WOMAN);
      GetDlgItemText(nID,sex);
      //校验操作
while(ar.ReadString(username)){
    username.TrimLeft();
    username.TrimRight();
    if(strcmp(username,m_Sign_Account)==0)
    {
        flag=true;//如果已存在用户名，则标记flag为true
        break;
    }else
    {
        ar.ReadString(username);//读取下一行（每一行为一个属性，比如用户名，密码，性别，总共3 个属性）
        ar.ReadString(username);//读取下一行
    }
}
ar.Close();

fp.SeekToEnd();//文件写入为追加操作，所以写入前必须将文件指针移动至文件尾

    if(!flag)
    {
        //CFile Write(*str,GetLength())写入
        fp.Write(m_Sign_Account,m_Sign_Account.GetLength());
        //win虽是\r\n，在写程序只需要\n即可换行
        fp.Write("\n",sizeof(char));
        fp.Write(m_Sign_Pass,m_Sign_Pass.GetLength());
        fp.Write("\n",sizeof(char));
        fp.Write(sex,sex.GetLength());
        fp.Write("\n",sizeof(char));
        fp.Close();
        MessageBox("注册成功");
        CDialog::OnOK();
    }
    else
    {
        MessageBox("用户已存在");//用户已存在提示框，不关闭注册框，可让用户自由选择是否继续注册
    }

	CDialog::OnOK();
}


void CRegDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnCancel();
	CLoginDlg login_Dialog;
}


BOOL CRegDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_brush.CreateSolidBrush(RGB(253,245,230));
	// TODO:  在此添加额外的初始化
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
    SetLayeredWindowAttributes(0,200,LWA_ALPHA);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


HBRUSH CRegDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brush;
}
