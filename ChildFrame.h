#pragma once
#include "afxpropertygridctrl.h"


// CChildFrame 对话框

class CChildFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CChildFrame)

public:
	CChildFrame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChildFrame();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CMFCPropertyGridCtrl m_propertyGrid;
	afx_msg void OnBnClickedSendorderbtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMThemeChangedMfcpropertygridOrder(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedMfcpropertygridOrder();
	void str2hex(CString str, char* hex); // 这个函数可能需要更改长度;
  
	CString int10ToStr16(LONGLONG a);	//10进制转16进制字符串

};
