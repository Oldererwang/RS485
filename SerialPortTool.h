
// SerialPortTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSerialPortToolApp:
// �йش����ʵ�֣������ SerialPortTool.cpp
//

class CSerialPortToolApp : public CWinAppEx
{
public:
	CSerialPortToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSerialPortToolApp theApp;