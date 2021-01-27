
// ChatClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CChatClientDlg 对话框




CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CChatClientDlg::OnConnect)
	ON_BN_CLICKED(IDC_SEND, &CChatClientDlg::OnSend) 
	ON_MESSAGE(WM_SOCKET, OnSocket)
END_MESSAGE_MAP()


// CChatClientDlg 消息处理程序

BOOL CChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	GetDlgItem(IDC_TEXT)->EnableWindow(false);
	GetDlgItem(IDC_SENDTEXT)->EnableWindow(false);
	//GetDlgItem(IDC_CONNECT)->EnableWindow(false);
	WSADATA data;
	WORD w = MAKEWORD(2,0);
	::WSAStartup(w,&data);

	s = ::socket(AF_INET,SOCK_STREAM,0);
	//addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//addr.sin_port = htons(8080);
	//addr.sin_family = AF_INET;
	::WSAAsyncSelect(s,this->m_hWnd,WM_SOCKET,FD_READ);//异步模式
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatClientDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatClientDlg::OnConnect()
{
		CString str,str1;
	int port;
	GetDlgItem(IDC_ADDR)->GetWindowText(str);
	GetDlgItem(IDC_PORT)->GetWindowText(str1);
	if(str == "" || str1 == ""){
		MessageBox(_T("地址或者端口不能为空"));
	}else{
		port = atoi(str1.GetBuffer(1));
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr(str.GetBuffer(1));
		addr.sin_port= ntohs(port);
		GetDlgItem(IDC_TEXT)->SetWindowText("正在连接服务器...\r\n");
		int rc = ::connect(s,(sockaddr*)&addr,sizeof(addr));
		int  isOK = (rc == NO_ERROR || (rc == SOCKET_ERROR && ::WSAGetLastError() == WSAEWOULDBLOCK));
		if(isOK){
			GetDlgItem(IDC_TEXT)->GetWindowText(str);
			str += "连接成功!\r\n";
			GetDlgItem(IDC_TEXT)->SetWindowText(str);
			GetDlgItem(IDC_SENDTEXT)->EnableWindow(true);
			GetDlgItem(IDC_ADDR)->EnableWindow(false);
			GetDlgItem(IDC_PORT)->EnableWindow(false);
		}else{
			GetDlgItem(IDC_TEXT)->GetWindowText(str);
			str += "连接失败，请重试！\r\n";
			GetDlgItem(IDC_TEXT)->SetWindowText(str);
		}
	}
}


void CChatClientDlg::OnBnClickedConnect()
{
		// TODO: 在此添加控件通知处理程序代码

}


void CChatClientDlg::OnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,str1;
	GetDlgItem(IDC_SENDTEXT)->GetWindowText(str);
	if(str == ""){
		GetDlgItem(IDC_TEXT)->GetWindowText(str1);
		str1 +="\r\n发送内容不能为空！"; 
		str1 +="\r\n";
		GetDlgItem(IDC_TEXT)->SetWindowText(str1);
	}else{
		::send(s,str.GetBuffer(1),sizeof(str),0);
		GetDlgItem(IDC_TEXT)->GetWindowText(str1);
		str1 +="\r\n发送内容为：";
		str1 +=str;
		str1 +="\r\n";
		GetDlgItem(IDC_TEXT)->SetWindowText(str1);
	}
}

LRESULT CChatClientDlg::OnSocket(WPARAM nID, LPARAM lParam)
{
	// TODO: 在此添加控件通知处理程序代码
	//rror C2440: “static_cast”: 无法从“void (__thiscall CChatClientDlg::* )(WPARAM,LPARAM)”
	//转换为“LRESULT (__thiscall CWnd::* )(WPARAM,LPARAM)”
//      从基类型到派生类型的强制转换需要 dynamic_cast 或 static_cast

	char cs[100] = {0};
	if(lParam == FD_READ)
	{
		CString num = "";
		recv(s,cs,100,NULL);
		GetDlgItem(IDC_TEXT)->GetWindowTextA(num);
		num += "\r\n服务器说：";
		num += (LPTSTR)cs;
		GetDlgItem(IDC_TEXT)->SetWindowTextA(num);
	}

	return 0;
}