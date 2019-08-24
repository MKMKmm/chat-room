// SelfChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SelfChat.h"
#include "SelfChatDlg.h"
//ADD
//#include "ClientSocket.h"
#include "tagHeader.h"
#include "LoginDlg.h"
#include "RegDlg.h"
#include <atlimage.h>
#include "mmsystem.h"  
#include <Digitalv.h>
#pragma comment(lib,"Winmm.lib")  
//ADD
	
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//ȫ�ֱ���
HWND m_hWnd;
DWORD DeviceId;
MCI_OPEN_PARMS mciopenparms;




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CAboutDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSelfChatDlg �Ի���




CSelfChatDlg::CSelfChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelfChatDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_strMessage(_T(""))
	, strport(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Pchat=NULL;
}

void CSelfChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	DDX_Control(pDX, IDC_LIST1, m_UserList);
	DDX_Control(pDX, IDC_EDIT3, m_MessageList);
	DDX_Text(pDX, IDC_EDIT4, m_strMessage);
	DDX_Control(pDX, IDC_EDIT2, m_port);
	DDX_Text(pDX, IDC_EDIT2, strport);
	DDX_Control(pDX, IDC_EDIT4, m_EditWords);
	DDX_Control(pDX, IDC_EDIT1, m_Usr);
	DDX_Control(pDX, IDC_BUTTON1, m_Enter);
	DDX_Control(pDX, IDC_BUTTON2, m_Quit);
	DDX_Control(pDX, IDC_BUTTON3, m_Send);
	DDX_Control(pDX, IDC_BUTTON4, m_Refresh);
	DDX_Control(pDX, IDCANCEL, m_Exit);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
}

BEGIN_MESSAGE_MAP(CSelfChatDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CSelfChatDlg::OnEnter)
	ON_BN_CLICKED(IDC_BUTTON2, &CSelfChatDlg::OnQuit)
	ON_BN_CLICKED(IDC_BUTTON3, &CSelfChatDlg::OnSend)
	ON_BN_CLICKED(IDC_BUTTON4, &CSelfChatDlg::OnRefresh)
	ON_BN_CLICKED(IDC_BUTTON5, &CSelfChatDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDCANCEL, &CSelfChatDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_filechoice, &CSelfChatDlg::OnBnClickedfilechoice)
	ON_BN_CLICKED(IDC_play, &CSelfChatDlg::OnBnClickedplay)
	ON_BN_CLICKED(IDC_pause, &CSelfChatDlg::OnBnClickedpause)
	ON_LBN_DBLCLK(IDC_LIST1, &CSelfChatDlg::OnLbnDblclkList1)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CSelfChatDlg::OnNMCustomdrawSlider1)
//ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER1, &CSelfChatDlg::OnTRBNThumbPosChangingSlider1)
ON_WM_HSCROLL()
//ON_WM_CTLCOLOR()
ON_WM_HSCROLL()
END_MESSAGE_MAP()

CSelfChatDlg::~CSelfChatDlg()
{
       if (NULL != m_Pchat)   
    {   
        // ɾ����ģ̬�Ի������   
        delete m_Pchat;   
    }   
}
// CSelfChatDlg ��Ϣ�������

BOOL CSelfChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//ADD
	m_pSocket=NULL;

	//��ʼ����
	m_Usr.SetFocus();
	m_Quit.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
	m_Refresh.EnableWindow(false);
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
	SetLayeredWindowAttributes(0,200,LWA_ALPHA);
	//ADD
	while (TRUE)
	{
		CLoginDlg login_Dialog;
		//ģ̬�Ի���
		int nReturn = login_Dialog.DoModal();//����IDOK��IDCANCEL��������ص���IDCANCEL����Ҫ����WindowsCommDlgExtendedError������ȷ���Ƿ�����һ������IDOK��IDCANCEL���ǳ������������û�ѡ�����OK��ť����Cancel��ť
		if(nReturn == IDCANCEL){//���ȡ��
			exit(0);
		}
		if (nReturn == IDOK){//���ȷ��	
			CWnd* pLoginWhd = this->GetDlgItem(IDD_DIALOG1);
			CString str_User = login_Dialog.m_strUser;
			CString str_Password = login_Dialog.m_strPassword;
			UpdateData();//���ؼ����ݸ��Ƹ��ؼ�����
			CString username;
			CString password;
			CString sex;
			//��ע�����Ʋ���
			bool flag=false;
			char * path="username.txt";
			CFile file;
			file.Open(path,CFile::modeRead);
			file.SeekToBegin();
			CArchive ar(&file,CArchive::load);
			//ȥ���������ҿո�����
			str_User.TrimLeft();
			str_User.TrimRight();
			str_Password.TrimLeft();
			str_Password.TrimRight();
			//У���û����룬��ע��У����ͬ�Ĳ������������֤��һ������У������
			while(ar.ReadString(username))
			{
				if(ar.ReadString(password))
				{
					username.TrimLeft();
					username.TrimRight();
					password.TrimLeft();
					password.TrimRight();
					if(strcmp(username,str_User)==0
						&&strcmp(password,str_Password)==0)
					{
						flag=true;
						ar.ReadString(sex);//����û���֤��ȷ��flag=true,����sexΪ�û����Ա�
						break;          
					}               
				}
				ar.ReadString(sex);     
			}
			//�ر�CFile��CArchive
			ar.Close();
			file.Close();
			if(flag)
			{
				break;
			}
			else{
				MessageBox("�û��������ڻ��������");//�û����������û���������ʾ

			}
		}

	}

	m_slider.SetRange(0,100);//������ƶ���Χ0~1000
	m_slider.SetPos(50);//����ָ��ĳ�ʼλ����Ϊ500�����ʼ����Ϊ50
	SetDlgItemInt(IDC_volume, 50);
	GetDlgItem(IDC_play)->EnableWindow(false);//�ļ�û�ж�ȡʱ���а�ťӦ���ǲ���ѡ��
	GetDlgItem(IDC_pause)->EnableWindow(false);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSelfChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSelfChatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	//ע�͸���䣺��ֹ�ظ������ػ�����
           CPaintDC    dc(this);   
           CRect    rect;     
           GetClientRect(rect);     
           dc.FillSolidRect(rect,    RGB(74, 83, 97));     

		   CRect rc;
		   GetWindowRect(&rc);
		   CImage mImage;
		if(mImage.Load(_T("���.jpg")) == S_OK)
		{
			//������ͼƬ��������ʹ��ڴ�Сһ��
			mImage.Draw(GetDC()->GetSafeHdc(), CRect(0,0,rc.Width(),rc.Height()));
		}

           CDialog::OnPaint();
      

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSelfChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSelfChatDlg::OnEnter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	UpdateData();
	m_pSocket = new CClientSocket;
	m_pSocket->GetDlg(this);

	BYTE nFild[4];
	CString sip;
	ServerIP.GetAddress(nFild[0],nFild[1],nFild[2],nFild[3]);	
	sip.Format("%d.%d.%d.%d",nFild[0],nFild[1],nFild[2],nFild[3]);
	if(m_strName.IsEmpty())
	{
		AfxMessageBox("���Լ�ȡ���ǳư�!");
		return;
	}
	if(sip.IsEmpty())
	{
		AfxMessageBox("��ָ��IP��ַ!");
		return;	
	}
	if(strport.IsEmpty())
	{
		AfxMessageBox("��ָ�����Ӷ˿�!");
		return;
	}

	if(!m_pSocket->Create())
	{
		AfxMessageBox("���紴�����󣡣���");
		m_pSocket->Close();
		return;
	}
	if(!m_pSocket->Connect(sip,atoi(strport)))
	{
		AfxMessageBox("���ӷ�����ʧ�ܣ�����");
		m_pSocket->Close();
		return;	
	}

	//����
	m_Usr.EnableWindow(false);
	ServerIP.EnableWindow(false);
	m_port.EnableWindow(false);
	m_Enter.EnableWindow(false);
	m_Quit.EnableWindow(true);
	m_EditWords.EnableWindow(true);
	m_EditWords.SetFocus();
	m_Send.EnableWindow(true);
	m_Refresh.EnableWindow(true);
	m_Exit.EnableWindow(false);
	//����

	Header head;
	head.type = LOGIN_IO;
	head.len = m_strName.GetLength();
	head.flag=0;
	m_pSocket->Send((char *)&head,sizeof(Header));
	m_pSocket->Send(m_strName,m_strName.GetLength());

	theApp.m_strName = m_strName;
	m_MessageList.SetWindowTextA("");
	this->SetWindowTextA(m_strName + "-SelfChat");

//ADD
}

void CSelfChatDlg::OnQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	if(m_pSocket)
	{
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket=NULL;
	}
	m_UserList.ResetContent();
	m_MessageList.ReplaceSel("���Ѿ��˳���, лл���!");
	this->SetWindowTextA("�����ҿͻ���-SelfChat");

	//����
	m_Usr.EnableWindow(true);
	m_Usr.SetFocus();
	ServerIP.EnableWindow(true);
	m_port.EnableWindow(true);
	m_Enter.EnableWindow(true);
	m_Quit.EnableWindow(false);
	m_EditWords.EnableWindow(false);
	m_Send.EnableWindow(false);
	m_Exit.EnableWindow(true);
//ADD
}

void CSelfChatDlg::OnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	UpdateData();
	if(m_strMessage == "")
	{
		AfxMessageBox("���ܷ��Ϳ���Ϣ!");
		m_EditWords.SetFocus();
		return;
	}
	Header head;
	head.type = SEND_MESSAGE;
	head.len = m_strMessage.GetLength();
	head.flag=0;
	m_pSocket->Send((char *)&head,sizeof(Header));


	if(m_pSocket->Send(m_strMessage,m_strMessage.GetLength()))
	{
		m_strMessage = "";
		UpdateData(FALSE);
		m_EditWords.SetFocus();
		return;
	}
	else
	{
		AfxMessageBox("���紫�����");		
	}
//ADD
}

//ADD
BOOL CSelfChatDlg::GetMsgFromRoom()
{
	char buff[1000];
	memset(buff,0,sizeof(buff));
	m_pSocket->Receive(buff, sizeof(buff));
	m_pSocket->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
	
	CString strTemp = buff;
	strTemp += "\r\n";
	m_MessageList.ReplaceSel(strTemp);
	return TRUE;
}
//ADD

//ADD
void  CSelfChatDlg::UpdateUser()
{
    char buff[1000];
	memset(buff,0,sizeof(buff));
	m_pSocket->Receive(buff, sizeof(buff));
	m_pSocket->AsyncSelect(FD_CLOSE|FD_READ|FD_WRITE);
	
	CString user_info = buff;

	CString array[100];
	int b = 0;
	for( int i = 0; i < user_info.GetLength(); i++ )
	{
		if(i != (user_info.GetLength() - 1))
		{
			if ( user_info[i] == '&' )
			{
				b ++;
			}
			else
			{
				array[b] = array[b] + user_info[i];
			}
		}
	}

	m_UserList.ResetContent();
	for(int j = 0; j < b + 1; j ++)
	{
		m_UserList.AddString(array[j]);
	}
}
//ADD
void CSelfChatDlg::OnRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	m_MessageList.SetWindowTextA("");
//ADD
}

void CSelfChatDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
//ADD
}


void CAboutDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CSelfChatDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialog::OnCancel();
	EndDialog(-1);
}

void CSelfChatDlg::OnLbnDblclkList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText;   
    int nCurSel;   
     if (NULL == m_pSocket->m_Pchat)   
    {   
        // ������ģ̬�Ի���ʵ��   
        m_pSocket->m_Pchat = new Pchat();   
		m_pSocket->m_Pchat->GetDlg(this);
        m_pSocket->m_Pchat->Create(IDD_DIALOG3, this);   
    }   
    // ��ʾ��ģ̬�Ի���   
    m_pSocket->m_Pchat->ShowWindow(SW_SHOW);   
    nCurSel = m_UserList.GetCurSel();           // ��ȡ��ǰѡ���б���   
    m_UserList.GetText(nCurSel, strText);       // ��ȡѡ���б�����ַ��� 
	

}


//����
void Load(HWND hWnd, CString strFilepath)
{
	m_hWnd = hWnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0); //�ڼ����ļ�ǰ�������һ�β��ŵ��豸
	mciopenparms.lpstrElementName = strFilepath; //�������ļ�·�������豸
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))
	{
		//��������ʧ��,��������Ϣ������buffer,����ʾ������
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256); //��ȡ�������Ӧ�Ĵ�����Ϣ
		MessageBox(hWnd, buffer, "�����棡", MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP); //����������Ϣ��ʾ�Ի���
	}
	DeviceId = mciopenparms.wDeviceID;
	//���ļ��ɹ��͹����ļ����豸
}

void play()
{
     //���Ų����ṹ
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback=(DWORD)m_hWnd;
	mciplayparms.dwFrom=0;//ÿ�β��Ŷ��Ǵ�0��ʼ����  dwFrom�����������ֲ��ŵ���ʼλ��
	mciSendCommand(DeviceId,MCI_PLAY,MCI_FROM|MCI_NOTIFY,(DWORD)(LPVOID)&mciplayparms);//dwCallback��MCI_NOTIFY����Գ��ֵ�

}


void pause()
{
	mciSendCommand(DeviceId, MCI_PAUSE, 0, 0);
}

void resume()
{
	mciSendCommand(DeviceId, MCI_RESUME, 0, 0);
}



DWORD setVolume(DWORD vol)
{
	MCI_DGV_SETAUDIO_PARMS setvolume; //���������Ĳ����ṹ��
	setvolume.dwCallback = NULL; //
	setvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME; //��������������
	setvolume.dwValue = vol; //����ֵ��vol
	mciSendCommand(DeviceId, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&setvolume);
	return 0;
}



void CSelfChatDlg::OnBnClickedfilechoice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	char szFileFilter[]="mp3�ļ�(*.mp3)|*.mp3|"
		"wma�ļ�(*.wma)|*.wma|"
		"wav�ļ�(*.wav)|*.wav|"
		"�����ļ�(*.*)|*.*|";//�ļ����͹���  
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY,szFileFilter);
	if(dlg.DoModal()==IDOK)
	{
		CString strFilepath=dlg.GetPathName();
		CString strFilename=dlg.GetFileName();
		SetDlgItemText(IDC_filename,strFilename);
		Load(this->m_hWnd,strFilepath);
		//�ļ���ȡ�ɹ�ʱ���а�ť��Ϊ��ѡ
		GetDlgItem(IDC_play)->EnableWindow(true);
		GetDlgItem(IDC_pause)->EnableWindow(true);
	}
}


void CSelfChatDlg::OnBnClickedplay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		play();
        SetDlgItemText(IDC_pause, "��ͣ");

}


void CSelfChatDlg::OnBnClickedpause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CString strTemp;
	GetDlgItemText(IDC_pause, strTemp); //��ȡ��ť��״̬
	if (strTemp.Compare("��ͣ") == 0)
	{
		pause();
		SetDlgItemText(IDC_pause, "�ָ�");
	}
 
	if (strTemp.Compare("�ָ�") == 0)
	{
	
		resume();
		SetDlgItemText(IDC_pause, "��ͣ");
	}

}





void CSelfChatDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int pos = m_slider.GetPos();    // ��ȡˮƽ��������ǰλ��  
 
	switch (nSBCode)
	{
		// ����������һ�У���pos��1  
	case SB_LINELEFT:
		pos -= 1;
		break;
		// ������ҹ���һ�У���pos��1  
	case SB_LINERIGHT:
		pos += 1;
		break;
		// ����������һҳ����pos��10  
	case SB_PAGELEFT:
		pos -= 10;
		break;
		// ������ҹ���һҳ����pos��10  
	case SB_PAGERIGHT:
		pos += 10;
		break;
		// �������������ˣ���posΪ1  
	case SB_LEFT:
		pos = 1;
		break;
		// ������������Ҷˣ���posΪ100  
	case SB_RIGHT:
		pos = 100;
		break;
		// ����϶������������ָ��λ�ã���pos��ֵΪnPos��ֵ  
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
	default:
		SetDlgItemInt(IDC_volume, pos);
		return;
	}
 
	// ���ù�����λ��  
	m_slider.SetPos(pos);
	setVolume(pos);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

}
