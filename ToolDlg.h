
// ToolDlg.h : 头文件
//

#pragma once

#define CURRENTVALUE0 3.5
#define CURRENTVALUE1 100

#include "SerialPortTool.h"
#include "SerialPort.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "ChildFrame.h"

class COrderEdit;
static CString m_MyData;
static CString m_Add("");
static int dataNum =0;

// CToolDlg 对话框
class CToolDlg : public CDialog
{
	// 构造
public:
	CToolDlg(CWnd* pParent = NULL);	// 标准构造函数
	COrderEdit *orderEditDlg;		//子窗口类成员
	CChildFrame *m_ChildFrame;
	CFont m_editFont;
	CFont m_firstFont;


	bool m_Connected;
	bool m_Light;	//切换b类数据结构

	// 对话框数据
	enum { IDD = IDD_SERIALPORTTOOL_DIALOG };
	CComboBox	m_cboBaudRate;		// 波特率
	CComboBox	m_cboSerialPort;	// 串口列表
	CButton		m_btnOpenClosePort;
	//	CButton		m_btnClearCount;
	CString		m_StrSendData;		// 要发送的数据
	CString		m_StrSerialPort;	// 获得当前串口
	CString		m_StrBaudRate;		// 获得当前波特率
	CString		m_StrFlowControl;	// 获得当前流控制
	BOOL		m_bHexReceive;		// 是否以16进制接收
	UINT		m_uReceiveBytes;	// 统计收到的字节数
	UINT		m_uSendBytes;		// 统计发出的字节数

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CRect m_ChildRect;

	int m_Row;	//listcurrentset行
	int m_Col;	//listcurrentset列

	// 实现
protected:
	HICON m_hIcon;
	CSerialPort m_SerialPort;
	CBrush m_brush;		//画刷，背景颜色

	LOGFONT logfont;		//listcontrol控件字体变量		
	CString msgNotice;		//串口发来的字符串

	BYTE m_RxData[2048];
	char m_HexData[2048];	//Hex数据数组
	char hexData[512];		//根据协议确定 字节数*2
	long m_iRxLen;			//缓冲长度
	int endFLag;			//缓冲行数
	int dfInt;				//设置时间循环flag

	CString knowStrData;		//Hex数据
	CString groundCuA;			//A相接地电流
	CString groundCuB;			//B相接地电流
	CString groundCuC;			//C相接地电流
	CString groundCuAll;		//总接地电流
	CString CurrentA;			//A相运行电流
	CString CurrentB;			//B相运行电流
	CString CurrentC;			//C相运行电流

	char* m_szWriteBuffer;//写缓冲区
	DWORD m_nWriteBufferSize;//写缓冲区大小

	CString hexCharToNumber(char HexChar);			//16进制转16进制字节数字
	char CombineHexChar(char CharH,char CharL);
	void HexStringFilter(CString &str);
	CString ChangeCharstr2Hexstr(CString Charstr);	
	//ASCII字符数组转16进制字符数组
	void str2hex(char* str, char* hex);	
	
	CString hex2data(char* hex);					//字符数组转CString
	void hexString2Byte(CString& in, BYTE *out);	//16进制CString转BYTE数组
	CString kDatatoOrder(CString date);		//k的数据转换为指令
	CString bDatatoOrder(CString date);		//b的数据转换为指令
	CString LookChildString(CString cStr);	//解析电流数据
	CString AvoidLarge(CString cstr);		//防呆避免数据过大
	void RefreshCom();						//串口重置函数
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OrderMessage(WPARAM wParam, LPARAM lParam);	 //接收子窗口发送的信息
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);	//串口热插拔消息
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenPort();
	afx_msg void OnBnClickedBtnClearReceive();
	afx_msg void OnBnClickedChkAutoSendData();
	afx_msg void OnBnClickedChkHexSend();
	afx_msg void OnBnClickedChkReceive();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LPARAM OnComm(WPARAM ch, LPARAM port);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListCtrl m_ListCurrent;
	CListCtrl m_ListInfo;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedSendorderButton1();
	CListCtrl m_currentSet_List;
	CComboBox m_cboCurrent;
	afx_msg void OnBnClickedButtonCal();

	BOOL m_Check1;
	BOOL m_Check2;
	BOOL m_Check3;
	BOOL m_Check4;
	BOOL m_Check5;
	BOOL m_Check6;
	BOOL m_Check7;

	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedDefault();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnCbnSelchangeCboSerialPort();
	afx_msg void OnBnClickedshowstatebtn();
	CString editIp1;
	CString editIp2;
	CString editIp3;
	afx_msg void OnEnChangeEditip1();
	afx_msg void OnEnChangeEditip2();
	afx_msg void OnEnChangeEditip3();
	CString editIp4;
	afx_msg void OnEnChangeEditip4();
	afx_msg void OnBnClickedsetipbtn();
	afx_msg void OnBnClickedsetportbtn();
	afx_msg void OnEnChangeEditport();
	CString m_port;
protected:


public:
	afx_msg void OnBnClickedOpenchildframe();
	CTabCtrl m_tab;
	//双击list事件
	afx_msg void OnNMDblclkList4(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_ListCurrentStr;
	
	CEdit m_CurrentEdit;

	afx_msg void OnBnClickedAutodefaultbtn();
	afx_msg void OnNMClickListCurrent(NMHDR* pNMHDR, LRESULT* pResult);
	CRichEditCtrl m_CtrRichEdit;
	CString m_StrRichEdit;
};
