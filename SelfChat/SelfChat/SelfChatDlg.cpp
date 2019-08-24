// SelfChatDlg.cpp : 实现文件
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

//全局变量
HWND m_hWnd;
DWORD DeviceId;
MCI_OPEN_PARMS mciopenparms;




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSelfChatDlg 对话框




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
        // 删除非模态对话框对象   
        delete m_Pchat;   
    }   
}
// CSelfChatDlg 消息处理程序

BOOL CSelfChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//ADD
	m_pSocket=NULL;

	//初始界面
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
		//模态对话框
		int nReturn = login_Dialog.DoModal();//返回IDOK或IDCANCEL。如果返回的是IDCANCEL，则要调用WindowsCommDlgExtendedError函数来确定是否发生了一个错误。IDOK和IDCANCEL都是常量，它表明用户选择的是OK按钮还是Cancel按钮
		if(nReturn == IDCANCEL){//点击取消
			exit(0);
		}
		if (nReturn == IDOK){//点击确定	
			CWnd* pLoginWhd = this->GetDlgItem(IDD_DIALOG1);
			CString str_User = login_Dialog.m_strUser;
			CString str_Password = login_Dialog.m_strPassword;
			UpdateData();//将控件数据复制给控件变量
			CString username;
			CString password;
			CString sex;
			//与注册类似操作
			bool flag=false;
			char * path="username.txt";
			CFile file;
			file.Open(path,CFile::modeRead);
			file.SeekToBegin();
			CArchive ar(&file,CArchive::load);
			//去除数据左右空格数据
			str_User.TrimLeft();
			str_User.TrimRight();
			str_Password.TrimLeft();
			str_Password.TrimRight();
			//校验用户密码，与注册校验相同的操作，这里多验证了一步，即校验密码
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
						ar.ReadString(sex);//如果用户验证正确，flag=true,并且sex为用户的性别
						break;          
					}               
				}
				ar.ReadString(sex);     
			}
			//关闭CFile和CArchive
			ar.Close();
			file.Close();
			if(flag)
			{
				break;
			}
			else{
				MessageBox("用户名不存在或密码错误");//用户密码错误或用户不存在提示

			}
		}

	}

	m_slider.SetRange(0,100);//滑块的移动范围0~1000
	m_slider.SetPos(50);//滑块指针的初始位置设为500代表初始音量为50
	SetDlgItemInt(IDC_volume, 50);
	GetDlgItem(IDC_play)->EnableWindow(false);//文件没有读取时所有按钮应该是不可选的
	GetDlgItem(IDC_pause)->EnableWindow(false);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSelfChatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	//注释该语句：防止重复调用重画函数
           CPaintDC    dc(this);   
           CRect    rect;     
           GetClientRect(rect);     
           dc.FillSolidRect(rect,    RGB(74, 83, 97));     

		   CRect rc;
		   GetWindowRect(&rc);
		   CImage mImage;
		if(mImage.Load(_T("天空.jpg")) == S_OK)
		{
			//这里让图片绘制区域和窗口大小一致
			mImage.Draw(GetDC()->GetSafeHdc(), CRect(0,0,rc.Width(),rc.Height()));
		}

           CDialog::OnPaint();
      

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSelfChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSelfChatDlg::OnEnter()
{
	// TODO: 在此添加控件通知处理程序代码
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
		AfxMessageBox("给自己取个昵称吧!");
		return;
	}
	if(sip.IsEmpty())
	{
		AfxMessageBox("请指定IP地址!");
		return;	
	}
	if(strport.IsEmpty())
	{
		AfxMessageBox("请指定连接端口!");
		return;
	}

	if(!m_pSocket->Create())
	{
		AfxMessageBox("网络创建错误！！！");
		m_pSocket->Close();
		return;
	}
	if(!m_pSocket->Connect(sip,atoi(strport)))
	{
		AfxMessageBox("连接服务器失败！！！");
		m_pSocket->Close();
		return;	
	}

	//界面
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
	//界面

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
	// TODO: 在此添加控件通知处理程序代码
//ADD
	if(m_pSocket)
	{
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket=NULL;
	}
	m_UserList.ResetContent();
	m_MessageList.ReplaceSel("你已经退出了, 谢谢光顾!");
	this->SetWindowTextA("聊天室客户端-SelfChat");

	//界面
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
	// TODO: 在此添加控件通知处理程序代码
//ADD
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
		AfxMessageBox("网络传输错误！");		
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
	// TODO: 在此添加控件通知处理程序代码
//ADD
	m_MessageList.SetWindowTextA("");
//ADD
}

void CSelfChatDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
//ADD
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
//ADD
}


void CAboutDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CSelfChatDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnCancel();
	EndDialog(-1);
}

void CSelfChatDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText;   
    int nCurSel;   
     if (NULL == m_pSocket->m_Pchat)   
    {   
        // 创建非模态对话框实例   
        m_pSocket->m_Pchat = new Pchat();   
		m_pSocket->m_Pchat->GetDlg(this);
        m_pSocket->m_Pchat->Create(IDD_DIALOG3, this);   
    }   
    // 显示非模态对话框   
    m_pSocket->m_Pchat->ShowWindow(SW_SHOW);   
    nCurSel = m_UserList.GetCurSel();           // 获取当前选中列表项   
    m_UserList.GetText(nCurSel, strText);       // 获取选中列表项的字符串 
	

}


//加载
void Load(HWND hWnd, CString strFilepath)
{
	m_hWnd = hWnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0); //在加载文件前先清空上一次播放的设备
	mciopenparms.lpstrElementName = strFilepath; //将音乐文件路径传给设备
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))
	{
		//如果打开玩家失败,将出错信息储存在buffer,并显示出错警告
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256); //获取错误码对应的错误信息
		MessageBox(hWnd, buffer, "出错警告！", MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP); //弹出错误信息提示对话框
	}
	DeviceId = mciopenparms.wDeviceID;
	//打开文件成功就关联文件到设备
}

void play()
{
     //播放参数结构
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback=(DWORD)m_hWnd;
	mciplayparms.dwFrom=0;//每次播放都是从0开始播放  dwFrom用于设置音乐播放的起始位置
	mciSendCommand(DeviceId,MCI_PLAY,MCI_FROM|MCI_NOTIFY,(DWORD)(LPVOID)&mciplayparms);//dwCallback与MCI_NOTIFY是配对出现的

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
	MCI_DGV_SETAUDIO_PARMS setvolume; //设置音量的参数结构体
	setvolume.dwCallback = NULL; //
	setvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME; //动作是设置音量
	setvolume.dwValue = vol; //音量值是vol
	mciSendCommand(DeviceId, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&setvolume);
	return 0;
}



void CSelfChatDlg::OnBnClickedfilechoice()
{
	// TODO: 在此添加控件通知处理程序代码
	
	char szFileFilter[]="mp3文件(*.mp3)|*.mp3|"
		"wma文件(*.wma)|*.wma|"
		"wav文件(*.wav)|*.wav|"
		"所有文件(*.*)|*.*|";//文件类型过滤  
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY,szFileFilter);
	if(dlg.DoModal()==IDOK)
	{
		CString strFilepath=dlg.GetPathName();
		CString strFilename=dlg.GetFileName();
		SetDlgItemText(IDC_filename,strFilename);
		Load(this->m_hWnd,strFilepath);
		//文件读取成功时所有按钮变为可选
		GetDlgItem(IDC_play)->EnableWindow(true);
		GetDlgItem(IDC_pause)->EnableWindow(true);
	}
}


void CSelfChatDlg::OnBnClickedplay()
{
	// TODO: 在此添加控件通知处理程序代码
		play();
        SetDlgItemText(IDC_pause, "暂停");

}


void CSelfChatDlg::OnBnClickedpause()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString strTemp;
	GetDlgItemText(IDC_pause, strTemp); //获取按钮的状态
	if (strTemp.Compare("暂停") == 0)
	{
		pause();
		SetDlgItemText(IDC_pause, "恢复");
	}
 
	if (strTemp.Compare("恢复") == 0)
	{
	
		resume();
		SetDlgItemText(IDC_pause, "暂停");
	}

}





void CSelfChatDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int pos = m_slider.GetPos();    // 获取水平滚动条当前位置  
 
	switch (nSBCode)
	{
		// 如果向左滚动一列，则pos减1  
	case SB_LINELEFT:
		pos -= 1;
		break;
		// 如果向右滚动一列，则pos加1  
	case SB_LINERIGHT:
		pos += 1;
		break;
		// 如果向左滚动一页，则pos减10  
	case SB_PAGELEFT:
		pos -= 10;
		break;
		// 如果向右滚动一页，则pos加10  
	case SB_PAGERIGHT:
		pos += 10;
		break;
		// 如果滚动到最左端，则pos为1  
	case SB_LEFT:
		pos = 1;
		break;
		// 如果滚动到最右端，则pos为100  
	case SB_RIGHT:
		pos = 100;
		break;
		// 如果拖动滚动块滚动到指定位置，则pos赋值为nPos的值  
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
	default:
		SetDlgItemInt(IDC_volume, pos);
		return;
	}
 
	// 设置滚动块位置  
	m_slider.SetPos(pos);
	setVolume(pos);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

}
