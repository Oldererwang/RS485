#pragma once
#include "afxpropertygridctrl.h"
#include "SerialPort.h"


// CChildFrame �Ի���

class CChildFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CChildFrame)

public:
	CChildFrame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildFrame();
	CFont m_editFont;

	bool m_Connected;

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CMFCPropertyGridCtrl m_propertyGrid;
	afx_msg void OnBnClickedSendorderbtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMThemeChangedMfcpropertygridOrder(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedMfcpropertygridOrder();
	void str2hex(CString str, char* hex); // �������������Ҫ���ĳ���;
	//10����ת16�����ַ���
	CString int10ToStr16(LONGLONG num);
	//10����ת16�����ַ���,flag��Ӧ�Ƿ��λfla=1��λ��0����λ
	CString int10ToStr16(LONGLONG num,int flag);
	//���硰66 03 ...����ʽ���ַ����Կո�Ϊ���ת��Ϊ��Ӧ��16�������������BYTE��������
	int HexStrToHex(CString str, BYTE* data);
	//HexChar�����Ĺ����ǽ�16�����ַ���ASCII��תΪ��Ӧ��С��16������
	int HexChar(char c);

	afx_msg void OnBnClickedSettimesendbtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedDefalutbtn();
protected:
	afx_msg LRESULT OnChildmessage(WPARAM wParam, LPARAM lParam);
};
