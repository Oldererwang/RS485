
// ToolDlg.h : ͷ�ļ�
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

// CToolDlg �Ի���
class CToolDlg : public CDialog
{
	// ����
public:
	CToolDlg(CWnd* pParent = NULL);	// ��׼���캯��
	COrderEdit *orderEditDlg;		//�Ӵ������Ա
	CChildFrame *m_ChildFrame;
	CFont m_editFont;
	CFont m_firstFont;


	bool m_Connected;
	bool m_Light;	//�л�b�����ݽṹ

	// �Ի�������
	enum { IDD = IDD_SERIALPORTTOOL_DIALOG };
	CComboBox	m_cboBaudRate;		// ������
	CComboBox	m_cboSerialPort;	// �����б�
	CButton		m_btnOpenClosePort;
	//	CButton		m_btnClearCount;
	CString		m_StrSendData;		// Ҫ���͵�����
	CString		m_StrSerialPort;	// ��õ�ǰ����
	CString		m_StrBaudRate;		// ��õ�ǰ������
	CString		m_StrFlowControl;	// ��õ�ǰ������
	BOOL		m_bHexReceive;		// �Ƿ���16���ƽ���
	UINT		m_uReceiveBytes;	// ͳ���յ����ֽ���
	UINT		m_uSendBytes;		// ͳ�Ʒ������ֽ���

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CRect m_ChildRect;

	int m_Row;	//listcurrentset��
	int m_Col;	//listcurrentset��

	// ʵ��
protected:
	HICON m_hIcon;
	CSerialPort m_SerialPort;
	CBrush m_brush;		//��ˢ��������ɫ

	LOGFONT logfont;		//listcontrol�ؼ��������		
	CString msgNotice;		//���ڷ������ַ���

	BYTE m_RxData[2048];
	char m_HexData[2048];	//Hex��������
	char hexData[512];		//����Э��ȷ�� �ֽ���*2
	long m_iRxLen;			//���峤��
	int endFLag;			//��������
	int dfInt;				//����ʱ��ѭ��flag

	CString knowStrData;		//Hex����
	CString groundCuA;			//A��ӵص���
	CString groundCuB;			//B��ӵص���
	CString groundCuC;			//C��ӵص���
	CString groundCuAll;		//�ܽӵص���
	CString CurrentA;			//A�����е���
	CString CurrentB;			//B�����е���
	CString CurrentC;			//C�����е���

	char* m_szWriteBuffer;//д������
	DWORD m_nWriteBufferSize;//д��������С

	CString hexCharToNumber(char HexChar);			//16����ת16�����ֽ�����
	char CombineHexChar(char CharH,char CharL);
	void HexStringFilter(CString &str);
	CString ChangeCharstr2Hexstr(CString Charstr);	
	//ASCII�ַ�����ת16�����ַ�����
	void str2hex(char* str, char* hex);	
	
	CString hex2data(char* hex);					//�ַ�����תCString
	void hexString2Byte(CString& in, BYTE *out);	//16����CStringתBYTE����
	CString kDatatoOrder(CString date);		//k������ת��Ϊָ��
	CString bDatatoOrder(CString date);		//b������ת��Ϊָ��
	CString LookChildString(CString cStr);	//������������
	CString AvoidLarge(CString cstr);		//�����������ݹ���
	void RefreshCom();						//�������ú���
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OrderMessage(WPARAM wParam, LPARAM lParam);	 //�����Ӵ��ڷ��͵���Ϣ
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);	//�����Ȳ����Ϣ
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
	//˫��list�¼�
	afx_msg void OnNMDblclkList4(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_ListCurrentStr;
	
	CEdit m_CurrentEdit;

	afx_msg void OnBnClickedAutodefaultbtn();
	afx_msg void OnNMClickListCurrent(NMHDR* pNMHDR, LRESULT* pResult);
	CRichEditCtrl m_CtrRichEdit;
	CString m_StrRichEdit;
};
