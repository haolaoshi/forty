
// ChatServerDlg.h : ͷ�ļ�
//

#pragma once
 
 #define WM_SOCKET	WM_USER+1000
// CChatServerDlg �Ի���
class CChatServerDlg : public CDialogEx
{
// ����
public:
	CChatServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

	SOCKET s,s1;

	sockaddr_in addr,addr1;
// �Ի�������
	enum { IDD = IDD_VSNET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnSocket(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSend();
};
