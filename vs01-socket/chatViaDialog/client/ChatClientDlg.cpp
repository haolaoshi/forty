
// ChatClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
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


// CChatClientDlg �Ի���




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


// CChatClientDlg ��Ϣ�������

BOOL CChatClientDlg::OnInitDialog()
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
	::WSAAsyncSelect(s,this->m_hWnd,WM_SOCKET,FD_READ);//�첽ģʽ
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatClientDlg::OnPaint()
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
		MessageBox(_T("��ַ���߶˿ڲ���Ϊ��"));
	}else{
		port = atoi(str1.GetBuffer(1));
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr(str.GetBuffer(1));
		addr.sin_port= ntohs(port);
		GetDlgItem(IDC_TEXT)->SetWindowText("�������ӷ�����...\r\n");
		int rc = ::connect(s,(sockaddr*)&addr,sizeof(addr));
		int  isOK = (rc == NO_ERROR || (rc == SOCKET_ERROR && ::WSAGetLastError() == WSAEWOULDBLOCK));
		if(isOK){
			GetDlgItem(IDC_TEXT)->GetWindowText(str);
			str += "���ӳɹ�!\r\n";
			GetDlgItem(IDC_TEXT)->SetWindowText(str);
			GetDlgItem(IDC_SENDTEXT)->EnableWindow(true);
			GetDlgItem(IDC_ADDR)->EnableWindow(false);
			GetDlgItem(IDC_PORT)->EnableWindow(false);
		}else{
			GetDlgItem(IDC_TEXT)->GetWindowText(str);
			str += "����ʧ�ܣ������ԣ�\r\n";
			GetDlgItem(IDC_TEXT)->SetWindowText(str);
		}
	}
}


void CChatClientDlg::OnBnClickedConnect()
{
		// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CChatClientDlg::OnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str,str1;
	GetDlgItem(IDC_SENDTEXT)->GetWindowText(str);
	if(str == ""){
		GetDlgItem(IDC_TEXT)->GetWindowText(str1);
		str1 +="\r\n�������ݲ���Ϊ�գ�"; 
		str1 +="\r\n";
		GetDlgItem(IDC_TEXT)->SetWindowText(str1);
	}else{
		::send(s,str.GetBuffer(1),sizeof(str),0);
		GetDlgItem(IDC_TEXT)->GetWindowText(str1);
		str1 +="\r\n��������Ϊ��";
		str1 +=str;
		str1 +="\r\n";
		GetDlgItem(IDC_TEXT)->SetWindowText(str1);
	}
}

LRESULT CChatClientDlg::OnSocket(WPARAM nID, LPARAM lParam)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//rror C2440: ��static_cast��: �޷��ӡ�void (__thiscall CChatClientDlg::* )(WPARAM,LPARAM)��
	//ת��Ϊ��LRESULT (__thiscall CWnd::* )(WPARAM,LPARAM)��
//      �ӻ����͵��������͵�ǿ��ת����Ҫ dynamic_cast �� static_cast

	char cs[100] = {0};
	if(lParam == FD_READ)
	{
		CString num = "";
		recv(s,cs,100,NULL);
		GetDlgItem(IDC_TEXT)->GetWindowTextA(num);
		num += "\r\n������˵��";
		num += (LPTSTR)cs;
		GetDlgItem(IDC_TEXT)->SetWindowTextA(num);
	}

	return 0;
}