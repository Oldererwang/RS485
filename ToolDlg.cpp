
// ToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ToolDlg.h"
#include "OrderEdit.h"
#include "ChildFrame.h"
#include "AboutDlg.h"
#include <Dbt.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolDlg 对话框




CToolDlg::CToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolDlg::IDD, pParent)
	, editIp1(_T(""))
	, editIp2(_T(""))
	, editIp3(_T(""))
	, editIp4(_T(""))
	, m_port(_T(""))
	, m_ListCurrentStr(_T(""))
	, m_StrRichEdit(_T(""))
{
	//初始化
	m_StrSendData = _T("");
	m_StrRichEdit = _T("");
	m_bHexReceive = FALSE;
	m_StrSerialPort = _T("");
	m_StrBaudRate = _T("");
	m_uReceiveBytes = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Connected = 0;	//表明串口连接未连接
	m_iRxLen = 0;		//初始化串口缓冲数组长度
	endFLag = 0;
	dfInt = 0;
	orderFlag = -1;

	for (int i = 0; i < 2048; ++i)
	{
		m_RxData[i] = 0;
	}

	m_Check1 = TRUE;
	m_Check2 = FALSE;
	m_Check3 = FALSE;
	m_Check4 = FALSE;
	m_Check5 = FALSE;
	m_Check6 = FALSE;
	m_Check7 = FALSE;
}

void CToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_BAUD_RATE, m_cboBaudRate);
	DDX_Control(pDX, IDC_CBO_SERIAL_PORT, m_cboSerialPort);
	DDX_Control(pDX, IDC_BTN_OPEN_CLOSE_PORT, m_btnOpenClosePort);

	DDX_CBString(pDX, IDC_CBO_SERIAL_PORT, m_StrSerialPort);
	DDX_CBString(pDX, IDC_CBO_BAUD_RATE, m_StrBaudRate);
	DDX_Control(pDX, IDC_LIST2, m_ListCurrent);
	DDX_Control(pDX, IDC_LIST3, m_ListInfo);
	DDX_Control(pDX, IDC_LIST4, m_currentSet_List);
	DDX_Control(pDX, IDC_COMBO2, m_cboCurrent);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	DDX_Check(pDX, IDC_CHECK4, m_Check4);
	DDX_Check(pDX, IDC_CHECK5, m_Check5);
	DDX_Check(pDX, IDC_CHECK6, m_Check6);
	DDX_Check(pDX, IDC_CHECK7, m_Check7);

	DDX_Text(pDX, EditIP1, editIp1);
	DDX_Text(pDX, EditIp2, editIp2);
	DDX_Text(pDX, EditIP3, editIp3);
	DDX_Text(pDX, EditIP4, editIp4);
	DDX_Text(pDX, IDC_EDITPort, m_port);

	DDX_Control(pDX, IDC_EDIT1, m_CurrentEdit);
	DDX_Control(pDX, IDC_RICHEDIT21, m_CtrRichEdit);
	DDX_Text(pDX, IDC_RICHEDIT21, m_StrRichEdit);
}

BEGIN_MESSAGE_MAP(CToolDlg, CDialog)

	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPEN_CLOSE_PORT, &CToolDlg::OnBnClickedBtnOpenPort)
	ON_BN_CLICKED(IDC_CHK_HEX_SEND, &CToolDlg::OnBnClickedChkHexSend)
	ON_WM_DEVICECHANGE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_COMM_RXCHAR, &CToolDlg::OnComm)
	ON_BN_CLICKED(IDC_BUTTON_Cal, &CToolDlg::OnBnClickedButtonCal)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CToolDlg::OnBnClickedButtonSet)
	ON_MESSAGE(WM_ORDERMESSAGE, &CToolDlg::OrderMessage)
	ON_MESSAGE(WM_BYTEMESSAGE, &CToolDlg::ByteMessage)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolDlg::OnBnClickedDefault)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK1, &CToolDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CToolDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CToolDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CToolDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CToolDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CToolDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CToolDlg::OnBnClickedCheck7)
	ON_EN_CHANGE(EditIP1, &CToolDlg::OnEnChangeEditip1)
	ON_EN_CHANGE(EditIp2, &CToolDlg::OnEnChangeEditip2)
	ON_EN_CHANGE(EditIP3, &CToolDlg::OnEnChangeEditip3)
	ON_EN_CHANGE(EditIP4, &CToolDlg::OnEnChangeEditip4)
	ON_BN_CLICKED(setIpBtn, &CToolDlg::OnBnClickedsetipbtn)
	ON_BN_CLICKED(setPortBtn, &CToolDlg::OnBnClickedsetportbtn)
	ON_EN_CHANGE(IDC_EDITPort, &CToolDlg::OnEnChangeEditport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST4, &CToolDlg::OnNMDblclkList4)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, &CToolDlg::OnNMClickListCurrent)

	ON_WM_DESTROY()

	ON_COMMAND(ID_32772, &CToolDlg::On32772)
	ON_COMMAND(ID_32776, &CToolDlg::OnMenuCOrder)
	ON_COMMAND(ID_32777, &CToolDlg::OnMenuBOrder)
	ON_COMMAND(ID_32774, &CToolDlg::OnTimeSet)
	ON_COMMAND(ID_32775, &CToolDlg::OnMenuShowState)
	ON_COMMAND(4, &CToolDlg::OnMenuOrder)
	ON_COMMAND(ID_32778, &CToolDlg::OnMenuSetDefault)
	ON_COMMAND(ID_32779, &CToolDlg::OnMenuSaveCache)
	ON_COMMAND(ID_32780, &CToolDlg::OnMenuClearReceive)
	ON_COMMAND(ID_32773, &CToolDlg::OnMenuAboutDlg)
END_MESSAGE_MAP()


// CToolDlg 消息处理程序

BOOL CToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	/*这一部分是menu菜单*/
	CMenu* pMenu = new CMenu;
	pMenu->LoadMenu(IDR_MENU1); //载入菜单资源
	SetMenu(pMenu);

	ReadWndPosition();		//载入窗口位置

	//这一块是窗口控件记忆功能，配置ini文件
	CFileFind finder;
	CString bundrateStr, IpStr, portStr;
	bool ifFind = finder.FindFile(_T(".\\Defalut.ini"));
	if (!ifFind)	//ini文件初始化
	{
		::WritePrivateProfileString("IDC_CBO_BAUD_RATE", "BundRate", "115200", ".\\Defalut.ini");
		::WritePrivateProfileString("IpAddress", "IP", "192.168.000.001", ".\\Defalut.ini");
		::WritePrivateProfileString("Port", "port","6666", ".\\Defalut.ini");
		::WritePrivateProfileString("TimeSet", "time", "1000", ".\\Defalut.ini");
	}

	//得到ini文件中的值
	::GetPrivateProfileString("IDC_CBO_BAUD_RATE", "BundRate", "115200", bundrateStr.GetBuffer(20), 20, ".\\Defalut.ini");
	::GetPrivateProfileString("IpAddress", "IP", "192.168.000.001",IpStr.GetBuffer(20),20, ".\\Defalut.ini");
	::GetPrivateProfileString("Port", "port", "6666",portStr.GetBuffer(10),10, ".\\Defalut.ini");
	bundrateStr.ReleaseBuffer();
	IpStr.ReleaseBuffer();
	portStr.ReleaseBuffer();
	//从ini文件读取设置
	GetDlgItem(IDC_EDITPort)->SetWindowTextA(portStr);

	int pointFind = IpStr.Find(".");
	CString IpStrr1 = IpStr.Left(pointFind);
	IpStr.Delete(0,pointFind+1);
	pointFind = IpStr.Find(".");
	CString IpStrr2 = IpStr.Left(pointFind);
	IpStr.Delete(0,pointFind+1);
	pointFind = IpStr.Find(".");
	CString IpStrr3 = IpStr.Left(pointFind);
	IpStr.Delete(0,pointFind+1);
	CString IpStrr4 = IpStr;
	GetDlgItem(EditIP1)->SetWindowTextA(IpStrr1);
	GetDlgItem(EditIp2)->SetWindowTextA(IpStrr2);
	GetDlgItem(EditIP3)->SetWindowTextA(IpStrr3);
	GetDlgItem(EditIP4)->SetWindowTextA(IpStrr4);

	/*这一部分是改变控件内字体的大小*/
	m_editFont.CreatePointFont(150, _T("Times New Roman"));
	m_currentSet_List.SetFont(&m_editFont);
	m_CurrentEdit.SetFont(&m_editFont);

	CFont  pfont;
	pfont.CreatePointFont(75, _T("微软雅黑"));

	static CFont font1;
	static CFont font2;
	static CFont font3;

	pfont.GetLogFont(&logfont);
	logfont.lfHeight = logfont.lfHeight * 1.7;		//这里可以修改字体的高比例
	logfont.lfWidth = logfont.lfWidth * 1.7;			//这里可以修改字体的宽比例
	font1.CreateFontIndirect(&logfont);
	m_ListCurrent.SetFont(&font1);

	m_ListInfo.SetFont(&font1);

	pfont.GetLogFont(&logfont);
	logfont.lfHeight = logfont.lfHeight * 4441.7;		//这里可以修改字体的高比例
	logfont.lfWidth = logfont.lfWidth * 1.6;			//这里可以修改字体的宽比例
	font2.CreateFontIndirect(&logfont);

	pfont.GetLogFont(&logfont);
	logfont.lfHeight = logfont.lfHeight * 1.2;		//这里可以修改字体的高比例
	logfont.lfWidth = logfont.lfWidth * 1.2;			//这里可以修改字体的宽比例
	font3.CreateFontIndirect(&logfont);
	GetDlgItem(IDC_RICHEDIT21)->SetFont(&font3);

	font1.Detach();
	font2.Detach();
	font3.Detach();
	
	/*这一部分是TAB窗口*/
	//m_tab.InsertItem(0,_T("第一页"));  
	////m_Tab.InsertItem(1,_T(“第二页”));
	//m_ChildFrame.Create( IDD_DIALOG1 , this ); 
	//m_tab.SetCurSel(0);

	/*这一部分是新建子窗口ChildFrame*/
	m_ChildFrame = new CChildFrame;
	m_ChildFrame->Create(IDD_DIALOG1, this);
	GetDlgItem(IDC_STATIC_ChildArea)->GetWindowRect(&m_ChildRect);
	ScreenToClient(m_ChildRect);
	m_ChildFrame->MoveWindow(m_ChildRect);
	GetDlgItem(IDC_STATIC_ChildArea)->ShowWindow(HIDE_WINDOW);
	m_ChildFrame->ShowWindow(SW_HIDE);

	/*ChildFrame子窗口初始化*/
	CRect rectPro;
	m_ChildFrame->m_propertyGrid.GetHeaderCtrl().GetClientRect(&rectPro);
	m_ChildFrame->m_propertyGrid.EnableHeaderCtrl(TRUE);  //使用表头   
	m_ChildFrame->m_propertyGrid.SetVSDotNetLook();  //使用样式   
	m_ChildFrame->m_propertyGrid.MarkModifiedProperties(); //着重显示更改过的部分

	HDITEM a;
	a.cxy = rectPro.Width() / 3;
	a.mask = HDI_WIDTH;
	m_ChildFrame->m_propertyGrid.GetHeaderCtrl().SetItem(0, new HDITEM(a));

	m_ChildFrame->m_propertyGrid.EnableHeaderCtrl(TRUE, _T("标识"), _T("报文"));
	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty(
		_T("指令"),
		_T("请选择指令"),
		_T("这是StartFlag"));
	pProp1->AddOption(_T("0xC00055AA"));
	pProp1->AddOption(_T("0xC10055AA"));
	pProp1->AddOption(_T("0xC20055AA"));
	pProp1->AddOption(_T("0xC30055AA"));
	pProp1->AddOption(_T("0xC40055AA"));
	pProp1->AllowEdit(FALSE);  //不允许对选项进行编辑
	m_ChildFrame->m_propertyGrid.AddProperty(pProp1);
	CMFCPropertyGridProperty* pProp2 = new CMFCPropertyGridProperty(
		_T("数据长度"),
		_T("20"),
		_T("这是Len"));
	pProp2->AllowEdit(FALSE);
	m_ChildFrame->m_propertyGrid.AddProperty(pProp2);
	CMFCPropertyGridProperty* pProp3 = new CMFCPropertyGridProperty(
		_T("设备ID"),
		_T("ZTZN0001"),
		_T("这是设备ID"));
	m_ChildFrame->m_propertyGrid.AddProperty(pProp3);
	CMFCPropertyGridProperty* pProp4 = new CMFCPropertyGridProperty(
		_T("数据内容"),
		_T("00000000"),
		_T("预留1"));
	m_ChildFrame->m_propertyGrid.AddProperty(pProp4);
	CMFCPropertyGridProperty* pProp5 = new CMFCPropertyGridProperty(
		_T("数据内容"),
		_T("00000000"),
		_T("预留2"));
	m_ChildFrame->m_propertyGrid.AddProperty(pProp5);
	CMFCPropertyGridProperty* pProp6 = new CMFCPropertyGridProperty(
		_T("数据内容"),
		_T("00000000"),
		_T("预留3"));
	m_ChildFrame->m_propertyGrid.AddProperty(pProp6);
	CMFCPropertyGridProperty* pProp7 = new CMFCPropertyGridProperty(
		_T("校验和"),
		_T(""),
		_T(""));
	m_ChildFrame->m_propertyGrid.AddProperty(pProp7);

	//CFont  *aFont = this->GetDlgItem(IDC_BTN_OPEN_CLOSE_PORT)->GetFont(); 
	//aFont.CreatePointFont( 100 ,  _T("宋体"));
	//m_ChildFrame->m_propertyGrid.SetFont(&aFont);	//设置m_propertyGrid字体

	m_brush.CreateSolidBrush(RGB(0, 255, 0));	//生成绿色刷子
	//找到整个窗口大小位置坐标r1
	CRect rt1;
	this->GetWindowRect(&rt1);

	CRect rt2;
	GetDlgItem(setIpBtn)->GetWindowRect(&rt2);

	//找到m_ListCurrent相对窗口左上角位置r2
	CRect rt3;
	m_ListCurrent.GetWindowRect(rt3);
	ScreenToClient(rt3);

	/*这一部分是创建命令子窗口并隐藏*/
	orderEditDlg = new COrderEdit;
	orderEditDlg->Create(IDD_EDIT_DIALOG, this);
	orderEditDlg->SetWindowPos(&CWnd::wndTop, (rt1.right), rt3.top + 10, 0, 0, SWP_NOSIZE);	//设置子窗口位置

	//编辑框指定文本
	orderEditDlg->SetDlgItemText(IDC_EDIT1, ">DEVICE_ID:ZTZN0001");
	orderEditDlg->SetDlgItemText(IDC_EDIT2, ">TIME:2019-10-20@20:30:00");
	orderEditDlg->SetDlgItemText(IDC_EDIT3, ">DEVICE_IP:192.168.001.100");
	orderEditDlg->SetDlgItemText(IDC_EDIT4, ">DEVICE_PORT:6000");
	orderEditDlg->SetDlgItemText(IDC_EDIT5, ">DEVICE_MAC:AA:BB:CC:DD:EE:FF");
	orderEditDlg->SetDlgItemText(IDC_EDIT6, ">DEVICE_GATEWAY:192.168.001.001");
	orderEditDlg->SetDlgItemText(IDC_EDIT7, ">DEVICE_MASK:255.255.255.000");
	orderEditDlg->SetDlgItemText(IDC_EDIT8, ">SERVER_IP:192.168.001.110");
	orderEditDlg->SetDlgItemText(IDC_EDIT9, ">SERVER_PORT:6002");
	orderEditDlg->SetDlgItemText(IDC_EDIT10, ">UPLOAD:30");
	orderEditDlg->SetDlgItemText(IDC_EDIT11, ">SAMPLTIME:300");
	orderEditDlg->SetDlgItemText(IDC_EDIT12, ">CALIB[n]:10000|-0000|10000|-0000|10000");
	orderEditDlg->SetDlgItemText(IDC_EDIT13, ">RATIO:040|040|040|040|040|040|040|040");
	orderEditDlg->SetDlgItemText(IDC_EDIT14, ">REBOOT");
	orderEditDlg->SetDlgItemText(IDC_EDIT15, ">SAVE");
	orderEditDlg->SetDlgItemText(IDC_EDIT16, ">SHOW_STAT");
	orderEditDlg->SetDlgItemText(IDC_EDIT17, ">SHOW_CALIB");
	//orderEditDlg->SetDlgItemText(IDC_EDIT18,"");
	orderEditDlg->SetDlgItemText(IDC_EDIT19, ">UPDATE");
	//orderEditDlg->SetDlgItemText(IDC_EDIT20,"");

	orderEditDlg->ShowWindow(SW_HIDE);
	m_CurrentEdit.ShowWindow(SW_HIDE);

	CRect rect1;
	m_ListCurrent.GetClientRect(&rect1);			// 获取m_ListCurrent的位置和大小   
	// 为列表视图控件添加全行选中和栅格风格   
	m_ListInfo.SetExtendedStyle(m_ListInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCurrent.SetExtendedStyle(m_ListCurrent.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rect2;
	m_currentSet_List.GetClientRect(&rect2);		// 获取m_currentSet_List的位置和大小   
	m_currentSet_List.SetExtendedStyle(m_currentSet_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_ListCurrent.ModifyStyle(0, LVS_NOCOLUMNHEADER);//不显示标题

	// 为列表视图控件添加列
	m_ListInfo.InsertColumn(0, _T("设备ID"), LVCFMT_LEFT, rect1.Width() * 7 / 32, 0);
	m_ListInfo.InsertColumn(1, _T("系统日期"), LVCFMT_LEFT, rect1.Width() * 9 / 32, 1);
	m_ListInfo.InsertColumn(2, _T("运行时间"), LVCFMT_LEFT, rect1.Width() / 4, 2);
	m_ListInfo.InsertColumn(3, _T("本机电压"), LVCFMT_LEFT, rect1.Width() / 4, 3);
	m_ListCurrent.InsertColumn(0, _T(""), LVCFMT_LEFT, rect1.Width() / 5, 0);
	m_ListCurrent.InsertColumn(1, _T("通道电流名称"), LVCFMT_CENTER, rect1.Width() * 2 / 5, 1);
	m_ListCurrent.InsertColumn(2, _T("电流大小(A)"), LVCFMT_CENTER, rect1.Width() * 2 / 5, 2);

	m_currentSet_List.InsertColumn(0, _T(""), LVCFMT_LEFT, rect2.Width() / 6, 0);
	m_currentSet_List.InsertColumn(1, _T("0A"), LVCFMT_CENTER, rect2.Width() / 6, 1);
	m_currentSet_List.InsertColumn(2, _T("3.5A"), LVCFMT_CENTER, rect2.Width() / 3, 2);
	m_currentSet_List.InsertColumn(3, _T("100A"), LVCFMT_CENTER, rect2.Width() / 3, 3);

	m_currentSet_List.InsertItem(0, _T(""));
	m_currentSet_List.InsertItem(1, _T(""));
	m_currentSet_List.InsertItem(2, _T(""));
	m_currentSet_List.InsertItem(3, _T(""));
	m_currentSet_List.InsertItem(4, _T(""));
	m_currentSet_List.InsertItem(5, _T(""));
	m_currentSet_List.InsertItem(6, _T(""));
	m_currentSet_List.SetItemText(0, 0, _T("通道1:"));
	m_currentSet_List.SetItemText(1, 0, _T("通道2:"));
	m_currentSet_List.SetItemText(2, 0, _T("通道3:"));
	m_currentSet_List.SetItemText(3, 0, _T("通道4:"));
	m_currentSet_List.SetItemText(4, 0, _T("通道5:"));
	m_currentSet_List.SetItemText(5, 0, _T("通道6:"));
	m_currentSet_List.SetItemText(6, 0, _T("通道7:"));

	m_ListInfo.InsertItem(0, _T(""));

	m_ListCurrent.InsertItem(0, _T("通道1:"));
	m_ListCurrent.InsertItem(1, _T("通道2:"));
	m_ListCurrent.InsertItem(2, _T("通道3:"));
	m_ListCurrent.InsertItem(3, _T("通道4:"));
	m_ListCurrent.InsertItem(4, _T("通道5:"));
	m_ListCurrent.InsertItem(5, _T("通道6:"));
	m_ListCurrent.InsertItem(6, _T("通道7:"));

	//m_ListCurrent.SetItemText(0, 1, _T("A相接地电流"));
	//m_ListCurrent.SetItemText(1, 1, _T("B相接地电流"));
	//m_ListCurrent.SetItemText(2, 1, _T("C相接地电流"));
	//m_ListCurrent.SetItemText(3, 1, _T(" 总接地电流"));
	//m_ListCurrent.SetItemText(4, 1, _T("A相运行电流"));
	//m_ListCurrent.SetItemText(5, 1, _T("B相运行电流"));
	//m_ListCurrent.SetItemText(6, 1, _T("C相运行电流"));
	m_btnOpenClosePort.SetWindowText(_T("打开串口"));

	if (m_bHexReceive)
		GetDlgItem(IDC_RICHEDIT21)->ModifyStyle(0, ES_UPPERCASE, 0);


	UINT uBaudRate[] = { 300,600,1200,2400,4800,9600,14400,19200,38400,56000,57600,115200,230400,460800,921600 };
	CString Parity[] = { _T("None"),_T("Odd"),_T("Even"),_T("Mark"),_T("Space") };


	CString StrTemp;

	// 显示波特率
	for (int i = 0; i < sizeof(uBaudRate) / sizeof(UINT); ++i)
	{
		StrTemp.Format("%d", uBaudRate[i]);
		m_cboBaudRate.AddString(LPCTSTR(StrTemp));
	}
	StrTemp.Format("%d", 115200);
	m_cboBaudRate.SetCurSel(m_cboBaudRate.FindString(0, StrTemp));

	m_cboBaudRate.SetCurSel(m_cboBaudRate.FindString(0, _T(bundrateStr)));

	// 列出系统所有的串口
	for (int i = 1; i < 200; ++i)
	{
		if (m_SerialPort.InitPort(this, i)) {
			StrTemp.Format("COM%d", i);
			m_cboSerialPort.AddString(LPCTSTR(StrTemp));
		}
	}
	if (m_cboSerialPort.GetCount())
	{
		m_cboSerialPort.SetCurSel(0);
	}

	//电流校准目标COMBOX
	m_cboCurrent.InsertString(0, _T("0A"));
	m_cboCurrent.InsertString(1, _T("3.5A"));
	m_cboCurrent.InsertString(2, _T("100A"));
	m_cboCurrent.SetCurSel(0);

	//

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CToolDlg::RefreshCom()
{
	CString StrTemp;
	for (int i = 1; i < 200; ++i)
	{
		if (m_SerialPort.InitPort(this, i)) {
			StrTemp.Format("COM%d", i);
			m_cboSerialPort.AddString(LPCTSTR(StrTemp));
		}
	}
	if (m_cboSerialPort.GetCount())
	{
		m_cboSerialPort.SetCurSel(0);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。


void CToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		// 创建内存缓存DC
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		CBitmap bufferMemBitmap;
		CRect rect;
		GetClientRect(&rect);
		bufferMemBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		memDC.SelectObject(&bufferMemBitmap);
		CBrush whiteBrush;
		whiteBrush.CreateSolidBrush(RGB(255, 255, 255));
		memDC.FillRect(CRect(0, 0, rect.Width(), rect.Height()), &whiteBrush);

		// 使用memDC做绘图操作
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		//CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		memDC.DrawIcon(x, y, m_hIcon);

		// 将内存缓冲DC拷贝至当前DC
		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		bufferMemBitmap.DeleteObject();
		memDC.DeleteDC();


		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		//// 使图标在工作区矩形中居中
		//int cxIcon = GetSystemMetrics(SM_CXICON);
		//int cyIcon = GetSystemMetrics(SM_CYICON);
		//CRect rect;
		//GetClientRect(&rect);
		//int x = (rect.Width() - cxIcon + 1) / 2;
		//int y = (rect.Height() - cyIcon + 1) / 2;

		//// 绘制图标
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CToolDlg::OnBnClickedBtnOpenPort()	//打开串口
{
	// TODO: 在此添加控件通知处理程序代码
	CString tmstr;
	GetDlgItem(IDC_BTN_OPEN_CLOSE_PORT)->GetWindowText(tmstr);
	if ("打开串口" == tmstr)
	{
		CString portnrStr, str;
		UINT portnr;
		UINT baud;

		m_cboSerialPort.GetLBText(m_cboSerialPort.GetCurSel(), portnrStr);
		for (int i = 3; i < portnrStr.GetLength(); i++)
		{
			char ch = portnrStr[i];
			portnr = (UINT)ch;
			str += ch;
		}
		portnr = atoi(str);

		if (!m_Connected)
		{
			//110;300;600;1200;2400;4800;9600;14400;19200;28800;38400;56000;57600;115200;128000;256000;
			switch (m_cboBaudRate.GetCurSel())
			{
			case 0:
				baud = 300;
				break;
			case 1:
				baud = 600;
				break;
			case 2:
				baud = 1200;
				break;
			case 3:
				baud = 2400;
				break;
			case 4:
				baud = 4800;
				break;
			case 5:
				baud = 9600;
				break;
			case 6:
				baud = 14400;
				break;
			case 7:
				baud = 19200;
				break;
			case 8:
				baud = 38400;
				break;
			case 9:
				baud = 56000;
				break;
			case 10:
				baud = 57600;
				break;
			case 11:
				baud = 115200;
				break;
			default:
				break;
			}
			//None无;Odd奇;Even偶;Mark 1;Space 0;

			BOOL IsOpen = m_SerialPort.InitPort(this, portnr, baud, 'N', 8, 1, EV_RXCHAR | EV_RXFLAG, 2048, 1, 1, 1, 1, 1);
			//判断串口是否打开

			if (IsOpen)	//如果成功打开
			{
				GetDlgItem(IDC_CBO_BAUD_RATE)->GetWindowText(cboStr);
				SetDlgItemText(IDC_BTN_OPEN_CLOSE_PORT, _T("关闭串口"));
				GetDlgItem(IDC_CBO_SERIAL_PORT)->EnableWindow(FALSE);	//控件变灰
				GetDlgItem(IDC_CBO_BAUD_RATE)->EnableWindow(FALSE);

				m_CtrRichEdit.SetSel(-1, -1);
				m_CtrRichEdit.ReplaceSel(_T("成功打开串口！\r\n"));
				//MessageBox(_T(" 成功打开串口！"),_T("提示"));
				m_Connected = 1;

				//发送消息给B类
				::SendMessage(m_ChildFrame->GetSafeHwnd(), WM_CHILDMESSAGE, WPARAM(m_Connected), 0);
			}
			else
			{
				AfxMessageBox(_T("打开串口失败，请重新打开！"));
			}

			if (m_SerialPort.StartMonitoring())
			{
				//AfxMessageBox(_T("串口线程已成功启动"));
			}
			else
			{
				AfxMessageBox(_T("串口线程启动失败，请检查原因！"));
			}
		}
	}
	else
	{
		if (m_Connected)
		{
			SetDlgItemText(IDC_BTN_OPEN_CLOSE_PORT, _T("打开串口"));
			GetDlgItem(IDC_CBO_SERIAL_PORT)->EnableWindow(TRUE);
			GetDlgItem(IDC_CBO_BAUD_RATE)->EnableWindow(TRUE);

			m_SerialPort.ClosePort();
			m_Connected = 0;

			//发送消息给B类
			::SendMessage(m_ChildFrame->GetSafeHwnd(), WM_CHILDMESSAGE, WPARAM(m_Connected), 0);

		}
	}

}

void CToolDlg::OnBnClickedChkAutoSendData()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void CToolDlg::OnBnClickedChkHexSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CToolDlg::OnBnClickedChkReceive()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bHexReceive)
		GetDlgItem(IDC_RICHEDIT21)->ModifyStyle(0, ES_UPPERCASE, 0);
	else
		GetDlgItem(IDC_RICHEDIT21)->ModifyStyle(0, ES_UPPERCASE, 0);
	UpdateData(FALSE);
}

void CToolDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)		//nIDEvent 为定时器事件ID，1，2，3  
	{
	case 1:
	{
		CString cStr, order;
		cStr.Format("%d", dfInt);
		if (dfInt < 7)
		{
			order = _T(">CALIB[") + _T(cStr) + _T("]:10000|+0000|10000|+0000|10000\r\n");
		}
		//	else
		//	order = _T(">SHOW_CALIB\r\n");

		//MessageBox(_T("1123123"));
		m_SerialPort.WriteToPort(order.GetBuffer(order.GetLength()));
		dfInt++;
		if (7 == dfInt)
		{
			dfInt = 0;
			KillTimer(1);
		}
	}
	break;

	}
	CDialog::OnTimer(nIDEvent);
}

LPARAM CToolDlg::OnComm(WPARAM ch, LPARAM port)
{
	/************************************************************************/
	/* B类数据结构解析                                                         */
	/************************************************************************/
	if (_T("57600") == cboStr)
	{
		CString strTemp; 
		strTemp.Format("%d", m_iRxLen);
		m_RxData[m_iRxLen] = ch;	//缓冲字符数组

		msgNotice += char(ch);
		m_iRxLen++;				//控制行数
		char m_HeadData[8] = { 0,0,0,0,0,0,0,0 };
		CString headData;

		//找出指令 然后再进行解析
		if (9 == m_iRxLen)
		{
			for (int i = 0; i < 8; i++)
			{
				m_HeadData[i] = m_RxData[i];
			}

			str2hex(m_HeadData, hexData , 8);
			headData = hex2data(hexData);

			if (-1 == orderFlag)
			{
				if (_T("AA5500A0") == headData.Left(8))	//0xA000
				{
					orderFlag = 0; 
					CString	sum = headData.Mid(8, 2);
					int sumInt1 = _tcstoul(_T(sum), NULL, 16);
					sum.Format("%d", sumInt1);

					m_CtrRichEdit.SetSel(-1, -1);
					m_CtrRichEdit.ReplaceSel(_T("0xA000指令 数据长度："));
					m_CtrRichEdit.ReplaceSel(_T(sum) + _T("\r\n"));

				}
				else if (_T("AA5500A1") == headData.Left(8))	//0xA100
				{	
					orderFlag = 1;
					CString	sum = headData.Mid(8, 2);
					int sumInt1 = _tcstoul(_T(sum), NULL, 16);
					sum.Format("%d", sumInt1);

					m_CtrRichEdit.SetSel(-1, -1);
					m_CtrRichEdit.ReplaceSel(_T("0xA100指令 数据长度："));
					m_CtrRichEdit.ReplaceSel(_T(sum) + _T("\r\n"));
				}
				else if (_T("AA5500A2") == headData.Left(8))	//0xA200
				{
					orderFlag = 2;
					CString	sum = headData.Mid(8, 2);
					int sumInt1 = _tcstoul(_T(sum), NULL, 16);
					sum.Format("%d", sumInt1);
					m_CtrRichEdit.SetSel(-1, -1);
					m_CtrRichEdit.ReplaceSel(_T("0xA200指令 数据长度："));
					m_CtrRichEdit.ReplaceSel(_T(sum) + _T("\r\n"));
				}
				else if (_T("AA5500A3") == headData.Left(8))	//0xA300
				{
					orderFlag = 3;
					CString	sum = headData.Mid(8, 2);
					int sumInt1 = _tcstoul(_T(sum), NULL, 16);
					sum.Format("%d", sumInt1);
					m_CtrRichEdit.SetSel(-1, -1);
					m_CtrRichEdit.ReplaceSel(_T("0xA300指令 数据长度："));
					m_CtrRichEdit.ReplaceSel(_T(sum) + _T("\r\n"));
				}
				else if (_T("AA5500A4") == headData.Left(8))	//0xA400
				{
					orderFlag = 4;
					CString	sum = headData.Mid(8, 2);
					int sumInt1 = _tcstoul(_T(sum), NULL, 16);
					sum.Format("%d", sumInt1);
					m_CtrRichEdit.SetSel(-1, -1);
					m_CtrRichEdit.ReplaceSel(_T("0xA400指令 数据长度："));
					m_CtrRichEdit.ReplaceSel(_T(sum) + _T("\r\n"));
				}
			}
		}

		//解析
		if (0 == orderFlag)
		{
			if (m_iRxLen == 148)
			{
				//解析设备ID
				m_CtrRichEdit.SetSel(-1, -1);
				m_CtrRichEdit.ReplaceSel(_T("设备ID："));
				m_CtrRichEdit.ReplaceSel(msgNotice.Mid(8, 8) + _T("\r\n"));

				for (int i = 0; i < 132; i++)
				{
					m_HexData[i] = m_RxData[i + 16];
				}
				str2hex(m_HexData, hexData , 264 );		//维护时str2hex可能需要更改参数
				knowStrData = hex2data(hexData);	//得到需要解析的字符串knowStrData

				//解析日期和时间
				CString time1 = knowStrData.Mid(0, 2);; 	//时间	
				CString time2 = knowStrData.Mid(2, 2);
				CString time3 = knowStrData.Mid(4, 2);
				int timeInt1 = _tcstoul(_T(time1), NULL, 16);
				int timeInt2 = _tcstoul(_T(time2), NULL, 16);
				int timeInt3 = _tcstoul(_T(time3), NULL, 16);
				time1.Format("%d", timeInt1);
				time2.Format("%d", timeInt2);
				time3.Format("%d", timeInt3);
				CString systemTime = time3 + _T(":") + time2 + _T(":") + time1;

				CString date1 = knowStrData.Mid(8, 2);; 	//日期	
				CString date2 = knowStrData.Mid(10, 2);
				CString date3 = knowStrData.Mid(12, 2);
				int dateInt1 = _tcstoul(_T(date1), NULL, 16);
				int dateInt2 = _tcstoul(_T(date2), NULL, 16);
				int dateInt3 = _tcstoul(_T(date3), NULL, 16);
				date1.Format("%d", dateInt1);
				date2.Format("%d", dateInt2);
				date3.Format("%d", dateInt3);
				CString systemDate = _T("20") + date3 + _T("-") + date2 + _T("-") + date1;
				
				m_CtrRichEdit.SetSel(-1, -1);
				m_CtrRichEdit.ReplaceSel(_T("日期时间："));
				m_CtrRichEdit.ReplaceSel(systemDate + _T("  ") + systemTime + _T("\r\n"));

				//解析运行时长，电压和电流
				CString strRunTime;
				CString strLocalVbat;
				CString strGroundCuA;
				CString strGroundCuB;
				CString strGroundCuC;
				CString strGroundCuAll;
				CString strCurrentA;
				CString strCurrentB;
				CString strCurrentC;

				BYTE byteLocalVbat[5];
				BYTE byteGroundCuA[5];
				BYTE byteGroundCuB[5];
				BYTE byteGroundCuC[5];
				BYTE byteGroundCuAll[5];
				BYTE byteCurrentA[5];
				BYTE byteCurrentB[5];
				BYTE byteCurrentC[5];

				float fLocalVbat;
				float fGroundCuA;
				float fGroundCuB;
				float fGroundCuC;
				float fGroundCuAll;
				float fCurrentA;
				float fCurrentB;
				float fCurrentC;

				//16位CString转换为字节数组
				hexString2Byte(knowStrData.Mid(80, 8), byteLocalVbat);	//电池电压
				hexString2Byte(knowStrData.Mid(16, 8), byteGroundCuA);
				hexString2Byte(knowStrData.Mid(24, 8), byteGroundCuB);
				hexString2Byte(knowStrData.Mid(32, 8), byteGroundCuC);
				hexString2Byte(knowStrData.Mid(40, 8), byteGroundCuAll);
				hexString2Byte(knowStrData.Mid(48, 8), byteCurrentA);
				hexString2Byte(knowStrData.Mid(56, 8), byteCurrentB);
				hexString2Byte(knowStrData.Mid(64, 8), byteCurrentC);

				//防止越界 维护时修改
				byteLocalVbat[4] = '\0';
				byteGroundCuA[4] = '\0';
				byteGroundCuB[4] = '\0';
				byteGroundCuC[4] = '\0';
				byteGroundCuAll[4] = '\0';
				byteCurrentA[4] = '\0';
				byteCurrentB[4] = '\0';
				byteCurrentC[4] = '\0';

				//字节数组转成浮点数
				memcpy(&fLocalVbat, &byteLocalVbat[0], 4);
				memcpy(&fGroundCuA, &byteGroundCuA[0], 4);
				memcpy(&fGroundCuB, &byteGroundCuB[0], 4);
				memcpy(&fGroundCuC, &byteGroundCuC[0], 4);
				memcpy(&fGroundCuAll, &byteGroundCuAll[0], 4);
				memcpy(&fCurrentA, &byteCurrentA[0], 4);
				memcpy(&fCurrentB, &byteCurrentB[0], 4);
				memcpy(&fCurrentC, &byteCurrentC[0], 4);

				//浮点数转回CString
				strLocalVbat.Format("%.4lf", fLocalVbat);
				strGroundCuA.Format("%.4lf", fGroundCuA);
				strGroundCuB.Format("%.4lf", fGroundCuB);
				strGroundCuC.Format("%.4lf", fGroundCuC);
				strGroundCuAll.Format("%.4lf", fGroundCuAll);
				strCurrentA.Format("%.4lf", fCurrentA);
				strCurrentB.Format("%.4lf", fCurrentB);
				strCurrentC.Format("%.4lf", fCurrentC);

				//解析时间
				CString tm1 = knowStrData.Mid(168, 2);
				CString tm2 = knowStrData.Mid(170, 2);
				CString tm3 = knowStrData.Mid(172, 2);
				CString tm4 = knowStrData.Mid(174, 2);

				int value = _tcstoul(_T(tm4 + tm3 + tm2 + tm1), NULL, 16);
				CString sH, sM, sS;
				sH.Format("%d", value / 3600);
				sM.Format("%d", (value - (value / 3600) * 3600) / 60);
				sS.Format("%d", (value % 3600) % 60);
				if (sH.GetLength() < 2)
					sH = "0" + sH;
				if (sM.GetLength() < 2)
					sM = "0" + sM;
				if (sS.GetLength() < 2)
					sS = "0" + sS;
				strRunTime = sH + ":" + sM + ":" + sS;

				//Info表放数据
				m_ListInfo.SetItemText(0, 0, msgNotice.Mid(8, 8));
				m_ListInfo.SetItemText(0, 1, systemDate);
				m_ListInfo.SetItemText(0, 2, strRunTime);
				m_ListInfo.SetItemText(0, 3, strLocalVbat);

				//m_ListCurrent表放数据
				m_ListCurrent.SetItemText(0, 1, _T("A相接地电流"));
				m_ListCurrent.SetItemText(1, 1, _T("B相接地电流"));
				m_ListCurrent.SetItemText(2, 1, _T("C相接地电流"));
				m_ListCurrent.SetItemText(3, 1, _T(" 总接地电流"));
				m_ListCurrent.SetItemText(4, 1, _T("A相运行电流"));
				m_ListCurrent.SetItemText(5, 1, _T("B相运行电流"));
				m_ListCurrent.SetItemText(6, 1, _T("C相运行电流"));

				m_ListCurrent.SetItemText(0, 2, strGroundCuA);
				m_ListCurrent.SetItemText(1, 2, strGroundCuB);
				m_ListCurrent.SetItemText(2, 2, strGroundCuC);
				m_ListCurrent.SetItemText(3, 2, strGroundCuAll);
				m_ListCurrent.SetItemText(4, 2, strCurrentA);
				m_ListCurrent.SetItemText(5, 2, strCurrentB);
				m_ListCurrent.SetItemText(6, 2, strCurrentC);
			
				//回到初始值
				orderFlag = -1;
				m_iRxLen = 0;
				msgNotice = _T("");

			}
		}
		else if (1 == orderFlag)
		{
			if (32 == m_iRxLen)
			{
				m_CtrRichEdit.SetSel(-1, -1);
				m_CtrRichEdit.ReplaceSel(_T("设备ID："));
				m_CtrRichEdit.ReplaceSel(msgNotice.Mid(8, 8));
				m_CtrRichEdit.ReplaceSel("\r\n");

				for (int i = 0; i < 16; i++)
				{
					m_HexData[i] = m_RxData[i + 16];
				}
				str2hex(m_HexData, hexData, 32);		//维护时str2hex可能需要更改参数
				knowStrData = hex2data(hexData);	//得到需要解析的字符串knowStrData

				CString strCatchTime;	//采样时间
				CString tm1 = knowStrData.Mid(0, 2);
				CString tm2 = knowStrData.Mid(2, 2);
				CString tm3 = knowStrData.Mid(4, 2);
				CString tm4 = knowStrData.Mid(6, 2);

				int value = _tcstoul(_T(tm1 + tm2 + tm3 + tm4), NULL, 16);
				CString sH, sM, sS;
				sH.Format("%d", value / 3600);
				sM.Format("%d", (value - (value / 3600) * 3600) / 60);
				sS.Format("%d", (value % 3600) % 60);
				if (sH.GetLength() < 2)
					sH = "0" + sH;
				if (sM.GetLength() < 2)
					sM = "0" + sM;
				if (sS.GetLength() < 2)
					sS = "0" + sS;
				strCatchTime = sH + ":" + sM + ":" + sS;

				m_CtrRichEdit.SetSel(-1, -1);
				m_CtrRichEdit.ReplaceSel(_T("采样时间：") + _T(strCatchTime) + _T("\r\n"));

				//回到初始值
				orderFlag = -1;	//重新判断
				m_iRxLen = 0;
				msgNotice = _T("");
			}
		}
		else if (2 == orderFlag)
		{
			if (32 == m_iRxLen)
			{
				m_CtrRichEdit.SetSel(-1, -1);
				m_CtrRichEdit.ReplaceSel(_T("设备ID："));
				m_CtrRichEdit.ReplaceSel(msgNotice.Mid(8, 8));
				m_CtrRichEdit.ReplaceSel("\r\n");

				for (int i = 0; i < 16; i++)
				{
					m_HexData[i] = m_RxData[i + 16];
				}
				str2hex(m_HexData, hexData, 32);		//维护时str2hex可能需要更改参数
				knowStrData = hex2data(hexData);	//得到需要解析的字符串knowStrData		

				//解析日期和时间
				CString time1 = knowStrData.Mid(10, 2); 	//时间	
				CString time2 = knowStrData.Mid(12, 2);
				CString time3 = knowStrData.Mid(14, 2);
				int timeInt1 = _tcstoul(_T(time1), NULL, 16);
				int timeInt2 = _tcstoul(_T(time2), NULL, 16);
				int timeInt3 = _tcstoul(_T(time3), NULL, 16);
				time1.Format("%d", timeInt1);
				time2.Format("%d", timeInt2);
				time3.Format("%d", timeInt3);
				CString systemTime = time1 + _T(":") + time2 + _T(":") + time3;

				CString date1 = knowStrData.Mid(2, 2);; 	//日期	
				CString date2 = knowStrData.Mid(4, 2);
				CString date3 = knowStrData.Mid(6, 2);
				int dateInt1 = _tcstoul(_T(date1), NULL, 16);
				int dateInt2 = _tcstoul(_T(date2), NULL, 16);
				int dateInt3 = _tcstoul(_T(date3), NULL, 16);
				date1.Format("%d", dateInt1);
				date2.Format("%d", dateInt2);
				date3.Format("%d", dateInt3);
				if (dateInt1 < 10)
				{
					date1 = _T("0") + date1;
				}
				CString systemDate = _T("20") + date1 + _T("-") + date2 + _T("-") + date3;
				m_CtrRichEdit.ReplaceSel(_T("设置RTC时间："));
				m_CtrRichEdit.ReplaceSel(systemDate + _T("  "));
				m_CtrRichEdit.ReplaceSel(systemTime);
				m_CtrRichEdit.ReplaceSel("\r\n");

				//回到初始值
				orderFlag = -1;	//重新判断
				m_iRxLen = 0;
				msgNotice = _T("");
			}
		}
		else if (3 == orderFlag)
		{
			if (32 == m_iRxLen)
			{
				m_CtrRichEdit.SetSel(-1, -1);
				m_CtrRichEdit.ReplaceSel(_T("设备ID："));
				m_CtrRichEdit.ReplaceSel(msgNotice.Mid(8, 8));
				m_CtrRichEdit.ReplaceSel("\r\n");

				for (int i = 0; i < 16; i++)
				{
					m_HexData[i] = m_RxData[i + 16];
				}
				str2hex(m_HexData, hexData, 32);		//维护时str2hex可能需要更改参数
				knowStrData = hex2data(hexData);	//得到需要解析的字符串knowStrData	

				//回到初始值
				orderFlag = -1;	//重新判断
				m_iRxLen = 0;
				msgNotice = _T("");
			}
		}
		else if (4 == orderFlag)
		{
			if (32 == m_iRxLen)
			{
				m_CtrRichEdit.SetSel(-1, -1);
				m_CtrRichEdit.ReplaceSel(_T("设备ID："));
				m_CtrRichEdit.ReplaceSel(msgNotice.Mid(8, 8));
				m_CtrRichEdit.ReplaceSel("\r\n");

				for (int i = 0; i < 16; i++)
				{
					m_HexData[i] = m_RxData[i + 16];
				}
				str2hex(m_HexData, hexData, 32);		//维护时str2hex可能需要更改参数
				knowStrData = hex2data(hexData);	//得到需要解析的字符串knowStrData	

				//回到初始值
				orderFlag = -1;	//重新判断
				m_iRxLen = 0;
				msgNotice = _T("");
			}
		}

		//滚动置底
		m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}

	/************************************************************************/
	/* C类数据结构解析                                                         */
	/************************************************************************/
	if (_T("115200") == cboStr)
	{
		int selcount = m_CtrRichEdit.GetLineCount();
		CString strTemp;
		strTemp.Format("%d", m_iRxLen);
		m_RxData[m_iRxLen] = ch;	//缓冲字符数组
		msgNotice += char(ch);
		CString msgTemp = " 采集数据:";
		m_iRxLen++;				//控制行数
		if ((m_RxData[m_iRxLen - 2] == '\r' && m_RxData[m_iRxLen - 1] == '\n'))
		{
			CString mLeft4 = msgNotice.Left(4);

			if ("设置" != mLeft4)
			{
				CString mstr1;
				for (int i = 0; i < m_iRxLen; i++)
				{
					mstr1 += char(m_RxData[i]);
				}

				m_CtrRichEdit.SetSel(-1, -1);
				m_CtrRichEdit.ReplaceSel(mstr1);
			}

			if ("设置" == mLeft4 || "状态" == mLeft4 || "保存" == mLeft4)
			{
				CString mTemp;
				for (int i = 0; i < m_iRxLen; i++)
				{
					mTemp += char(m_RxData[i]);
				}

				CHARFORMAT cf;
				ZeroMemory(&cf, sizeof(CHARFORMAT));
				cf.cbSize = sizeof(CHARFORMAT);
				cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE |
					CFM_ITALIC | CFM_SIZE | CFM_UNDERLINE;
				cf.dwEffects = 0;
				cf.crTextColor = RGB(255, 0, 0); //文字颜色
				m_CtrRichEdit.SetSel(-1, -1); //设置处理区域
				m_CtrRichEdit.SetSelectionCharFormat(cf);

				m_CtrRichEdit.ReplaceSel(mTemp);

			}

			if ("校准" == mLeft4 || msgNotice.Mid(0, 3) == "a1=")
			{
				//初始化电流校准系数
				CString mydata = LookChildString(msgNotice);
				m_MyData += mydata;
				dataNum++;

				if (8 == dataNum)
				{
					dataNum = 0;
					CStringArray strArr;

					while (m_MyData.Find(_T(" ")) > 0)
					{
						int findSpace = m_MyData.Find(_T(" "));

						strArr.Add(m_MyData.Left(findSpace));
						m_MyData.Delete(0, findSpace + 1);
					}

					int arrSize = strArr.GetSize();

					CString count;
					count.Format(_T("%d"), arrSize);
					//MessageBox(count, _T(""), MB_OK);
					//MessageBox(strArr.GetAt(0), _T(""), MB_OK);

					for (int i = 0; i < arrSize; i++)
					{
						if (strArr.GetAt(i).Find("\r\n") > 0)
						{
							int findN = strArr[i].Find("\r\n");
							strArr[i].Delete(0, findN + 2);
						}
						strArr[i] = strArr[i].Left(6);
					}

					m_currentSet_List.SetItemText(0, 1, _T(strArr[1]));//1 5 9 13 17 21 25
					m_currentSet_List.SetItemText(1, 1, _T(strArr[5]));
					m_currentSet_List.SetItemText(2, 1, _T(strArr[9]));
					m_currentSet_List.SetItemText(3, 1, _T(strArr[13]));
					m_currentSet_List.SetItemText(4, 1, _T(strArr[17]));
					m_currentSet_List.SetItemText(5, 1, _T(strArr[21]));
					m_currentSet_List.SetItemText(6, 1, _T(strArr[25]));

					m_currentSet_List.SetItemText(0, 2, _T(strArr[0]) + " " + strArr[1]);
					m_currentSet_List.SetItemText(1, 2, _T(strArr[4]) + " " + strArr[5]);
					m_currentSet_List.SetItemText(2, 2, _T(strArr[8]) + " " + strArr[9]);
					m_currentSet_List.SetItemText(3, 2, _T(strArr[12]) + " " + strArr[13]);
					m_currentSet_List.SetItemText(4, 2, _T(strArr[16]) + " " + strArr[17]);
					m_currentSet_List.SetItemText(5, 2, _T(strArr[20]) + " " + strArr[21]);
					m_currentSet_List.SetItemText(6, 2, _T(strArr[24]) + " " + strArr[25]);

					m_currentSet_List.SetItemText(0, 3, _T(strArr[2]) + " " + strArr[3]);
					m_currentSet_List.SetItemText(1, 3, _T(strArr[6]) + " " + strArr[7]);
					m_currentSet_List.SetItemText(2, 3, _T(strArr[10]) + " " + strArr[11]);
					m_currentSet_List.SetItemText(3, 3, _T(strArr[14]) + " " + strArr[15]);
					m_currentSet_List.SetItemText(4, 3, _T(strArr[18]) + " " + strArr[19]);
					m_currentSet_List.SetItemText(5, 3, _T(strArr[22]) + " " + strArr[23]);
					m_currentSet_List.SetItemText(6, 3, _T(strArr[26]) + " " + strArr[27]);
				}

				CString tempp = m_currentSet_List.GetItemText(m_Row, m_Col);
				m_CurrentEdit.SetWindowTextA(tempp);
			}

			if (msgTemp == msgNotice.Mid(0, 10))
			{
				for (int i = 0; i < 130; i++)
				{
					m_HexData[i] = m_RxData[i + 18];
				}
				str2hex(m_HexData, hexData,250);		//维护时str2hex可能需要更改参数
				knowStrData = hex2data(hexData);	//得到需要解析的字符串knowStrData

				CString systemID;
				systemID.Format(_T("%s"), m_RxData);

				int bugtest = 0;
				////////////////////////////////////////////////////////////////////
				/*
				电流解析：
				Mid函数：字符串切割
				atof函数：16进制CString变成double
				Format：变为带2位小数点字符串
				hexString2Byte：16进制字符串变成BYTE数组
				*/
				////////////////////////////////////////////////////////////////////
				CString strDivID;
				CString date1 = knowStrData.Mid(8, 2);	//日期			
				CString date2 = knowStrData.Mid(10, 2);
				CString date3 = knowStrData.Mid(12, 2);
				int dateInt1 = _tcstoul(_T(date1), NULL, 16);
				int dateInt2 = _tcstoul(_T(date2), NULL, 16);
				int dateInt3 = _tcstoul(_T(date3), NULL, 16);
				date1.Format("%d", dateInt1);
				date2.Format("%d", dateInt2);
				date3.Format("%d", dateInt3);
				if (dateInt3 < 10)
				{
					date3 = _T("0") + date3;
				}
				CString systemDate = _T("20") + date3 + _T("-") + date2 + _T("-") + date1;

				CString data2;
				CString data3;
				CString strRunTime;
				CString strLocalVbat;
				CString strGroundCuA;
				CString strGroundCuB;
				CString strGroundCuC;
				CString strGroundCuAll;
				CString strCurrentA;
				CString strCurrentB;
				CString strCurrentC;

				BYTE byteLocalVbat[5];
				BYTE byteGroundCuA[5];
				BYTE byteGroundCuB[5];
				BYTE byteGroundCuC[5];
				BYTE byteGroundCuAll[5];
				BYTE byteCurrentA[5];
				BYTE byteCurrentB[5];
				BYTE byteCurrentC[5];

				float fLocalVbat;
				float fGroundCuA;
				float fGroundCuB;
				float fGroundCuC;
				float fGroundCuAll;
				float fCurrentA;
				float fCurrentB;
				float fCurrentC;

				//16位CString转换为字节数组
				hexString2Byte(knowStrData.Mid(80, 8), byteLocalVbat);	//电池电压
				hexString2Byte(knowStrData.Mid(16, 8), byteGroundCuA);
				hexString2Byte(knowStrData.Mid(24, 8), byteGroundCuB);
				hexString2Byte(knowStrData.Mid(32, 8), byteGroundCuC);
				hexString2Byte(knowStrData.Mid(40, 8), byteGroundCuAll);
				hexString2Byte(knowStrData.Mid(48, 8), byteCurrentA);
				hexString2Byte(knowStrData.Mid(56, 8), byteCurrentB);
				hexString2Byte(knowStrData.Mid(64, 8), byteCurrentC);

				//防止越界 维护时修改
				byteLocalVbat[4] = '\0';
				byteGroundCuA[4] = '\0';
				byteGroundCuB[4] = '\0';
				byteGroundCuC[4] = '\0';
				byteGroundCuAll[4] = '\0';
				byteCurrentA[4] = '\0';
				byteCurrentB[4] = '\0';
				byteCurrentC[4] = '\0';

				//字节数组转成浮点数
				memcpy(&fLocalVbat, &byteLocalVbat[0], 4);
				memcpy(&fGroundCuA, &byteGroundCuA[0], 4);
				memcpy(&fGroundCuB, &byteGroundCuB[0], 4);
				memcpy(&fGroundCuC, &byteGroundCuC[0], 4);
				memcpy(&fGroundCuAll, &byteGroundCuAll[0], 4);
				memcpy(&fCurrentA, &byteCurrentA[0], 4);
				memcpy(&fCurrentB, &byteCurrentB[0], 4);
				memcpy(&fCurrentC, &byteCurrentC[0], 4);

				//浮点数转回CString
				strLocalVbat.Format("%.4lf", fLocalVbat);
				strGroundCuA.Format("%.4lf", fGroundCuA);
				strGroundCuB.Format("%.4lf", fGroundCuB);
				strGroundCuC.Format("%.4lf", fGroundCuC);
				strGroundCuAll.Format("%.4lf", fGroundCuAll);
				strCurrentA.Format("%.4lf", fCurrentA);
				strCurrentB.Format("%.4lf", fCurrentB);
				strCurrentC.Format("%.4lf", fCurrentC);

				//解析时间
				CString tm1 = knowStrData.Mid(168, 2);
				CString tm2 = knowStrData.Mid(170, 2);
				CString tm3 = knowStrData.Mid(172, 2);
				CString tm4 = knowStrData.Mid(174, 2);

				int value = _tcstoul(_T(tm4 + tm3 + tm2 + tm1), NULL, 16);
				CString sH, sM, sS;
				sH.Format("%d", value / 3600);
				sM.Format("%d", (value - (value / 3600) * 3600) / 60);
				sS.Format("%d", (value % 3600) % 60);
				if (sH.GetLength() < 2)
					sH = "0" + sH;
				if (sM.GetLength() < 2)
					sM = "0" + sM;
				if (sS.GetLength() < 2)
					sS = "0" + sS;
				strRunTime = sH + ":" + sM + ":" + sS;

				//Info表放数据
				m_ListInfo.SetItemText(0, 0, systemID.Mid(10, 8));
				m_ListInfo.SetItemText(0, 1, systemDate);
				m_ListInfo.SetItemText(0, 2, strRunTime);
				m_ListInfo.SetItemText(0, 3, strLocalVbat);

				//m_ListCurrent表放数据
				m_ListCurrent.SetItemText(0, 1, _T("A相接地电流"));
				m_ListCurrent.SetItemText(1, 1, _T("B相接地电流"));
				m_ListCurrent.SetItemText(2, 1, _T("C相接地电流"));
				m_ListCurrent.SetItemText(3, 1, _T(" 总接地电流"));
				m_ListCurrent.SetItemText(4, 1, _T("A相运行电流"));
				m_ListCurrent.SetItemText(5, 1, _T("B相运行电流"));
				m_ListCurrent.SetItemText(6, 1, _T("C相运行电流"));

				m_ListCurrent.SetItemText(0, 2, strGroundCuA);
				m_ListCurrent.SetItemText(1, 2, strGroundCuB);
				m_ListCurrent.SetItemText(2, 2, strGroundCuC);
				m_ListCurrent.SetItemText(3, 2, strGroundCuAll);
				m_ListCurrent.SetItemText(4, 2, strCurrentA);
				m_ListCurrent.SetItemText(5, 2, strCurrentB);
				m_ListCurrent.SetItemText(6, 2, strCurrentC);

			}

			m_StrRichEdit = "";
			msgNotice = "";
			m_iRxLen = 0;

			int nline = m_CtrRichEdit.GetLineCount();

			if (nline > 50000)
			{
				UpdateData(TRUE);
				m_StrSendData = _T("");			//清空编辑区
				UpdateData(FALSE);
			}

			//滚动置底
			m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
	}

	return 0;
}

CString CToolDlg::LookChildString(CString cStr)
{
	while (cStr.Find(_T("=")) > 0)
	{
		if (cStr.Find(_T("a1=")) > 0)
		{
			int csFind = cStr.Find(_T("a1="));
			cStr.Delete(0, csFind + 3);
		}

		int csFind2 = cStr.Find(_T("="));
		cStr.Delete(csFind2 - 2, 3);
	}
	return cStr;
}


CString CToolDlg::AvoidLarge(CString cstr)
{
	float num = _ttof(cstr);
	if (num >= 10)
	{
		CString wodema("9.9999");
		return wodema;
	}
	else if (num <= 0)
	{
		CString wodema("1.0000");
		return wodema;
	}
	else
		return cstr;
}

void CToolDlg::hexString2Byte(CString& in, BYTE out[])
{
	if (in.GetLength() < 8)		//指定8位字符 4个字节
		in = "0000" + in;
	int len = (int)strlen(in);
	char* str = (char*)malloc(len);
	memset(str, 0, len);
	memcpy(str, in, len);
	for (int i = 0; i < len; i += 2) {
		//小写转大写
		if (str[i] >= 'a' && str[i] <= 'f') str[i] = str[i] & ~0x20;
		if (str[i + 1] >= 'a' && str[i] <= 'f') str[i + 1] = str[i + 1] & ~0x20;
		//处理第前4位
		if (str[i] >= 'A' && str[i] <= 'F')
			out[i / 2] = (str[i] - 'A' + 10) << 4;
		else
			out[i / 2] = (str[i] & ~0x30) << 4;
		//处理后4位, 并组合起来
		if (str[i + 1] >= 'A' && str[i + 1] <= 'F')
			out[i / 2] |= (str[i + 1] - 'A' + 10);
		else
			out[i / 2] |= (str[i + 1] & ~0x30);
	}
	free(str);
	out[4] = '\0';
}

//float CToolDlg::ByteBufToFloat(BYTE *buf,int mode)
//{    
//    ASSERT(buf != NULL);
//    
//    if (buf == NULL)
//    {
//        return 0;
//    }
//
//    BYTE *pBuf=buf;
//    BYTE buff[4];
//    switch(mode)
//    {
//    default:
//    case 0: 
//        buff[0]=pBuf[3];
//        buff[1]=pBuf[2];
//        buff[2]=pBuf[1];
//        buff[3]=pBuf[0];
//        break;
//    case 1: 
//        buff[0]=pBuf[2];
//        buff[1]=pBuf[3];
//        buff[2]=pBuf[0];
//        buff[3]=pBuf[1];
//        break;
//    case 2: 
//        buff[0]=pBuf[0];
//        buff[1]=pBuf[1];
//        buff[2]=pBuf[2];
//        buff[3]=pBuf[3];
//        break;
//    case 3: 
//        buff[0]=pBuf[1];
//        buff[1]=pBuf[0];
//        buff[2]=pBuf[3];
//        buff[3]=pBuf[2];
//        break;
//    }
//    float Data;
//    memcpy(&Data,buff,4);
//    return  Data;
//}

CString CToolDlg::ChangeCharstr2Hexstr(CString Charstr)
{
	CString Hexstr = _T("");
	Charstr.MakeUpper();
	HexStringFilter(Charstr);
	int Length = Charstr.GetLength();
	if (Length % 2)
		Charstr.Delete(Length - 1);
	Length = Charstr.GetLength();
	for (int i = 0; i < Length / 2; i++)
	{
		Hexstr += CombineHexChar(Charstr.GetAt(i * 2), Charstr.GetAt(i * 2 + 1));
	}
	return Hexstr;
}

void CToolDlg::HexStringFilter(CString& str)
{
	BOOL bOK;
	for (int i = 0; i < str.GetLength();)
	{
		bOK = ((str.GetAt(i) >= '0') && (str.GetAt(i) <= '9')) ||
			((str.GetAt(i) >= 'A') && (str.GetAt(i) <= 'F')) ||
			((str.GetAt(i) >= 'a') && (str.GetAt(i) <= 'f'));
		if (!bOK)
			str.Delete(i);
		else i++;
	}
}
char CToolDlg::CombineHexChar(char CharH, char CharL)
{
	char result;
	CString temp;
	if (CharH >= '0' && CharH <= '9')			result = (CharH - '0');
	else if (CharH >= 'a' && CharH <= 'f')		result = (CharH - 'a' + 10);
	else if (CharH >= 'A' && CharH <= 'F')		result = (CharH - 'A' + 10);
	else								result = 0;
	result <<= 4;
	if (CharL >= '0' && CharL <= '9')			result += (CharL - '0');
	else if (CharL >= 'a' && CharL <= 'f')		result += (CharL - 'a' + 10);
	else if (CharL >= 'A' && CharL <= 'F')		result += (CharL - 'A' + 10);
	else								result += 0;
	return result;
}

void CToolDlg::str2hex(char* str, char* hex, int n)
{
	const char* cHex = "0123456789ABCDEF";
	int i = 0;
	for (int j = 0; j < n; j++)
	{
		unsigned int a = (unsigned int)str[j];
		hex[i++] = cHex[(a & 0xf0) >> 4];
		hex[i++] = cHex[(a & 0x0f)];
	}
}

CString CToolDlg::hex2data(char* hex)
{
	CString strData;
	char temp[261] = { 0 };
	for (int k = 0; k < 260; k++)
	{
		temp[k] = hex[k];
	}
	temp[260] = '\0';
	strData.Format(temp);
	return strData;
}

CString CToolDlg::hexCharToNumber(char HexChar)
{
	CString result = _T("");
	int temp = (HexChar & 0xF0) >> 4;
	if (temp < 10)
		result += char(temp + '0');
	else
		result += char(temp + 'A' - 10);
	temp = HexChar & 0x0F;
	if (temp < 10)
		result += char(temp + '0');
	else
		result += char(temp + 'A' - 10);
	return result;
}

void CToolDlg::OnBnClickedButtonCal()
{	// TODO: 在此添加控件通知处理程序代码
	if (m_Connected)
	{
		if (m_ListCurrent.GetItemText(0, 1) != "")	//判断电流有数据时才做计算
		{
			//得到m_ListCurrent上的电流值
			CString strCh0 = m_ListCurrent.GetItemText(0, 2);
			CString strCh1 = m_ListCurrent.GetItemText(1, 2);
			CString strCh2 = m_ListCurrent.GetItemText(2, 2);
			CString strCh3 = m_ListCurrent.GetItemText(3, 2);
			CString strCh4 = m_ListCurrent.GetItemText(4, 2);
			CString strCh5 = m_ListCurrent.GetItemText(5, 2);
			CString strCh6 = m_ListCurrent.GetItemText(6, 2);

			if (0 == m_cboCurrent.GetCurSel())
			{
				CString bCh0, bCh1, bCh2, bCh3, bCh4, bCh5, bCh6;
				bCh0.Format(_T("%.4f"), atof(strCh0));
				bCh1.Format(_T("%.4f"), atof(strCh1));
				bCh2.Format(_T("%.4f"), atof(strCh2));
				bCh3.Format(_T("%.4f"), atof(strCh3));
				bCh4.Format(_T("%.4f"), atof(strCh4));
				bCh5.Format(_T("%.4f"), atof(strCh5));
				bCh6.Format(_T("%.4f"), atof(strCh6));

				m_currentSet_List.SetItemText(0, 1, AvoidLarge(bCh0));
				m_currentSet_List.SetItemText(1, 1, AvoidLarge(bCh1));
				m_currentSet_List.SetItemText(2, 1, AvoidLarge(bCh2));
				m_currentSet_List.SetItemText(3, 1, AvoidLarge(bCh3));
				m_currentSet_List.SetItemText(4, 1, AvoidLarge(bCh4));
				m_currentSet_List.SetItemText(5, 1, AvoidLarge(bCh5));
				m_currentSet_List.SetItemText(6, 1, AvoidLarge(bCh6));
			}

			if (1 == m_cboCurrent.GetCurSel())		//当电流为3.5A时
			{
				CString bCh0 = (m_currentSet_List.GetItemText(0, 1)).Mid(0, 6);		//得到0时的b值	
				CString bCh1 = (m_currentSet_List.GetItemText(1, 1)).Mid(0, 6);
				CString bCh2 = (m_currentSet_List.GetItemText(2, 1)).Mid(0, 6);
				CString bCh3 = (m_currentSet_List.GetItemText(3, 1)).Mid(0, 6);
				CString bCh4 = (m_currentSet_List.GetItemText(4, 1)).Mid(0, 6);
				CString bCh5 = (m_currentSet_List.GetItemText(5, 1)).Mid(0, 6);
				CString bCh6 = (m_currentSet_List.GetItemText(6, 1)).Mid(0, 6);

				CString kCh0, kCh1, kCh2, kCh3, kCh4, kCh5, kCh6;
				kCh0.Format(_T("%.3f"), (3.5 + atof(bCh0)) / atof(strCh0));
				kCh1.Format(_T("%.3f"), (3.5 + atof(bCh1)) / atof(strCh1));
				kCh2.Format(_T("%.3f"), (3.5 + atof(bCh2)) / atof(strCh2));
				kCh3.Format(_T("%.3f"), (3.5 + atof(bCh3)) / atof(strCh3));
				kCh4.Format(_T("%.3f"), (3.5 + atof(bCh4)) / atof(strCh4));
				kCh5.Format(_T("%.3f"), (3.5 + atof(bCh5)) / atof(strCh5));
				kCh6.Format(_T("%.3f"), (3.5 + atof(bCh6)) / atof(strCh6));

				m_currentSet_List.SetItemText(0, 2, AvoidLarge(kCh0) + _T(" -") + AvoidLarge(bCh0));
				m_currentSet_List.SetItemText(1, 2, AvoidLarge(kCh1) + _T(" -") + AvoidLarge(bCh1));
				m_currentSet_List.SetItemText(2, 2, AvoidLarge(kCh2) + _T(" -") + AvoidLarge(bCh2));
				m_currentSet_List.SetItemText(3, 2, AvoidLarge(kCh3) + _T(" -") + AvoidLarge(bCh3));
				m_currentSet_List.SetItemText(4, 2, AvoidLarge(kCh4) + _T(" -") + AvoidLarge(bCh4));
				m_currentSet_List.SetItemText(5, 2, AvoidLarge(kCh5) + _T(" -") + AvoidLarge(bCh5));
				m_currentSet_List.SetItemText(6, 2, AvoidLarge(kCh6) + _T(" -") + AvoidLarge(bCh6));
			}
			int wode = 1;

			if (2 == m_cboCurrent.GetCurSel())		//当电流为100A时
			{
				CString kCh0, kCh1, kCh2, kCh3, kCh4, kCh5, kCh6;						//3.5A时的k值
				CString kTCh0, kTCh1, kTCh2, kTCh3, kTCh4, kTCh5, kTCh6;				//100A时的k值
				CString bTCh0, bTCh1, bTCh2, bTCh3, bTCh4, bTCh5, bTCh6;				//100A时的b值
				CString curCh0, curCh1, curCh2, curCh3, curCh4, curCh5, curCh6;		//3.5A时电流值
				int i0 = 0;
				int i1 = 0;
				int i2 = 0;
				int i3 = 0;
				int i4 = 0;
				int i5 = 0;
				int i6 = 0;
				while ((m_currentSet_List.GetItemText(0, 2)).Mid(i0, 1) != " ")
					i0++;
				while ((m_currentSet_List.GetItemText(1, 2)).Mid(i1, 1) != " ")
					i1++;
				while ((m_currentSet_List.GetItemText(2, 2)).Mid(i2, 1) != " ")
					i2++;
				while ((m_currentSet_List.GetItemText(3, 2)).Mid(i3, 1) != " ")
					i3++;
				while ((m_currentSet_List.GetItemText(4, 2)).Mid(i4, 1) != " ")
					i4++;
				while ((m_currentSet_List.GetItemText(5, 2)).Mid(i5, 1) != " ")
					i5++;
				while ((m_currentSet_List.GetItemText(6, 2)).Mid(i6, 1) != " ")
					i6++;
				kCh0 = (m_currentSet_List.GetItemText(0, 2)).Mid(0, i0);		//将3.5A时候的k解析出来
				kCh1 = (m_currentSet_List.GetItemText(1, 2)).Mid(0, i1);
				kCh2 = (m_currentSet_List.GetItemText(2, 2)).Mid(0, i2);
				kCh3 = (m_currentSet_List.GetItemText(3, 2)).Mid(0, i3);
				kCh4 = (m_currentSet_List.GetItemText(4, 2)).Mid(0, i4);
				kCh5 = (m_currentSet_List.GetItemText(5, 2)).Mid(0, i5);
				kCh6 = (m_currentSet_List.GetItemText(6, 2)).Mid(0, i6);

				curCh0.Format(_T("%.4f"), CURRENTVALUE0 / atof(kCh0));					//3.5/k 即得到此时电流值x
				curCh1.Format(_T("%.4f"), CURRENTVALUE0 / atof(kCh1));
				curCh2.Format(_T("%.4f"), CURRENTVALUE0 / atof(kCh2));
				curCh3.Format(_T("%.4f"), CURRENTVALUE0 / atof(kCh3));
				curCh4.Format(_T("%.4f"), CURRENTVALUE0 / atof(kCh4));
				curCh5.Format(_T("%.4f"), CURRENTVALUE0 / atof(kCh5));
				curCh6.Format(_T("%.4f"), CURRENTVALUE0 / atof(kCh6));

				kTCh0.Format(_T("%.3f"), (CURRENTVALUE1 - CURRENTVALUE0) / (atof(strCh0) - atof(curCh0)));		//求100A时k值 cstring
				kTCh1.Format(_T("%.3f"), (CURRENTVALUE1 - CURRENTVALUE0) / (atof(strCh1) - atof(curCh1)));
				kTCh2.Format(_T("%.3f"), (CURRENTVALUE1 - CURRENTVALUE0) / (atof(strCh2) - atof(curCh2)));
				kTCh3.Format(_T("%.3f"), (CURRENTVALUE1 - CURRENTVALUE0) / (atof(strCh3) - atof(curCh3)));
				kTCh4.Format(_T("%.3f"), (CURRENTVALUE1 - CURRENTVALUE0) / (atof(strCh4) - atof(curCh4)));
				kTCh5.Format(_T("%.3f"), (CURRENTVALUE1 - CURRENTVALUE0) / (atof(strCh5) - atof(curCh5)));
				kTCh6.Format(_T("%.3f"), (CURRENTVALUE1 - CURRENTVALUE0) / (atof(strCh6) - atof(curCh6)));

				bTCh0.Format(_T("%.4f"), (CURRENTVALUE1 - atof(kTCh0) * atof(strCh0)));		//求100A时b值 cstring
				bTCh1.Format(_T("%.4f"), (CURRENTVALUE1 - atof(kTCh1) * atof(strCh1)));
				bTCh2.Format(_T("%.4f"), (CURRENTVALUE1 - atof(kTCh2) * atof(strCh2)));
				bTCh3.Format(_T("%.4f"), (CURRENTVALUE1 - atof(kTCh3) * atof(strCh3)));
				bTCh4.Format(_T("%.4f"), (CURRENTVALUE1 - atof(kTCh4) * atof(strCh4)));
				bTCh5.Format(_T("%.4f"), (CURRENTVALUE1 - atof(kTCh5) * atof(strCh5)));
				bTCh6.Format(_T("%.4f"), (CURRENTVALUE1 - atof(kTCh6) * atof(strCh6)));


				m_currentSet_List.SetItemText(0, 3, AvoidLarge(kTCh0) + _T(" ") + AvoidLarge(bTCh0));
				m_currentSet_List.SetItemText(1, 3, AvoidLarge(kTCh1) + _T(" ") + AvoidLarge(bTCh1));
				m_currentSet_List.SetItemText(2, 3, AvoidLarge(kTCh2) + _T(" ") + AvoidLarge(bTCh2));
				m_currentSet_List.SetItemText(3, 3, AvoidLarge(kTCh3) + _T(" ") + AvoidLarge(bTCh3));
				m_currentSet_List.SetItemText(4, 3, AvoidLarge(kTCh4) + _T(" ") + AvoidLarge(bTCh4));
				m_currentSet_List.SetItemText(5, 3, AvoidLarge(kTCh5) + _T(" ") + AvoidLarge(bTCh5));
				m_currentSet_List.SetItemText(6, 3, AvoidLarge(kTCh6) + _T(" ") + AvoidLarge(bTCh6));
			}
		}
	}
}


void CToolDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_currentSet_List.GetItemText(0, 3) != "")	//判断有电流系数时才做校准
	{
		UpdateData(true);

		CString kCh0("10000"), kCh1("10000"), kCh2("10000"), kCh3("10000"), kCh4("10000"), kCh5("10000"), kCh6("10000");						//3.5A时的k值
		CString bCh0("+0000"), bCh1("+0000"), bCh2("+0000"), bCh3("+0000"), bCh4("+0000"), bCh5("+0000"), bCh6("+0000");						//3.5A时的b值
		CString kTCh0("10000"), kTCh1("10000"), kTCh2("10000"), kTCh3("10000"), kTCh4("10000"), kTCh5("10000"), kTCh6("10000");				//100A时的k值
		CString bTCh0("+0000"), bTCh1("+0000"), bTCh2("+0000"), bTCh3("+0000"), bTCh4("+0000"), bTCh5("+0000"), bTCh6("+0000");				//100A时的b值
		//取电流校准系数
		int i0 = 0;
		int i1 = 0;
		int i2 = 0;
		int i3 = 0;
		int i4 = 0;
		int i5 = 0;
		int i6 = 0;
		while ((m_currentSet_List.GetItemText(0, 2)).Mid(i0, 1) != " ")
			i0++;
		while ((m_currentSet_List.GetItemText(1, 2)).Mid(i1, 1) != " ")
			i1++;
		while ((m_currentSet_List.GetItemText(2, 2)).Mid(i2, 1) != " ")
			i2++;
		while ((m_currentSet_List.GetItemText(3, 2)).Mid(i3, 1) != " ")
			i3++;
		while ((m_currentSet_List.GetItemText(4, 2)).Mid(i4, 1) != " ")
			i4++;
		while ((m_currentSet_List.GetItemText(5, 2)).Mid(i5, 1) != " ")
			i5++;
		while ((m_currentSet_List.GetItemText(6, 2)).Mid(i6, 1) != " ")
			i6++;
		kCh0 = (m_currentSet_List.GetItemText(0, 2)).Mid(0, i0);		//将3.5A时候的k解析出来(4位）
		kCh1 = (m_currentSet_List.GetItemText(1, 2)).Mid(0, i1);
		kCh2 = (m_currentSet_List.GetItemText(2, 2)).Mid(0, i2);
		kCh3 = (m_currentSet_List.GetItemText(3, 2)).Mid(0, i3);
		kCh4 = (m_currentSet_List.GetItemText(4, 2)).Mid(0, i4);
		kCh5 = (m_currentSet_List.GetItemText(5, 2)).Mid(0, i5);
		kCh6 = (m_currentSet_List.GetItemText(6, 2)).Mid(0, i6);
		float f1 = _tstof(kCh0);
		float f2 = _tstof(kCh1);
		float f3 = _tstof(kCh2);
		float f4 = _tstof(kCh3);
		float f5 = _tstof(kCh4);
		float f6 = _tstof(kCh5);
		float f7 = _tstof(kCh6);
		kCh0.Format("%.4f", f1);
		kCh1.Format("%.4f", f2);
		kCh2.Format("%.4f", f3);
		kCh3.Format("%.4f", f4);
		kCh4.Format("%.4f", f5);
		kCh5.Format("%.4f", f6);
		kCh6.Format("%.4f", f7);

		/*将3.5A时候的b解析出来*/
		//第一种方法
		//bCh0 = (m_currentSet_List.GetItemText(0,1)).Mid(i0,((m_currentSet_List.GetItemText(0,1)).GetLength()-i0));		//将3.5A时候的b解析出来
		//第二种方法
		bCh0 = (m_currentSet_List.GetItemText(0, 2));
		bCh0.Delete(0, i0 + 1);
		bCh1 = (m_currentSet_List.GetItemText(1, 2));
		bCh1.Delete(0, i1 + 1);
		bCh2 = (m_currentSet_List.GetItemText(2, 2));
		bCh2.Delete(0, i2 + 1);
		bCh3 = (m_currentSet_List.GetItemText(3, 2));
		bCh3.Delete(0, i3 + 1);
		bCh4 = (m_currentSet_List.GetItemText(4, 2));
		bCh4.Delete(0, i4 + 1);
		bCh5 = (m_currentSet_List.GetItemText(5, 2));
		bCh5.Delete(0, i5 + 1);
		bCh6 = (m_currentSet_List.GetItemText(6, 2));
		bCh6.Delete(0, i6 + 1);

		CString  str = m_currentSet_List.GetItemText(0, 1);

		while ((m_currentSet_List.GetItemText(0, 3)).Mid(i0, 1) != " ")
			i0++;
		while ((m_currentSet_List.GetItemText(1, 3)).Mid(i1, 1) != " ")
			i1++;
		while ((m_currentSet_List.GetItemText(2, 3)).Mid(i2, 1) != " ")
			i2++;
		while ((m_currentSet_List.GetItemText(3, 3)).Mid(i3, 1) != " ")
			i3++;
		while ((m_currentSet_List.GetItemText(4, 3)).Mid(i4, 1) != " ")
			i4++;
		while ((m_currentSet_List.GetItemText(5, 3)).Mid(i5, 1) != " ")
			i5++;
		while ((m_currentSet_List.GetItemText(6, 3)).Mid(i6, 1) != " ")
			i6++;

		kTCh0 = (m_currentSet_List.GetItemText(0, 3)).Mid(0, i0);		//将100A时候的k解析出来
		kTCh1 = (m_currentSet_List.GetItemText(1, 3)).Mid(0, i1);
		kTCh2 = (m_currentSet_List.GetItemText(2, 3)).Mid(0, i2);
		kTCh3 = (m_currentSet_List.GetItemText(3, 3)).Mid(0, i3);
		kTCh4 = (m_currentSet_List.GetItemText(4, 3)).Mid(0, i4);
		kTCh5 = (m_currentSet_List.GetItemText(5, 3)).Mid(0, i5);
		kTCh6 = (m_currentSet_List.GetItemText(6, 3)).Mid(0, i6);
		float ff1 = _tstof(kTCh0);
		float ff2 = _tstof(kTCh1);
		float ff3 = _tstof(kTCh2);
		float ff4 = _tstof(kTCh3);
		float ff5 = _tstof(kTCh4);
		float ff6 = _tstof(kTCh5);
		float ff7 = _tstof(kTCh6);
		kTCh0.Format("%.4f", ff1);
		kTCh1.Format("%.4f", ff2);
		kTCh2.Format("%.4f", ff3);
		kTCh3.Format("%.4f", ff4);
		kTCh4.Format("%.4f", ff5);
		kTCh5.Format("%.4f", ff6);
		kTCh6.Format("%.4f", ff7);


		/*将100A时候的b解析出来*/
		bTCh0 = (m_currentSet_List.GetItemText(0, 3));
		bTCh0.Delete(0, i0 + 1);
		bTCh1 = (m_currentSet_List.GetItemText(1, 3));
		bTCh1.Delete(0, i1 + 1);
		bTCh2 = (m_currentSet_List.GetItemText(2, 3));
		bTCh2.Delete(0, i2 + 1);
		bTCh3 = (m_currentSet_List.GetItemText(3, 3));
		bTCh3.Delete(0, i3 + 1);
		bTCh4 = (m_currentSet_List.GetItemText(4, 3));
		bTCh4.Delete(0, i4 + 1);
		bTCh5 = (m_currentSet_List.GetItemText(5, 3));
		bTCh5.Delete(0, i5 + 1);
		bTCh6 = (m_currentSet_List.GetItemText(6, 3));
		bTCh6.Delete(0, i6 + 1);

		/************************************************************************/
		/* 将CString型的数据k，b转换成命令                                                                     */
		/************************************************************************/
		kCh0 = kDatatoOrder(kCh0);//1.0000  1.000
		kCh1 = kDatatoOrder(kCh1);
		kCh2 = kDatatoOrder(kCh2);
		kCh3 = kDatatoOrder(kCh3);
		kCh4 = kDatatoOrder(kCh4);
		kCh5 = kDatatoOrder(kCh5);
		kCh6 = kDatatoOrder(kCh6);

		kTCh0 = kDatatoOrder(kTCh0);
		kTCh1 = kDatatoOrder(kTCh1);
		kTCh2 = kDatatoOrder(kTCh2);
		kTCh3 = kDatatoOrder(kTCh3);
		kTCh4 = kDatatoOrder(kTCh4);
		kTCh5 = kDatatoOrder(kTCh5);
		kTCh6 = kDatatoOrder(kTCh6);

		bCh0 = bDatatoOrder(bCh0);
		bCh1 = bDatatoOrder(bCh1);
		bCh2 = bDatatoOrder(bCh2);
		bCh3 = bDatatoOrder(bCh3);
		bCh4 = bDatatoOrder(bCh4);
		bCh5 = bDatatoOrder(bCh5);
		bCh6 = bDatatoOrder(bCh6);

		bTCh0 = bDatatoOrder(bTCh0);
		bTCh1 = bDatatoOrder(bTCh1);
		bTCh2 = bDatatoOrder(bTCh2);
		bTCh3 = bDatatoOrder(bTCh3);
		bTCh4 = bDatatoOrder(bTCh4);
		bTCh5 = bDatatoOrder(bTCh5);
		bTCh6 = bDatatoOrder(bTCh6);

		if (m_Check1)
		{
			CString order2 = ">CALIB[0]:" + kCh0 + "|" + bCh0 + "|" + kTCh0 + "|" + bTCh0 + "|10000\r\n";
			m_SerialPort.WriteToPort(order2.GetBuffer(order2.GetLength()));

			m_Check1 = FALSE;
			m_Check2 = TRUE;
			UpdateData(FALSE);
		}
		else if (m_Check2)
		{
			CString order2 = ">CALIB[1]:" + kCh1 + "|" + bCh1 + "|" + kTCh1 + "|" + bTCh1 + "|10000\r\n";
			m_SerialPort.WriteToPort(order2.GetBuffer(order2.GetLength()));

			m_Check2 = FALSE;
			m_Check3 = TRUE;
			UpdateData(FALSE);
		}
		else if (m_Check3)
		{
			CString order2 = ">CALIB[2]:" + kCh2 + "|" + bCh2 + "|" + kTCh2 + "|" + bTCh2 + "|10000\r\n";
			m_SerialPort.WriteToPort(order2.GetBuffer(order2.GetLength()));

			m_Check3 = FALSE;
			m_Check4 = TRUE;
			UpdateData(FALSE);
		}
		else if (m_Check4)
		{
			CString order2 = ">CALIB[3]:" + kCh3 + "|" + bCh3 + "|" + kTCh3 + "|" + bTCh3 + "|10000\r\n";
			m_SerialPort.WriteToPort(order2.GetBuffer(order2.GetLength()));

			m_Check4 = FALSE;
			m_Check5 = TRUE;
			UpdateData(FALSE);
		}
		else if (m_Check5)
		{
			CString order2 = ">CALIB[4]:" + kCh4 + "|" + bCh4 + "|" + kTCh4 + "|" + bTCh4 + "|10000\r\n";
			m_SerialPort.WriteToPort(order2.GetBuffer(order2.GetLength()));

			m_Check5 = FALSE;
			m_Check6 = TRUE;
			UpdateData(FALSE);
		}
		else if (m_Check6)
		{
			CString order2 = ">CALIB[5]:" + kCh5 + "|" + bCh5 + "|" + kTCh5 + "|" + bTCh5 + "|10000\r\n";
			m_SerialPort.WriteToPort(order2.GetBuffer(order2.GetLength()));

			m_Check6 = FALSE;
			m_Check7 = TRUE;
			UpdateData(FALSE);
		}
		else if (m_Check7)
		{
			CString order2 = ">CALIB[6]:" + kCh6 + "|" + bCh6 + "|" + kTCh6 + "|" + bTCh6 + "|10000\r\n";
			m_SerialPort.WriteToPort(order2.GetBuffer(order2.GetLength()));

			m_Check7 = FALSE;
			m_Check1 = TRUE;
			UpdateData(FALSE);
		}

		//CString order1(_T(">SHOW_CALIB"));
		//order1 += "\r\n";
		//m_SerialPort.WriteToPort(order1.GetBuffer(order1.GetLength()));
		m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		/*	int nline = m_CtrRichEdit.GetLineCount();
		   m_CtrRichEdit.LineScroll(nline-1);		*/						//滚动置底

	}
}


LRESULT CToolDlg::ByteMessage(WPARAM wParam, LPARAM lParam)
{
	//如果当前连接成功
	if (m_Connected)
	{
		//处理用户自定义消息
		int num = (int)wParam;
		BYTE* byteOrder = (BYTE*)lParam;
		m_SerialPort.WriteToPort(byteOrder, num);

		return 0;
	}
}


LRESULT CToolDlg::OrderMessage(WPARAM wParam, LPARAM lParam)
{
	//如果当前连接成功
	if (m_Connected)
	{
		//处理用户自定义消息
		CString str((LPCTSTR)lParam);
		str += "\r\n";
		m_SerialPort.WriteToPort(str.GetBuffer(str.GetLength()));

		return 0;
	}
}

BOOL CToolDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	//DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;
	switch (nEventType)
	{
	case DBT_DEVICEREMOVECOMPLETE://移除设备
	{
		if (m_Connected)
		{
			SetDlgItemText(IDC_BTN_OPEN_CLOSE_PORT, _T("打开串口"));
			GetDlgItem(IDC_CBO_SERIAL_PORT)->EnableWindow(TRUE);
			GetDlgItem(IDC_CBO_BAUD_RATE)->EnableWindow(TRUE);

			m_SerialPort.ClosePort();
			m_Connected = 0;
		}
		break;
	}
	case DBT_DEVICEARRIVAL://添加设备
		RefreshCom();//刷新组合框的内容
		break;
	default:
		break;
	}
	return TRUE;
}

void CToolDlg::OnBnClickedDefault()
{
	if (m_Connected)
	{
		UpdateData(TRUE);
		CString defaultName;
		GetDlgItem(IDC_BUTTON1)->GetWindowText(defaultName);	//按钮名字								
		CString	idfName = defaultName.Left(1);					//找到按钮的数字
		int i = _ttoi(idfName);	//得到按钮名的通道数字

		CString order2 = _T(">CALIB[") + _T(idfName) + _T("]:10000|+0000|10000|+0000|10000\r\n");
		m_SerialPort.WriteToPort(order2.GetBuffer(order2.GetLength()));

		// TODO: 在此添加控件通知处理程序代码
		if (i < 6)
			i += 1;
		else
			i = 0;
		CString idfName2;
		idfName2.Format("%d", i);
		SetDlgItemText(IDC_BUTTON1, _T(idfName2) + _T("通道设置默认"));

		m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

		switch (i)
		{
		case 0:
			m_Check1 = TRUE;
			m_Check2 = FALSE;
			m_Check3 = FALSE;
			m_Check4 = FALSE;
			m_Check5 = FALSE;
			m_Check6 = FALSE;
			m_Check7 = FALSE;
			break;
		case 1:
			m_Check1 = FALSE;
			m_Check2 = TRUE;
			m_Check3 = FALSE;
			m_Check4 = FALSE;
			m_Check5 = FALSE;
			m_Check6 = FALSE;
			m_Check7 = FALSE;
			break;
		case 2:
			m_Check1 = FALSE;
			m_Check2 = FALSE;
			m_Check3 = TRUE;
			m_Check4 = FALSE;
			m_Check5 = FALSE;
			m_Check6 = FALSE;
			m_Check7 = FALSE;
			break;
		case 3:
			m_Check1 = FALSE;
			m_Check2 = FALSE;
			m_Check3 = FALSE;
			m_Check4 = TRUE;
			m_Check5 = FALSE;
			m_Check6 = FALSE;
			m_Check7 = FALSE;
			break;
		case 4:
			m_Check1 = FALSE;
			m_Check2 = FALSE;
			m_Check3 = FALSE;
			m_Check4 = FALSE;
			m_Check5 = TRUE;
			m_Check6 = FALSE;
			m_Check7 = FALSE;
			break;
		case 5:
			m_Check1 = FALSE;
			m_Check2 = FALSE;
			m_Check3 = FALSE;
			m_Check4 = FALSE;
			m_Check5 = FALSE;
			m_Check6 = TRUE;
			m_Check7 = FALSE;
			break;
		case 6:
			m_Check1 = FALSE;
			m_Check2 = FALSE;
			m_Check3 = FALSE;
			m_Check4 = FALSE;
			m_Check5 = FALSE;
			m_Check6 = FALSE;
			m_Check7 = TRUE;
			break;
		}
		UpdateData(FALSE);
	}
}

CString CToolDlg::kDatatoOrder(CString data)
{
	CString iOrder;
	data.Remove('.');		//从左找到.删除
	iOrder = data.Left(5);	//从左取5位

	return iOrder;
}

CString CToolDlg::bDatatoOrder(CString data)
{
	CString iOrder;		//命令格式
	data.Remove('.');		//找到.删除
	if ('-' == data.GetAt(0))		//当数据第一个符号为负数时候
	{
		iOrder = data.Left(5);		//从左取6位
	}
	else
	{
		CString addFlag("+");
		iOrder = addFlag + data.Left(4);		//从左取5位
	}
	return iOrder;
}


void CToolDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Connected)
	{
		UpdateData(true);
		m_CtrRichEdit.SetSel(-1, -1);
		m_CtrRichEdit.ReplaceSel(CString("\r\n"));

		CString temp;
		temp = ">SHOW_CALIB\r\n";
		m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()));
		m_uSendBytes += temp.GetLength();
	}

}



void CToolDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1))
	{
		SetDlgItemText(IDC_BUTTON1, _T("0通道设置默认"));
		m_Check2 = FALSE;
		//GetDlgItem(IDC_CHECK2)->EnableWindow(false);
		m_Check3 = FALSE;
		m_Check4 = FALSE;
		m_Check5 = FALSE;
		m_Check6 = FALSE;
		m_Check7 = FALSE;

		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(0), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(1), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(2), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(3), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(4), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(5), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(6), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		m_currentSet_List.SetFocus();
	}
	else
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK7)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	/*int nline = m_CtrRichEdit.GetLineCount();
	m_CtrRichEdit.LineScroll(nline-1);		*/						//滚动置底
}


void CToolDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK2))
	{
		SetDlgItemText(IDC_BUTTON1, _T("1通道设置默认"));
		m_Check1 = FALSE;
		m_Check3 = FALSE;
		m_Check4 = FALSE;
		m_Check5 = FALSE;
		m_Check6 = FALSE;
		m_Check7 = FALSE;

		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(0), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(1), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(2), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(3), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(4), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(5), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(6), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(1, LVIS_SELECTED, LVIS_SELECTED);
		m_currentSet_List.SetFocus();
	}
	else
	{

		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK7)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	/*	int nline = m_CtrRichEdit.GetLineCount();
		m_CtrRichEdit.LineScroll(nline-1);	*/							//滚动置底
}


void CToolDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK3))
	{
		SetDlgItemText(IDC_BUTTON1, _T("2通道设置默认"));
		m_Check1 = FALSE;
		m_Check2 = FALSE;
		m_Check4 = FALSE;
		m_Check5 = FALSE;
		m_Check6 = FALSE;
		m_Check7 = FALSE;

		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(0), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(1), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(2), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(3), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(4), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(5), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(6), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(2, LVIS_SELECTED, LVIS_SELECTED);
		m_currentSet_List.SetFocus();
	}
	else
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK7)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	/*	int nline = m_CtrRichEdit.GetLineCount();
		m_CtrRichEdit.LineScroll(nline-1);		*/						//滚动置底
}


void CToolDlg::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK4))
	{
		SetDlgItemText(IDC_BUTTON1, _T("3通道设置默认"));
		m_Check1 = FALSE;
		m_Check2 = FALSE;
		m_Check3 = FALSE;
		m_Check5 = FALSE;
		m_Check6 = FALSE;
		m_Check7 = FALSE;

		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(0), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(1), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(2), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(3), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(4), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(5), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(6), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(3, LVIS_SELECTED, LVIS_SELECTED);
		m_currentSet_List.SetFocus();
	}
	else
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK7)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	/*
		int nline = m_CtrRichEdit.GetLineCount();
		m_CtrRichEdit.LineScroll(nline-1);	*/							//滚动置底
}


void CToolDlg::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK5))
	{
		SetDlgItemText(IDC_BUTTON1, _T("4通道设置默认"));
		m_Check1 = FALSE;
		m_Check2 = FALSE;
		m_Check3 = FALSE;
		m_Check4 = FALSE;
		m_Check6 = FALSE;
		m_Check7 = FALSE;

		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(0), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(1), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(2), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(3), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(4), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(5), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(6), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(4, LVIS_SELECTED, LVIS_SELECTED);
		m_currentSet_List.SetFocus();
	}
	else
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK7)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	/*	int nline = m_CtrRichEdit.GetLineCount();
		m_CtrRichEdit.LineScroll(nline-1);		*/						//滚动置底
}


void CToolDlg::OnBnClickedCheck6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK6))
	{
		SetDlgItemText(IDC_BUTTON1, _T("5通道设置默认"));
		m_Check1 = FALSE;
		m_Check2 = FALSE;
		m_Check3 = FALSE;
		m_Check4 = FALSE;
		m_Check5 = FALSE;
		m_Check7 = FALSE;

		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(0), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(1), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(2), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(3), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(4), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(5), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(6), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(5, LVIS_SELECTED, LVIS_SELECTED);
		m_currentSet_List.SetFocus();
	}
	else
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK7)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	/*	int nline = m_CtrRichEdit.GetLineCount();
		m_CtrRichEdit.LineScroll(nline-1);	*/							//滚动置底
}


void CToolDlg::OnBnClickedCheck7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK7))
	{
		SetDlgItemText(IDC_BUTTON1, _T("6通道设置默认"));
		m_Check1 = FALSE;
		m_Check2 = FALSE;
		m_Check3 = FALSE;
		m_Check4 = FALSE;
		m_Check5 = FALSE;
		m_Check6 = FALSE;

		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(0), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(1), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(2), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(3), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(4), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(5), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(m_currentSet_List.SetSelectionMark(6), 0, LVIS_SELECTED);
		m_currentSet_List.SetItemState(6, LVIS_SELECTED, LVIS_SELECTED);
		m_currentSet_List.SetFocus();
	}
	else
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
	}

	UpdateData(FALSE);
	m_CtrRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);	//滚动置底
}



void CToolDlg::OnEnChangeEditip1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (editIp1.GetLength() > 2)
	{
		editIp1 = editIp1.Right(3);
		GetDlgItem(EditIp2)->SetWindowTextA("");
		GetDlgItem(EditIp2)->SetFocus();
		UpdateData(false);
	}
}


void CToolDlg::OnEnChangeEditip2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (editIp2.GetLength() == 3)
	{
		editIp2 = editIp2.Right(3);
		GetDlgItem(EditIP3)->SetWindowTextA("");
		GetDlgItem(EditIP3)->SetFocus();
		UpdateData(false);
	}
}

void CToolDlg::OnEnChangeEditip3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (editIp3.GetLength() == 3)
	{
		editIp3 = editIp3.Right(3);
		GetDlgItem(EditIP4)->SetWindowTextA("");
		GetDlgItem(EditIP4)->SetFocus();
		UpdateData(false);
	}
}


void CToolDlg::OnEnChangeEditip4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (editIp4.GetLength() > 2)
	{
		editIp4 = editIp4.Right(3);
		GetDlgItem(IDC_EDIT_Port)->SetFocus();
	}
	UpdateData(FALSE);
}


void CToolDlg::OnBnClickedsetipbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Connected)
	{
		CString order1, order2, order3, order4;
		GetDlgItem(EditIP1)->GetWindowTextA(order1);
		GetDlgItem(EditIp2)->GetWindowTextA(order2);
		GetDlgItem(EditIP3)->GetWindowTextA(order3);
		GetDlgItem(EditIP4)->GetWindowTextA(order4);
		CString order = ">DEVICE_IP:" + order1 + "." + order2 + "." + order3 + "." + order4 + "\r\n";
		m_SerialPort.WriteToPort(order.GetBuffer(order.GetLength()));
	}
}


void CToolDlg::OnBnClickedsetportbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Connected)
	{
		CString order1;
		GetDlgItem(IDC_EDIT_Port)->GetWindowTextA(order1);
		CString order = ">DEVICE_PORT:" + order1 + "\r\n";
		m_SerialPort.WriteToPort(order.GetBuffer(order.GetLength()));
	}
}


void CToolDlg::OnEnChangeEditport()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_port.GetLength() > 4)
	{
		m_port = m_port.Left(5);
	}
	UpdateData(FALSE);
}

void CToolDlg::OnNMDblclkList4(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	LVHITTESTINFO info;
	info.pt = pNMItemActivate->ptAction;

	if (m_currentSet_List.SubItemHitTest(&info) != -1)
	{
		CRect rc;

		m_Row = pNMItemActivate->iItem;//获得选中的行
		m_Col = pNMItemActivate->iSubItem;//获得选中列

		int n = m_currentSet_List.GetItemCount();//获取当前一共多少行

		m_currentSet_List.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；
		m_CurrentEdit.SetParent(&m_currentSet_List);//转换坐标为列表框中的坐标
		m_CurrentEdit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_CurrentEdit.SetWindowText(m_currentSet_List.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；
		m_CurrentEdit.ShowWindow(SW_SHOW);//显示Edit控件；
		m_CurrentEdit.SetFocus();//设置Edit焦点
		m_CurrentEdit.ShowCaret();//显示光标
		m_CurrentEdit.SetSel(-1);//将光标移动到最后
		if (m_Row == n - 1)
		{
			m_currentSet_List.InsertItem(m_Row + 1, _T(""));
		}
	}
	*pResult = 0;
}


void CToolDlg::OnNMClickListCurrent(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString tem;
	m_CurrentEdit.GetWindowText(tem); //得到用户输入的新的内容

	m_currentSet_List.SetItemText(m_Row, m_Col, tem); //设置编辑框的新内容
	m_CurrentEdit.ShowWindow(SW_HIDE); //隐藏编辑框

	*pResult = 0;
}


BOOL CToolDlg::ReadWndPosition()
{
	WINDOWPLACEMENT wp;
	CFile file;
	if (!file.Open(_T("wodema.position"), CFile::modeRead))
		return FALSE;
	UINT nByteRead = file.Read(&wp, sizeof(wp));
	if (sizeof(wp) != nByteRead)
		return FALSE;
	if(!::SetWindowPlacement(this->GetSafeHwnd(), &wp))
		return FALSE;
	file.Close();
	return TRUE;
}

BOOL CToolDlg::WriteWndPosition()
{
	WINDOWPLACEMENT wp = { sizeof(wp) };
	::GetWindowPlacement(this->GetSafeHwnd(), &wp);
	CFile file;
	if (!file.Open(_T("wodema.position"), CFile::modeCreate | CFile::modeWrite))
		return FALSE;
	file.Write(&wp, sizeof(wp));
	file.Close();
	return TRUE;
}

BOOL CToolDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	CString baudrateStr, Ip1,Ip2,Ip3,Ip4,portStr;
	GetDlgItem(IDC_CBO_BAUD_RATE)->GetWindowTextA(baudrateStr);
	GetDlgItem(EditIP1)->GetWindowTextA(Ip1);
	GetDlgItem(EditIp2)->GetWindowTextA(Ip2);
	GetDlgItem(EditIP3)->GetWindowTextA(Ip3);
	GetDlgItem(EditIP4)->GetWindowTextA(Ip4);
	GetDlgItem(IDC_EDIT_Port)->GetWindowTextA(portStr);

	//将值写入ini文件
	::WritePrivateProfileString("IDC_CBO_BAUD_RATE", "BundRate", baudrateStr, ".\\Defalut.ini");
	::WritePrivateProfileString("IpAddress", "IP", _T(Ip1+"."+Ip2+"."+Ip3+"."+Ip4), ".\\Defalut.ini");
	::WritePrivateProfileString("Port", "port", _T(portStr), ".\\Defalut.ini");

	WriteWndPosition();

	return CDialog::DestroyWindow();
}


afx_msg LRESULT CToolDlg::OnTochildMessage(WPARAM wParam, LPARAM lParam)
{

	return 0;
}


void CToolDlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
	ShellExecute(NULL, _T("open"), _T(".\\Defalut.ini"), NULL, NULL, SW_SHOWNORMAL);// 下划线的地方可以是网址或者是文件夹的位置，亦或者是文件的路径。
}


void CToolDlg::OnMenuCOrder()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem(IDC_STATIC_ChildArea)->ShowWindow(SW_HIDE);
	m_ChildFrame->ShowWindow(SW_HIDE);

	m_currentSet_List.ShowWindow(SW_SHOW);		//通过隐藏其他控件
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_Cal)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SET)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK7)->ShowWindow(SW_SHOW);
}


void CToolDlg::OnMenuBOrder()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem(IDC_STATIC_ChildArea)->ShowWindow(SW_SHOW);
	m_ChildFrame->ShowWindow(SW_SHOW);

	m_currentSet_List.ShowWindow(SW_HIDE);		//通过隐藏其他控件
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Cal)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SET)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK7)->ShowWindow(SW_HIDE);


	m_ChildFrame->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

}


void CToolDlg::OnTimeSet()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Connected)
	{
		CString str;
		CTime tm = CTime::GetCurrentTime();
		CString nowDateTime = tm.Format(_T("%Y-%m-%d@%H:%M:%S"));
		CString order = _T(">TIME:") + nowDateTime + _T("\r\n");

		m_SerialPort.WriteToPort(order.GetBuffer(order.GetLength()));
	}
}


void CToolDlg::OnMenuShowState()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Connected)
	{
		CString order(">SHOW_STAT\r\n");
		m_SerialPort.WriteToPort(order);
	}
}


void CToolDlg::OnMenuOrder()
{
	// TODO: 在此添加命令处理程序代码
	if (!orderEditDlg->IsWindowVisible())
	{
		orderEditDlg->ShowWindow(SW_SHOW);

	}
	else
		orderEditDlg->ShowWindow(SW_HIDE);
}

void CToolDlg::OnMenuSetDefault()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Connected)
	{
		SetTimer(1, 50, 0);
	}
}


void CToolDlg::OnMenuSaveCache()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Connected)
	{
		CString order = _T(">SAVE\r\n");
		m_SerialPort.WriteToPort(order.GetBuffer(order.GetLength()));
	}
}


void CToolDlg::OnMenuClearReceive()
{
	// TODO: 在此添加命令处理程序代码
	m_CtrRichEdit.SetSel(0, -1);
	m_CtrRichEdit.ReplaceSel("");
}


void CToolDlg::OnMenuAboutDlg()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CAboutDlg aboutDlg;           // 构造对话框类CTipDlg的实例   
	nRes = aboutDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;   
}
