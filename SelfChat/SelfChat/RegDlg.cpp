// RegDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SelfChat.h"
#include "RegDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"

// CRegDlg �Ի���

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


// CRegDlg ��Ϣ�������


void CRegDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

    CString username;//���ļ��ж�ȡ�û�������У�飬���������û������ļ��Ѵ����򲻽���ע��
    CString sex;
    bool flag=false;//���
    char * path="username.txt";//�ļ�·��

    CFile fp;//ʹ��MFC��CFile������д���ļ�
    fp.Open(path,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
    fp.SeekToBegin();//�ƶ��ļ�ָ��λ�����ļ�ͷ

    CArchive ar(&fp,CArchive::load);//ʹ��CArchive���ж�ȡ�ļ�
    UpdateData();//�����ݴӿؼ����Ƶ��ؼ�����

    //�������ҿո����
     m_Sign_Account.TrimLeft();
     m_Sign_Account.TrimRight();

     m_Sign_Pass.TrimLeft();
     m_Sign_Pass.TrimRight();

      //��ѡ��ѡ�񲢻�ȡ���ı�
      UINT nID=GetCheckedRadioButton(IDC_RADIO_MAN,IDC_RADIO_WOMAN);
      GetDlgItemText(nID,sex);
      //У�����
while(ar.ReadString(username)){
    username.TrimLeft();
    username.TrimRight();
    if(strcmp(username,m_Sign_Account)==0)
    {
        flag=true;//����Ѵ����û���������flagΪtrue
        break;
    }else
    {
        ar.ReadString(username);//��ȡ��һ�У�ÿһ��Ϊһ�����ԣ������û��������룬�Ա��ܹ�3 �����ԣ�
        ar.ReadString(username);//��ȡ��һ��
    }
}
ar.Close();

fp.SeekToEnd();//�ļ�д��Ϊ׷�Ӳ���������д��ǰ���뽫�ļ�ָ���ƶ����ļ�β

    if(!flag)
    {
        //CFile Write(*str,GetLength())д��
        fp.Write(m_Sign_Account,m_Sign_Account.GetLength());
        //win����\r\n����д����ֻ��Ҫ\n���ɻ���
        fp.Write("\n",sizeof(char));
        fp.Write(m_Sign_Pass,m_Sign_Pass.GetLength());
        fp.Write("\n",sizeof(char));
        fp.Write(sex,sex.GetLength());
        fp.Write("\n",sizeof(char));
        fp.Close();
        MessageBox("ע��ɹ�");
        CDialog::OnOK();
    }
    else
    {
        MessageBox("�û��Ѵ���");//�û��Ѵ�����ʾ�򣬲��ر�ע��򣬿����û�����ѡ���Ƿ����ע��
    }

	CDialog::OnOK();
}


void CRegDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialog::OnCancel();
	CLoginDlg login_Dialog;
}


BOOL CRegDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_brush.CreateSolidBrush(RGB(253,245,230));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
    SetLayeredWindowAttributes(0,200,LWA_ALPHA);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CRegDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brush;
}
