#pragma once
#include "afxwin.h"

// COrderEdit �Ի���

class COrderEdit : public CDialogEx
{
	DECLARE_DYNAMIC(COrderEdit)

public:
	COrderEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COrderEdit();

// �Ի�������
	enum { IDD = IDD_EDIT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();

	DECLARE_MESSAGE_MAP()
public:

	CEdit m_Orderedit1;
	CString m_strOrderEdit1;

};
