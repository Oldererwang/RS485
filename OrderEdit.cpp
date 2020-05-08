// OrderEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialPortTool.h"
#include "OrderEdit.h"
#include "afxdialogex.h"



// COrderEdit 对话框

IMPLEMENT_DYNAMIC(COrderEdit, CDialogEx)

COrderEdit::COrderEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(COrderEdit::IDD, pParent)
	, m_strOrderEdit1(_T(""))
{
}

COrderEdit::~COrderEdit()
{
}

void COrderEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Orderedit1);
	DDX_Text(pDX, IDC_EDIT1, m_strOrderEdit1);
}

BEGIN_MESSAGE_MAP(COrderEdit, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &COrderEdit::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &COrderEdit::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &COrderEdit::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &COrderEdit::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &COrderEdit::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &COrderEdit::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &COrderEdit::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &COrderEdit::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &COrderEdit::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &COrderEdit::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &COrderEdit::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &COrderEdit::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &COrderEdit::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &COrderEdit::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &COrderEdit::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &COrderEdit::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &COrderEdit::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &COrderEdit::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &COrderEdit::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &COrderEdit::OnBnClickedButton20)
END_MESSAGE_MAP()


// COrderEdit 消息处理程序
//发送端
void COrderEdit::OnBnClickedButton1()	
{
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowTextA(str);

	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
		//(LPARAM)str.GetBuffer(str.GetLength()));
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton2()	
{
	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton3()	
{
	CString str;
	GetDlgItem(IDC_EDIT3)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton4()	
{
	CString str;
	GetDlgItem(IDC_EDIT4)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton5()	
{
	CString str;
	GetDlgItem(IDC_EDIT5)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton6()	
{
	CString str;
	GetDlgItem(IDC_EDIT6)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton7()	
{
	CString str;
	GetDlgItem(IDC_EDIT7)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton8()	
{
	CString str;
	GetDlgItem(IDC_EDIT8)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton9()	
{
	CString str;
	GetDlgItem(IDC_EDIT9)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton10()	
{
	CString str;
	GetDlgItem(IDC_EDIT10)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton11()	
{
	CString str;
	GetDlgItem(IDC_EDIT11)->GetWindowTextA(str);

	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	//(LPARAM)str.GetBuffer(str.GetLength()));
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton12()	
{
	CString str;
	GetDlgItem(IDC_EDIT12)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton13()	
{
	CString str;
	GetDlgItem(IDC_EDIT13)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton14()	
{
	CString str;
	GetDlgItem(IDC_EDIT14)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton15()	
{
	CString str;
	GetDlgItem(IDC_EDIT15)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton16()	
{
	CString str;
	GetDlgItem(IDC_EDIT16)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton17()	
{
	CString str;
	GetDlgItem(IDC_EDIT17)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton18()	
{
	CString str;
	GetDlgItem(IDC_EDIT18)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton19()	
{
	CString str;
	GetDlgItem(IDC_EDIT19)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}
void COrderEdit::OnBnClickedButton20()	
{
	CString str;
	GetDlgItem(IDC_EDIT20)->GetWindowTextA(str);
	//将命令框中的命令字符串形式发送出去
	::SendMessage(this->GetParent()->m_hWnd, WM_ORDERMESSAGE, WPARAM(TRUE) ,(LPARAM)(LPCTSTR)str);
	str.ReleaseBuffer();
}

BOOL COrderEdit::ReadWndPosition()
{
	WINDOWPLACEMENT wp;
	CFile file;
	if (!file.Open(_T("1234.position"), CFile::modeRead))
		return FALSE;
	UINT nByteRead = file.Read(&wp, sizeof(wp));
	if (sizeof(wp) != nByteRead)
		return FALSE;
	if(!::SetWindowPlacement(this->GetSafeHwnd(), &wp))
		return FALSE;
	file.Close();
	return TRUE;
}

BOOL COrderEdit::WriteWndPosition()
{
	WINDOWPLACEMENT wp = { sizeof(wp) };
	::GetWindowPlacement(this->GetSafeHwnd(), &wp);
	CFile file;
	if (!file.Open(_T("1234.position"), CFile::modeCreate | CFile::modeWrite))
		return FALSE;
	file.Write(&wp, sizeof(wp));
	file.Close();
	return TRUE;
}

BOOL COrderEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	ReadWndPosition();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL COrderEdit::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	WriteWndPosition();

	return CDialogEx::DestroyWindow();
}
