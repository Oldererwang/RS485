
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
	CString cboStr;	//得到波特率进行判断

	bool m_Connected;

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

	int unknow;

	// 实现
protected:
	HICON m_hIcon;
	CChildFrame childframe;
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
	int orderFlag;			//B类解析判断flag

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
	void str2hex(char* str, char* hex,int n);	
	
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
	afx_msg LRESULT ByteMessage(WPARAM wParam, LPARAM lParam);	 //接收子窗口发送的信息
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);	//串口热插拔消息
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenPort();
	afx_msg void OnBnClickedChkAutoSendData();
	afx_msg void OnBnClickedChkHexSend();
	afx_msg void OnBnClickedChkReceive();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LPARAM OnComm(WPARAM ch, LPARAM port);
	CListCtrl m_ListCurrent;
	CListCtrl m_ListInfo;
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
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
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
	CTabCtrl m_tab;
	//双击list事件
	afx_msg void OnNMDblclkList4(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_ListCurrentStr;
	
	CEdit m_CurrentEdit;

	afx_msg void OnNMClickListCurrent(NMHDR* pNMHDR, LRESULT* pResult);
	CRichEditCtrl m_CtrRichEdit;
	CString m_StrRichEdit;
	//读取串口大小位置记录
	BOOL ReadWndPosition();
	//写入窗口位置大小记录
	BOOL WriteWndPosition();
	//销毁窗口
	virtual BOOL DestroyWindow();
protected:
	afx_msg LRESULT OnTochildMessage(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void On32772();
	afx_msg void OnMenuCOrder();
	afx_msg void OnMenuBOrder();
	afx_msg void OnTimeSet();
	afx_msg void OnMenuShowState();
	afx_msg void OnMenuOrder();
	afx_msg void OnMenuSetDefault();
	afx_msg void OnMenuSaveCache();
	afx_msg void OnMenuClearReceive();
	afx_msg void OnMenuAboutDlg();
	afx_msg void OnBnClickedButton3();
};
