#pragma once
#include "afxpropertygridctrl.h"
#include "SerialPort.h"


// CChildFrame 对话框

class CChildFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CChildFrame)

public:
	CChildFrame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChildFrame();
	CFont m_editFont;

	bool m_Connected;

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
	//10进制转16进制字符串
	CString int10ToStr16(LONGLONG num);
	//10进制转16进制字符串,flag对应是否进位fla=1进位，0不进位
	CString int10ToStr16(LONGLONG num,int flag);
	//将如“66 03 ...”形式的字符串以空格为间隔转换为对应的16进制数并存放在BYTE型数组里
	int HexStrToHex(CString str, BYTE* data);
	//HexChar函数的功能是将16进制字符由ASCII码转为相应大小的16进制数
	int HexChar(char c);

	afx_msg void OnBnClickedSettimesendbtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedDefalutbtn();
protected:
	afx_msg LRESULT OnChildmessage(WPARAM wParam, LPARAM lParam);
};
