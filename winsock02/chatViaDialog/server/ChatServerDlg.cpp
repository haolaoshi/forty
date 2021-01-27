
// ChatServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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


// CChatServerDlg �Ի���




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


// CChatServerDlg ��Ϣ�������

BOOL CChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	    WSADATA data;
    WORD w = MAKEWORD(2, 0); 
    ::WSAStartup(w, &data);//1, �����ʼ����
   
    s = ::socket(AF_INET, SOCK_STREAM, 0);//2, �����׽��־����
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(8080);
	::bind(s,(sockaddr*)&addr,sizeof(addr));
	::listen(s,2);
	GetDlgItem(IDC_TEXT)->EnableWindow(false);
	GetDlgItem(IDC_ADDR)->SetWindowText(_T("��������������"));
 
	::WSAAsyncSelect(s,this->m_hWnd,WM_SOCKET,FD_ACCEPT|FD_READ);//�첽ģʽ
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatServerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
				str3.Format("��%d�ͻ��Ѿ�����������",n);
				GetDlgItem(IDC_TEXT)->SetWindowText(str3);
				str3 += ::inet_ntoa(addr1.sin_addr);
				str3 += "��¼ \r\n";
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
				num += "����˵";
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T(""),str1;
	GetDlgItem(IDC_SENDTEXT)->GetWindowText(str);

	if(str == "")
		MessageBox(_T("���Ͳ���Ϊ�գ�"));
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
			GetDlgItem(IDC_TEXT)->SetWindowText("��Ϣ����ʧ��\r\n");
		}

	}
}
