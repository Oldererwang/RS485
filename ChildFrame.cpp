// ChildFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialPortTool.h"
#include "ChildFrame.h"
#include "afxdialogex.h"


// CChildFrame 对话框

IMPLEMENT_DYNAMIC(CChildFrame, CDialogEx)

CChildFrame::CChildFrame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChildFrame::IDD, pParent)
{
	m_Connected = 0;

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

	ON_WM_DESTROY()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(SetTimeSendBtn, &CChildFrame::OnBnClickedSettimesendbtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(DefalutBtn, &CChildFrame::OnBnClickedDefalutbtn)
	ON_MESSAGE(WM_CHILDMESSAGE, &CChildFrame::OnChildmessage)
END_MESSAGE_MAP()


// CChildFrame 消息处理程序



void CChildFrame::OnBnClickedSendorderbtn()		//发送格式指令
{
	if (m_Connected)
	{
		if (m_propertyGrid.GetProperty(0)->GetValue() != CString(_T("请选择指令")))
		{
			CString str1, str2, str3, str4, str5, str6, strCstr;
			str1 = m_propertyGrid.GetProperty(0)->GetValue();
			str2 = m_propertyGrid.GetProperty(2)->GetValue();
			str3 = m_propertyGrid.GetProperty(3)->GetValue();
			str4 = m_propertyGrid.GetProperty(4)->GetValue();
			str5 = m_propertyGrid.GetProperty(5)->GetValue();
			str6 = m_propertyGrid.GetProperty(6)->GetValue();

			char strChar[18] = { 0 };
			str2hex(str2, strChar);
			strCstr.Format("%s", strChar);
			BYTE orderData[32] = { 0 };

			if ("0xC00055AA" == str1)
			{
				CString strDate = _T("AA5500C014000000") + strCstr + str3 + str4 + str5 + str6;
				for (int i = 2; i < strDate.GetLength(); i += 3)
				{
					strDate.Insert(i, _T(" "));
				}
				int wode = HexStrToHex(strDate, orderData);

				::SendMessage(this->GetParent()->m_hWnd, WM_BYTEMESSAGE, WPARAM(wode), (LPARAM)orderData);
			}

			if ("0xC10055AA" == str1)
			{
				//采样时间10进制转16
				long cStrInt = _ttoi(str3);
				str3 = int10ToStr16(cStrInt,1);

				while (str3.GetLength() < 8)
				{
					str3 = _T("0") + str3;
				}


				CString strDate = _T("AA5500C114000000") + strCstr + str3 + str4 + str5 + str6;
				for (int i = 2; i < strDate.GetLength(); i += 3)
				{
					strDate.Insert(i, _T(" "));
				}
				int wode = HexStrToHex(strDate, orderData);
				::SendMessage(this->GetParent()->m_hWnd, WM_BYTEMESSAGE, WPARAM(wode), (LPARAM)(LPCTSTR)orderData);
			}

			if ("0xC20055AA" == str1)
			{//01020304
				CStringArray cStrArrInt3;
				cStrArrInt3.Add(str3.Mid(2, 2));
				cStrArrInt3.Add(str3.Mid(4, 2));
				cStrArrInt3.Add(str3.Mid(6, 2));
				long cStrInt31 = _ttoi(cStrArrInt3[0]);
				long cStrInt32 = _ttoi(cStrArrInt3[1]);
				long cStrInt33 = _ttoi(cStrArrInt3[2]);
				str3 = int10ToStr16(cStrInt31) + int10ToStr16(cStrInt32) + int10ToStr16(cStrInt33);

				CStringArray cStrArrInt4;
				cStrArrInt4.Add(str4.Mid(2, 2));
				cStrArrInt4.Add(str4.Mid(4, 2));
				cStrArrInt4.Add(str4.Mid(6, 2));
				long cStrInt41 = _ttoi(cStrArrInt4[0]);
				long cStrInt42 = _ttoi(cStrArrInt4[1]);
				long cStrInt43 = _ttoi(cStrArrInt4[2]);
				str4 = int10ToStr16(cStrInt41) + int10ToStr16(cStrInt42) + int10ToStr16(cStrInt43);

				CStringArray cStrArr3;
				cStrArr3.Add(str3.Mid(4, 2));
				cStrArr3.Add(str3.Mid(2, 2));
				cStrArr3.Add(str3.Mid(0, 2));
				str3 = cStrArr3[0] + cStrArr3[1] + cStrArr3[2] + _T("00");

				CStringArray cStrArr4;
				cStrArr4.Add(str4.Mid(4, 2));
				cStrArr4.Add(str4.Mid(2, 2));
				cStrArr4.Add(str4.Mid(0, 2));
				str4 = cStrArr4[0] + cStrArr4[1] + cStrArr4[2] + _T("00");

				CString strDate = _T("AA5500C214000000") + strCstr + str3 + str4 + str5 + str6;
				for (int i = 2; i < strDate.GetLength(); i += 3)
				{
					strDate.Insert(i, _T(" "));
				}
				int wode = HexStrToHex(strDate, orderData);
				::SendMessage(this->GetParent()->m_hWnd, WM_BYTEMESSAGE, WPARAM(wode), (LPARAM)(LPCTSTR)orderData);
			}

			if ("0xC30055AA" == str1)
			{
				CString strDate = _T("AA5500C314000000") + strCstr + str3 + str4 + str5 + str6;
				for (int i = 2; i < strDate.GetLength(); i += 3)
				{
					strDate.Insert(i, _T(" "));
				}
				int wode = HexStrToHex(strDate, orderData);
				::SendMessage(this->GetParent()->m_hWnd, WM_BYTEMESSAGE, WPARAM(wode), (LPARAM)(LPCTSTR)orderData);
			}
			if ("0xC40055AA" == str1)
			{
				CString strDate = _T("AA5500C414000000") + strCstr + str3 + str4 + str5 + str6;
				for (int i = 2; i < strDate.GetLength(); i += 3)
				{
					strDate.Insert(i, _T(" "));
				}
				int wode = HexStrToHex(strDate, orderData);
				::SendMessage(this->GetParent()->m_hWnd, WM_BYTEMESSAGE, WPARAM(wode), (LPARAM)(LPCTSTR)orderData);
			}
		}
	}

	//将命令框中的命令字符串形式发送出去
	//::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	//(LPARAM)str.GetBuffer(str.GetLength()));
	//str.ReleaseBuffer();
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CChildFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//设置字体
	m_editFont.CreatePointFont(140, _T("Times New Roman"));
	m_propertyGrid.SetFont(&m_editFont);
	m_propertyGrid.SetFont(&m_editFont);


	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1);
	pSpin->SetRange32(0, 5000);  //设置值的范围：0-5000
	pSpin->SetBase(10);       //设置基数：十进制

	CString timeStr;
	::GetPrivateProfileString("TimeSet", "time", "1000",timeStr.GetBuffer(10),10, ".\\Defalut.ini");
	timeStr.ReleaseBuffer();
	SetDlgItemText(TimeEdit,_T(timeStr));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CChildFrame::OnStnClickedMfcpropertygridOrder()
{
	// TODO: 在此添加控件通知处理程序代码	
	CString str1, str2, str3, str4, str5, str6;
	str1 = m_propertyGrid.GetProperty(0)->GetValue();
	str2 = m_propertyGrid.GetProperty(2)->GetValue();
	str3 = m_propertyGrid.GetProperty(3)->GetValue();
	str4 = m_propertyGrid.GetProperty(4)->GetValue();
	str5 = m_propertyGrid.GetProperty(5)->GetValue();
	str6 = _T("14000000");

	char wode1[9] = { 0 };
	char wode2[9] = { 0 };
	CString strTemp1 = str1.Mid(8, 2);
	str2hex(str2.Mid(0, 4), wode1);
	str2hex(str2.Mid(4, 4), wode2);
	CString strTemp3 = str3.Mid(8, 2);
	CString wodetian1, wodetian2;
	wodetian1.Format("%s", wode1);
	wodetian2.Format("%s", wode2);

//	m_propertyGrid.GetProperty(6)->AllowEdit(false);

	CString str;	//校验和

	if ( "0xC00055AA" == str1 )	//第一种校验和计算C0
	{
		m_propertyGrid.GetProperty(3)->SetName(_T("预留"));
		m_propertyGrid.GetProperty(4)->SetName(_T("预留"));
		m_propertyGrid.GetProperty(5)->SetName(_T("预留"));
		CString strTT(_T("00000000"));

		while ( str3.GetLength() <8 )
		{
			str3 = _T("0") + str3;
		}
		while (str4.GetLength() < 8)
		{
			str4 = _T("0") + str4;
		}
		m_propertyGrid.GetProperty(3)->SetValue(_T(str3));
		m_propertyGrid.GetProperty(4)->SetValue(_T(str4));

		for (int i = 0; i < 8; i += 2)
		{
			int wode1 = _tcstoul(_T(wodetian1.Mid(i, 2)), NULL, 16);
			int wode2 = _tcstoul(_T(wodetian2.Mid(i, 2)), NULL, 16);
			int wode3 = _tcstoul(_T(str3.Mid(i, 2)), NULL, 16);
			int wode4 = _tcstoul(_T(str4.Mid(i, 2)), NULL, 16);
			int wode5 = _tcstoul(_T(str5.Mid(i, 2)), NULL, 16);

			str = str + int10ToStr16(wode1 + wode2 + wode3 + wode4 + wode5);
		}
		CMFCPropertyGridProperty* pSelected;
		pSelected = m_propertyGrid.GetProperty(6);
		pSelected->SetValue(str);
	}
	if ("0xC10055AA" == str1)	//C1
	{
		m_propertyGrid.GetProperty(3)->SetName(_T("设置采样时间"));
		m_propertyGrid.GetProperty(4)->SetName(_T("预留"));
		m_propertyGrid.GetProperty(5)->SetName(_T("预留"));

		////采样时间10进制转16
		long cStrInt = _ttoi(str3);
		str3 = int10ToStr16(cStrInt,1);

		while ( str3.GetLength() < 8 )
		{
			str3 = _T("0") + str3;
		}

		for (int i = 0; i < 8; i += 2)
		{
			int wode1 = _tcstoul(_T(wodetian1.Mid(i, 2)), NULL, 16);
			int wode2 = _tcstoul(_T(wodetian2.Mid(i, 2)), NULL, 16);
			int wode3 = _tcstoul(_T(str3.Mid(i, 2)), NULL, 16);
			int wode4 = _tcstoul(_T(str4.Mid(i, 2)), NULL, 16);
			int wode5 = _tcstoul(_T(str5.Mid(i, 2)), NULL, 16);

			str = str + int10ToStr16(wode1 + wode2 + wode3 + wode4 + wode5);
			int text = 0;
		}

		CMFCPropertyGridProperty* pSelected;
		pSelected = m_propertyGrid.GetProperty(6);
		pSelected->SetValue(str);
	}

	if ( "0xC20055AA" == str1 )
	{
		m_propertyGrid.GetProperty(3)->SetName(_T("设置年月日"));
		m_propertyGrid.GetProperty(4)->SetName(_T("设置时分秒"));
		m_propertyGrid.GetProperty(5)->SetName(_T("预留"));

		//str3,str4转为16进制
		CStringArray cStrArrInt3;
		cStrArrInt3.Add(str3.Mid(2, 2));
		cStrArrInt3.Add(str3.Mid(4, 2));
		cStrArrInt3.Add(str3.Mid(6, 2));
		long cStrInt31 = _ttoi(cStrArrInt3[0]);
		long cStrInt32 = _ttoi(cStrArrInt3[1]);
		long cStrInt33 = _ttoi(cStrArrInt3[2]);
		str3 = int10ToStr16(cStrInt31) + int10ToStr16(cStrInt32) + int10ToStr16(cStrInt33);

		CStringArray cStrArrInt4;
		cStrArrInt4.Add(str4.Mid(2, 2));
		cStrArrInt4.Add(str4.Mid(4, 2));
		cStrArrInt4.Add(str4.Mid(6, 2));
		long cStrInt41 = _ttoi(cStrArrInt4[0]);
		long cStrInt42 = _ttoi(cStrArrInt4[1]);
		long cStrInt43 = _ttoi(cStrArrInt4[2]);
		str4 = int10ToStr16(cStrInt41) + int10ToStr16(cStrInt42) + int10ToStr16(cStrInt43);

		str3 = _T("00") + str3;
		str4 = _T("00") + str4;

		CStringArray cStrArr3;
		cStrArr3.Add(str3.Mid(6, 2));
		cStrArr3.Add(str3.Mid(4, 2));
		cStrArr3.Add(str3.Mid(2, 2));
		cStrArr3.Add(str3.Mid(0, 2));

		str3 = cStrArr3[0] + cStrArr3[1] + cStrArr3[2] + cStrArr3[3];

		CStringArray cStrArr4;
		cStrArr4.Add(str4.Mid(6, 2));
		cStrArr4.Add(str4.Mid(4, 2));
		cStrArr4.Add(str4.Mid(2, 2));
		cStrArr4.Add(str4.Mid(0, 2));
		str4 = cStrArr4[0] + cStrArr4[1] + cStrArr4[2] + cStrArr4[3];

		for (int i = 0; i < 8; i += 2)
		{
			int wode1 = _tcstoul(_T(wodetian1.Mid(i, 2)), NULL, 16);
			int wode2 = _tcstoul(_T(wodetian2.Mid(i, 2)), NULL, 16);
			int wode3 = _tcstoul(_T(str3.Mid(i, 2)), NULL, 16);
			int wode4 = _tcstoul(_T(str4.Mid(i, 2)), NULL, 16);
			int wode5 = _tcstoul(_T(str5.Mid(i, 2)), NULL, 16);

			str = str + int10ToStr16((wode1 + wode2 + wode3 + wode4 + wode5),0);
		}
		CMFCPropertyGridProperty* pSelected;
		pSelected = m_propertyGrid.GetProperty(6);
		pSelected->SetValue(str);

	}

	if ( "0xC30055AA" == str1 )
	{

		m_propertyGrid.GetProperty(3)->SetName(_T("预留"));
		m_propertyGrid.GetProperty(4)->SetName(_T("预留"));
		m_propertyGrid.GetProperty(5)->SetName(_T("预留"));

	}

	if ( "0xC40055AA" == str1 )
	{

		m_propertyGrid.GetProperty(3)->SetName(_T("预留"));
		m_propertyGrid.GetProperty(4)->SetName(_T("预留"));
		m_propertyGrid.GetProperty(5)->SetName(_T("预留"));

	}


}

void CChildFrame::str2hex(CString str, char* hex)	//数据长度250 这个函数可能需要更改长度
{
	const char* cHex = "0123456789ABCDEF";
	int i = 0;
	for (int j = 0; j < str.GetLength(); j++)
	{
		unsigned int a = (unsigned int)str.GetAt(j);
		hex[i++] = cHex[(a & 0xf0) >> 4];
		hex[i++] = cHex[(a & 0x0f)];
	}
}

CString CChildFrame::int10ToStr16(LONGLONG num)
{
	if (num == 0)
	{
		return _T("00");
	}

	CString str;
	long long Temp = num / 16;
	int left = num % 16;
	if (Temp > 0)
		str += int10ToStr16(Temp);
	if (left < 10)
		str = str + char(left + '0');
	else
		str += char('A' + left - 10);

	return str;
}



CString CChildFrame::int10ToStr16(LONGLONG num,int flag)
{
	if (num == 0)
	{
		return _T("00");
	}

	CString str;
	long long Temp = num / 16;
	int left = num % 16;
	if (Temp > 0)
		str += int10ToStr16(Temp,1);
	if (left < 10)
		str = str + char(left + '0');
	else
		str += char('A' + left - 10);

	if (flag == 0)
	{
		if (str.GetLength() > 2)
		{
			str = str.Right(2);
		}
		return str;
	}

	else
		return str;
}

int CChildFrame::HexStrToHex(CString str, BYTE* data)
{
	int t, t1;
	int rlen = 0, len = str.GetLength();

	if (len == 1)
	{
		char h = str[0];
		t = HexChar(h);
		data[0] = (BYTE)t;
		rlen++;
	}
	//data.SetSize(len/2);

	for (int i = 0; i < len;)
	{
		char l, h = str[i];
		if (h == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		l = str[i];
		t = HexChar(h);
		t1 = HexChar(l);
		if ((t == 16) || (t1 == 16))
			break;
		else
			t = t * 16 + t1;
		i++;
		data[rlen] = (BYTE)t;
		rlen++;
	}
	return rlen;
}

int CChildFrame::HexChar(char c)
{
	if ((c >= '0') && (c <= '9'))
		return c - 0x30;
	else if ((c >= 'A') && (c <= 'F'))
		return c - 'A' + 10;
	else if ((c >= 'a') && (c <= 'f'))
		return c - 'a' + 10;
	else
		return 0x10;
}


void CChildFrame::OnBnClickedSettimesendbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Connected)
	{
		if (m_propertyGrid.GetProperty(0)->GetValue() != CString(_T("请选择指令")))
		{
			CString timeStr;
			GetDlgItem(TimeEdit)->GetWindowText(timeStr);
			::WritePrivateProfileString("TimeSet", "time", _T(timeStr), ".\\Defalut.ini");

			CString btnStr;
			GetDlgItem(SetTimeSendBtn)->GetWindowTextA(btnStr);
			if ("定时发送" == btnStr)
			{
				GetDlgItem(SetTimeSendBtn)->SetWindowTextA("停止发送");
				int timeInt = _ttoi(timeStr);
				SetTimer(1, timeInt, 0);
			}
			else
			{
				GetDlgItem(SetTimeSendBtn)->SetWindowTextA("定时发送");
				KillTimer(1);
			}
		}
	}
}


void CChildFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);

	switch (nIDEvent)
	{
	case 1:
		if (m_Connected)
		{
			OnBnClickedSendorderbtn();	//调用发送按钮
		}
		else
		{
			GetDlgItem(SetTimeSendBtn)->SetWindowTextA("定时发送");
			KillTimer(1);
		}
		break;
	}
}

void CChildFrame::OnBnClickedDefalutbtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CMFCPropertyGridProperty* pProp;
	m_propertyGrid.GetProperty(0)->SetValue("0xC00055AA");
	m_propertyGrid.GetProperty(2)->SetValue("ZTZN0001");
	m_propertyGrid.GetProperty(3)->SetValue("00000000");
	m_propertyGrid.GetProperty(4)->SetValue("00000000");
	m_propertyGrid.GetProperty(5)->SetValue("00000000");
	m_propertyGrid.GetProperty(6)->SetValue("");

}


afx_msg LRESULT CChildFrame::OnChildmessage(WPARAM wParam, LPARAM lParam)
{
	m_Connected = (bool)(WPARAM)wParam;
	return 0;
}
