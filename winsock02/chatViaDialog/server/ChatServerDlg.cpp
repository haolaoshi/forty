
// ChatServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
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


// CChatServerDlg 对话框




CChatServerDlg::CChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CChatServerDlg::OnSend)  
	ON_MESSAGE(WM_SOCKET, OnSocket)
END_MESSAGE_MAP()


// CChatServerDlg 消息处理程序

BOOL CChatServerDlg::OnInitDialog()
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
	    WSADATA data;
    WORD w = MAKEWORD(2, 0); 
    ::WSAStartup(w, &data);//1, 必须初始化：
   
    s = ::socket(AF_INET, SOCK_STREAM, 0);//2, 创建套接字句柄；
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(8080);
	::bind(s,(sockaddr*)&addr,sizeof(addr));
	::listen(s,2);
	GetDlgItem(IDC_TEXT)->EnableWindow(false);
	GetDlgItem(IDC_ADDR)->SetWindowText(_T("服务器监听启动"));
 
	::WSAAsyncSelect(s,this->m_hWnd,WM_SOCKET,FD_ACCEPT|FD_READ);//异步模式
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatServerDlg::OnPaint()
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
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CChatServerDlg::OnSocket(WPARAM wParam, LPARAM lParam)
{
	CString str3;
	char cs[100] = {0};
	int n= 0;
	int n1 = sizeof(addr1);
	switch(lParam){
		case FD_ACCEPT:
			{
				s1 = ::accept(s,(sockaddr*)&addr1,&n1);
				n++;
				str3.Format("有%d客户已经连接上来了",n);
				GetDlgItem(IDC_TEXT)->SetWindowText(str3);
				str3 += ::inet_ntoa(addr1.sin_addr);
				str3 += "登录 \r\n";
				GetDlgItem(IDC_TEXT)->SetWindowText(str3);
			}
			break;

		case FD_READ:
			{
				CString num = "";
				::recv(s1,cs,100,0);
				GetDlgItem(IDC_TEXT)->GetWindowText(num);
				num += "\r\n";
				num += (LPTSTR)::inet_ntoa(addr1.sin_addr);
				num += "对您说";
				num += cs;
				GetDlgItem(IDC_TEXT)->SetWindowText(num);
			}
			break;

		default:

			break;

		} 
	return 0;
}

void CChatServerDlg::OnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str = _T(""),str1;
	GetDlgItem(IDC_SENDTEXT)->GetWindowText(str);

	if(str == "")
		MessageBox(_T("发送不能为空！"));
	else{
		int rc = ::send(s1,str.GetBuffer(1),sizeof(str),0);
		//int  isOK = (rc == NO_ERROR || (rc == SOCKET_ERROR && ::WSAGetLastError() == WSAEWOULDBLOCK));
		//if(isOK){ 
		if(::send(s1,str.GetBuffer(1),sizeof(str),0) != SOCKET_ERROR){
			GetDlgItem(IDC_TEXT)->GetWindowText(str1);
			str1 += "\r\n";
			str1 += str;
			GetDlgItem(IDC_TEXT)->SetWindowText(str1);
		}else{
			GetDlgItem(IDC_TEXT)->SetWindowText("消息发送失败\r\n");
		}

	}
}
