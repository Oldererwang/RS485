
// SerialPortTool.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "SerialPortTool.h"
#include "ToolDlg.h"

#ifdef _DEBUGca'l'
#define new DEBUG_NEW
#endif


// CSerialPortToolApp

BEGIN_MESSAGE_MAP(CSerialPortToolApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSerialPortToolApp ����

CSerialPortToolApp::CSerialPortToolApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	AfxInitRichEdit2();
}


// Ψһ��һ�� CSerialPortToolApp ����

CSerialPortToolApp theApp;


// CSerialPortToolApp ��ʼ��

BOOL CSerialPortToolApp::InitInstance()
{
// TODO: ���� AfxInitRichEdit2() �Գ�ʼ�� richedit2 �⡣\n"	CWinAppEx::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CToolDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
