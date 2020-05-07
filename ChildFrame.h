#pragma once
#include "afxpropertygridctrl.h"


// CChildFrame �Ի���

class CChildFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CChildFrame)

public:
	CChildFrame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildFrame();

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
  
	CString int10ToStr16(LONGLONG a);	//10����ת16�����ַ���

};
