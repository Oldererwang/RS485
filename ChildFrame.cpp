// ChildFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SerialPortTool.h"
#include "ChildFrame.h"
#include "afxdialogex.h"


// CChildFrame �Ի���

IMPLEMENT_DYNAMIC(CChildFrame, CDialogEx)

CChildFrame::CChildFrame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChildFrame::IDD, pParent)
{
}

CChildFrame::~CChildFrame()
{
}

void CChildFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCPROPERTYGRID_ORDER, m_propertyGrid);
}


BEGIN_MESSAGE_MAP(CChildFrame, CDialogEx)
	
	ON_BN_CLICKED(SendOrderBtn, &CChildFrame::OnBnClickedSendorderbtn)
	ON_STN_CLICKED(IDC_MFCPROPERTYGRID_ORDER, &CChildFrame::OnStnClickedMfcpropertygridOrder)

END_MESSAGE_MAP()


// CChildFrame ��Ϣ�������



void CChildFrame::OnBnClickedSendorderbtn()		//����ָ��ĸ�ʽ����������
{
	if ( m_propertyGrid.GetProperty(6)->GetValue() != CString(_T("")) )
	{
		CString str1,str2,str3,str4,str5,str6,strCstr;
		str1 = m_propertyGrid.GetProperty(0)->GetValue();
		str2 = m_propertyGrid.GetProperty(2)->GetValue();
		str3 = m_propertyGrid.GetProperty(3)->GetValue();
		str4 = m_propertyGrid.GetProperty(4)->GetValue();
		str5 = m_propertyGrid.GetProperty(5)->GetValue();
		str6 = m_propertyGrid.GetProperty(6)->GetValue();	

		char strChar[18] = {0};
		str2hex(str2,strChar);
		strCstr.Format("%s",strChar);

		if ("0xC00055AA" == str1)
		{
			CString strDate = _T("AA5500C014000000") + strCstr + str3 + str4 + str5 + str6;
			for (int i = 2;i < strDate.GetLength();i+=3)
			{
				strDate.Insert(i,_T(" "));
			}
			::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)strDate);
			(LPARAM)strDate.GetBuffer(strDate.GetLength());
			strDate.ReleaseBuffer();
		}

		if ("0xC10055AA" == str1)
		{
			CString strDate = _T("AA5500C114000000") + strCstr + str3 + str4 + str5 + str6;
			for (int i = 2;i < strDate.GetLength();i+=3)
			{
				strDate.Insert(i,_T(" "));
			}
			::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)strDate);
			(LPARAM)strDate.GetBuffer(strDate.GetLength());
			strDate.ReleaseBuffer();
		}

		if ("0xC20055AA" == str1)
		{
			CString strDate = _T("AA5500C214000000") + strCstr + str3 + str4 + str5 + str6;
			for (int i = 2;i < strDate.GetLength();i+=3)
			{
				strDate.Insert(i,_T(" "));
			}
			::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)strDate);
			(LPARAM)strDate.GetBuffer(strDate.GetLength());
			strDate.ReleaseBuffer();
		}

		if ("0xC30055AA" == str1)
		{
			CString strDate = _T("AA5500C314000000") + strCstr + str3 + str4 + str5 + str6;
			for (int i = 2;i < strDate.GetLength();i+=3)
			{
				strDate.Insert(i,_T(" "));
			}
			::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)strDate);
			(LPARAM)strDate.GetBuffer(strDate.GetLength());
			strDate.ReleaseBuffer();
		}
		if ("0xC40055AA" == str1)
		{
			CString strDate = _T("AA5500C414000000") + strCstr + str3 + str4 + str5 + str6;
			for (int i = 2;i < strDate.GetLength();i+=3)
			{
				strDate.Insert(i,_T(" "));
			}
			::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)strDate);
			(LPARAM)strDate.GetBuffer(strDate.GetLength());
			strDate.ReleaseBuffer();
		}
	}



	//��������е������ַ�����ʽ���ͳ�ȥ
	//::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	//(LPARAM)str.GetBuffer(str.GetLength()));
	//str.ReleaseBuffer();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CChildFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
 
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CChildFrame::OnStnClickedMfcpropertygridOrder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	CString str1,str2,str3,str4,str5,str6;
	str1 = m_propertyGrid.GetProperty(0)->GetValue();
	str2 = m_propertyGrid.GetProperty(2)->GetValue();
	str3 = m_propertyGrid.GetProperty(3)->GetValue();
	str4 = m_propertyGrid.GetProperty(4)->GetValue();
	str5 = m_propertyGrid.GetProperty(5)->GetValue();
	str6 = _T("14000000");

	char wode1[9] = {0};
	char wode2[9] = {0};
	CString strTemp1 = str1.Mid(8,2);
	str2hex(str2.Mid(0,4),wode1);
	str2hex(str2.Mid(4,4),wode2);
	CString strTemp3 = str3.Mid(8,2);
	CString wodetian1,wodetian2;
	wodetian1.Format("%s",wode1);
	wodetian2.Format("%s",wode2);

	CString str;	//У���
	for (int i=0;i<8;i+=2)
	{
		int wode1 = _tcstoul(_T(wodetian1.Mid(i,2)),NULL,16);
		int wode2 = _tcstoul(_T(wodetian2.Mid(i,2)),NULL,16);
		int wode3 = _tcstoul(_T(str3.Mid(i,2)),NULL,16);
		int wode4 = _tcstoul(_T(str4.Mid(i,2)),NULL,16);
		int wode5 = _tcstoul(_T(str5.Mid(i,2)),NULL,16);

		str =str + int10ToStr16(wode1 + wode2 + wode3 + wode4 + wode5);
	}
	CMFCPropertyGridProperty *pSelected;
	pSelected = m_propertyGrid.GetProperty(6);
	pSelected->SetValue(str);

}

void CChildFrame::str2hex(CString str, char* hex)	//���ݳ���250 �������������Ҫ���ĳ���
{
	const char* cHex = "0123456789ABCDEF";
	int i=0;
	for(int j =0; j < str.GetLength(); j++)
	{
		unsigned int a =  (unsigned int) str.GetAt(j);
		hex[i++] = cHex[(a & 0xf0) >> 4];
		hex[i++] = cHex[(a & 0x0f)];
	}
}

CString CChildFrame::int10ToStr16(LONGLONG a)
{
	int y = 0;
	CString s;
	if(a==0)//0�Ƚ����⣬��������
	{
		s = _T("00");
		return s;
	}

	while(a>0)//����0����
	{
		y=a % 16;  //����
		if(y < 10)   //С��10������
		{
			s=char('0'+y)+s;	//�����ַ���ascll�����ַ���ǰ��ƴ��
		}
		else
			s=char('A'-10+y)+s;  //����9��������ABCDE��ʾ
		a=a/16;   
	}
	return s;
}

