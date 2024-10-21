// CountClockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CountClock.h"
#include "CountClockDlg.h"

//#include "utils.h"
#include "ping.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDT_TIME_COUNT 1024+1
#define IDT_TIME_COUNTER 1024+2
#define IDT_TIME_NOW 1024+3
#define IDT_TIME_COUNTER_1 1024+4   // ��ʱ��1
#define IDT_TIME_COUNTER_2 1024+5   // ��ʱ��2
#define IDT_TIME_COUNTER_3 1024+6   // ��ʱ��3
#define IDT_TIME_COUNTER_4 1024+7   // ��ʱ��4

#define WIN_SHAKE_SLEEP_TIME 50
#define WINDOW_SHAKE_NUM 3
#define TOTAL_COUNT_DOWN 3   // ����ʱ��ʱ��


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCountClockDlg dialog

CCountClockDlg::CCountClockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCountClockDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCountClockDlg)
	m_count = 0;
	m_times = 0;
	m_show = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_show1 = _T("");

	m_extend = false;
	m_show2 = _T("");
	m_show3 = _T("");
	m_show4 = _T("");
}

void CCountClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCountClockDlg)
	DDX_Control(pDX, IDC_BTN_COUNTER, m_btn_countdown);
	DDX_Control(pDX, IDC_COUNT, m_btn_count);
	DDX_Control(pDX, IDC_STATIC_NETWORK, m_network);
	DDX_Control(pDX, IDC_STATIC_NOW, m_now);
	DDX_Control(pDX, IDC_COUNTDOWN, m_countdown);
	DDX_Control(pDX, IDC_DOWN, m_down);
	DDX_Text(pDX, IDC_EDIT1, m_count);
	DDV_MinMaxUInt(pDX, m_count, 0, 9999999);
	DDX_Text(pDX, IDC_TIMES, m_times);
	DDX_Text(pDX, IDC_STATIC_COUNTER, m_show);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_DOWN_1, m_down1);
	//  DDX_Control(pDX, IDC_STATIC_COUNT1, m_down_1_show);
	DDX_Text(pDX, IDC_STATIC_COUNT1, m_show1);
	DDX_Control(pDX, IDC_COMBO_1, m_count_type0);
	DDX_Control(pDX, IDC_COMBO2, m_count_type1);
	DDX_Control(pDX, IDC_BTN_MUTIL, m_btn_extend);
	DDX_Control(pDX, IDC_BTN_COUNT_1, m_btn_counter_1);
	DDX_Control(pDX, IDC_BTN_COUNT_2, m_btn_counter_2);
	DDX_Control(pDX, IDC_COMBO3, m_count_type2);
	DDX_Control(pDX, IDC_DOWN_2, m_down2);
	//  DDX_Control(pDX, IDC_STATIC_COUNT2, m_show2);
	DDX_Text(pDX, IDC_STATIC_COUNT2, m_show2);
	DDX_Control(pDX, IDC_COMBO4, m_count_type3);
	DDX_Text(pDX, IDC_STATIC_COUNT3, m_show3);
	DDX_Control(pDX, IDC_DOWN_3, m_down3);
	DDX_Control(pDX, IDC_BTN_COUNT_3, m_btn_counter_3);
	DDX_Control(pDX, IDC_DOWN_4, m_down4);
	DDX_Text(pDX, IDC_STATIC_COUNT4, m_show4);
	DDX_Control(pDX, IDC_COMBO5, m_count_type4);
	DDX_Control(pDX, IDC_BTN_COUNT_4, m_btn_counter_4);
}

BEGIN_MESSAGE_MAP(CCountClockDlg, CDialog)
	//{{AFX_MSG_MAP(CCountClockDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_COUNT, OnCount)
	ON_BN_CLICKED(IDC_BTN_COUNTER, OnBtnCounter)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_UPDATETIME, OnUpdatetime)
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_DOWN, &CCountClockDlg::OnStnClickedDown)
	ON_EN_CHANGE(IDC_EDIT1, &CCountClockDlg::OnChangeEdit1)
	ON_BN_CLICKED(IDC_BTN_COUNT_1, &CCountClockDlg::OnBnClickedBtnCount1)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_1, &CCountClockDlg::OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTN_MUTIL, &CCountClockDlg::OnBnClickedBtnMutil)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CCountClockDlg::OnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BTN_COUNT_2, &CCountClockDlg::OnBnClickedBtnCount2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CCountClockDlg::OnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BTN_COUNT_3, &CCountClockDlg::OnBnClickedBtnCount3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CCountClockDlg::OnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BTN_COUNT_4, &CCountClockDlg::OnBnClickedBtnCount4)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CCountClockDlg::OnSelchangeCombo5)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCountClockDlg message handlers

BOOL CCountClockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_count = TOTAL_COUNT_DOWN;   // ����ʱ

	m_tp = new CTimepiece();
	m_tp1 = new CTimepiece();
	m_tp2 = new CTimepiece();
	m_tp3 = new CTimepiece();
	m_tp4 = new CTimepiece();

	m_show = m_tp->str();
	m_show1 = m_tp1->str();
	m_show2 = m_tp2->str();
	m_show3 = m_tp3->str();
	m_show4 = m_tp4->str();
	/*
		cHeight������ĸ߶ȡ�
		cWidth������Ŀ�ȡ�
		cEscapement���������б�ǡ�
		cOrientation���������б�ǡ�
		cWeight������Ĵ�ϸ��
		bItalic�������Ƿ�б�塣
		bUnderline�������Ƿ����»��ߡ�
		bStrikeOut�������Ƿ���ɾ���ߡ�
		iCharSet������ʹ�õ��ַ�����
		iOutPrecision��ָ�����ѡ����ʵ����塣
		iClipPrecision������ȷ���ü��ľ��ȡ�
		iQuality����ô����ѡ�����������ϡ�
		iPitchAndFamily�Ǽ���־�����Ա�־��
		pszFaceName����������ơ�

  */
	
	VERIFY(font.CreateFont(
		30,                       // nHeight
		25,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		FW_NORMAL | FW_BOLD,                // nWeight
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("Arial")));            // lpszFacename

	// Do something with the font just created...
	//	CClientDC dc(this);
	//	CFont *def_font = dc.SelectObject(&font);
	
	m_countdown.SetFont(&font);
	CString str;
	str.Format("%02i", 0);
	m_down.SetFont(&font);
	m_down.SetWindowText(str);
	m_countdown.SetFont(&font);
	m_countdown.SetWindowText(str);	
	m_down1.SetFont(&font);
	m_down1.SetWindowText(str);	
	m_down2.SetFont(&font);
	m_down2.SetWindowText(str);
	m_down3.SetFont(&font);
	m_down3.SetWindowText(str);

	m_down4.SetFont(&font);
	m_down4.SetWindowText(str);

	// Done with the font.  Delete the font object.
	//	dc.SelectObject(def_font);

	//ÿ��1����ִ��һ��OnTimer, ��ӡ��ǰʱ��
	SetTimer(IDT_TIME_NOW, 1000, NULL);    

	// ��ʼ������ʱ�ͼ�����
	m_bcountdown = false;
	
	InitCommbox();

	UpdateData(FALSE);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, HWND_TOP, cx/2 - 300/2, cy/2 - 300 /2, 293, 213, SWP_NOZORDER | SWP_NOREPOSITION | SWP_DRAWFRAME | SWP_SHOWWINDOW );//�ı䴰�ڵĳߴ磬λ�ú�Z��
	this->m_btn_extend.SetWindowText(">>");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCountClockDlg::InitCommbox()
{
	CTimepiece::TYPES types;
	for(types = m_tp->MILLSEC; types <= m_tp->MIN; types=(CTimepiece::TYPES)(types + 1))
	{		
		m_count_type0.AddString(m_tp->enumToString(types).c_str());
		m_count_type1.AddString(m_tp->enumToString(types).c_str());
		m_count_type2.AddString(m_tp->enumToString(types).c_str());
		m_count_type3.AddString(m_tp->enumToString(types).c_str());
		m_count_type4.AddString(m_tp->enumToString(types).c_str());
	}
	m_count_type0.SetCurSel(0);
	m_count_type1.SetCurSel(0);
	m_count_type2.SetCurSel(0);
	m_count_type3.SetCurSel(0);
	m_count_type4.SetCurSel(0);
}

void CCountClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
	
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCountClockDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCountClockDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCountClockDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent) 
    { 		
		case IDT_TIME_NOW:
		{
			SYSTEMTIME time;
			GetLocalTime(&time);
			CString str;
			str.Format("%04d/%02d/%02d %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
			m_now.SetWindowText(str);	
			return;
		}
        case IDT_TIME_COUNT: 
            // process the 10-second timer 
			{	
				UpdateCountDown();
				
				return;
			}   
		case IDT_TIME_COUNTER: 
			// process the 10-second timer 
			{				
				m_tp->KeepTime();
				UpdateCounter();
				return;
			}   
		case IDT_TIME_COUNTER_1:
            // process the 10-second timer 
			{				
				m_tp1->KeepTime();
				UpdateCounter();
				return;
			}     
		case IDT_TIME_COUNTER_2:
            // process the 10-second timer 
			{				
				m_tp2->KeepTime();
				UpdateCounter();
				return;
			}  
		case IDT_TIME_COUNTER_3:
            // process the 10-second timer 
			{				
				m_tp3->KeepTime();
				UpdateCounter();
				return;
			} 
		case IDT_TIME_COUNTER_4:
            // process the 10-second timer 
			{				
				m_tp4->KeepTime();
				UpdateCounter();
				return;
			}  
    } 

	CDialog::OnTimer(nIDEvent);
}

void CCountClockDlg::UpdateCounter()
{
	m_show = m_tp->str();
	m_show1 = m_tp1->str();
	m_show2 = m_tp2->str();
	m_show3 = m_tp3->str();
	m_show4 = m_tp4->str();
	UpdateData(false);

	// ���¼�������ʾ	

	CString str;
	str.Format("%02i", 	m_tp->display());
	// ÿ�ּ�ʱ��������ʾ
	m_down.SetWindowText(str);

	str.Format("%02i", 	m_tp1->display());
	// ÿ�ּ�ʱ��������ʾ
	m_down1.SetWindowText(str);

	str.Format("%02i", 	m_tp2->display());
	// ÿ�ּ�ʱ��������ʾ
	m_down2.SetWindowText(str);

	str.Format("%02i", 	m_tp3->display());
	// ÿ�ּ�ʱ��������ʾ
	m_down3.SetWindowText(str);

	str.Format("%02i", 	m_tp4->display());
	// ÿ�ּ�ʱ��������ʾ
	m_down4.SetWindowText(str);
		
}

void CCountClockDlg::UpdateCountDown()
{
	UpdateData(TRUE);
	m_times = m_times + 1;
	if (m_times == 60)
	{
		m_times = 0;
		m_count = m_count - 1;
	}
	if(m_count == 1)
	{
		CString str;
		str.Format("%02i", 60 - m_times);
		m_countdown.SetWindowText(str);				
	}
	if(m_count * 60 - m_times <= 5)
	{
		// ���5s���д��嶶��
		shake();
	}
	if(m_count <= 0)
	{
		CString str;
		str.Format("%02i", 0);
		m_countdown.SetWindowText(str);	
		KillTimer(IDT_TIME_COUNT);	
		
		// ��ʼ��������ʱ
		m_count = m_count_time;
	}
	
	UpdateData(FALSE);
}

void CCountClockDlg::OnCount() 
{
	// TODO: Add your control notification handler code here
	if(m_bcount){
		KillTimer(IDT_TIME_COUNT);
		m_btn_count.SetWindowText("��ʼ");
		m_bcount = false;		
		// ��ʼ��������ʱ
		m_count = m_count_time;
		m_times = 0;

		UpdateData(false);
	}
	else{
		// ���ݳ�ʼ��
		m_times = 0;
		CString str;
		str.Format("%02i", 0);
		m_countdown.SetWindowText(str);	

		SetTimer(IDT_TIME_COUNT, 1000, NULL);
		m_btn_count.SetWindowText("ֹͣ");
		m_bcount = true;
		UpdateData(true);
		m_count_time = m_count;
	}	
}


void CCountClockDlg::OnBtnCounter() 
{
	// TODO: Add your control notification handler code here
	if(m_tp->GetRuntag()){
		KillTimer(IDT_TIME_COUNTER);
		m_btn_countdown.SetWindowText("��ʱ0");
		m_tp->SetRuntag(false);	
	}else{
		// ���ݳ�ʼ��
		m_tp->InitTp();

		UpdateCounter();

		//��ʱֵ���Ժ���Ϊ��λ����
		m_tp->SetId(SetTimer(IDT_TIME_COUNTER, m_tp->GetElapTime(), NULL));    //ÿ��1����ִ��һ��OnTimer
		m_btn_countdown.SetWindowText("ֹͣ");
		m_tp->SetRuntag(true);		
	}   
}

HBRUSH CCountClockDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		switch(pWnd->GetDlgCtrlID())
		{	
			case IDC_COUNTDOWN:
			case IDC_DOWN: 
			case IDC_DOWN_1:
			case IDC_DOWN_3:
				{
					pDC->SetBkColor(RGB(244, 244, 244));
					pDC->SetTextColor(RGB(255, 0, 0));
					pDC->SetBkColor(RGB(244, 244, 244));
					//pDC->SetBkMode(TRANSPARENT);   
					return (HBRUSH)::GetStockObject(NULL_BRUSH);   
				}
			default:
				break;
		}
		
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}


void CCountClockDlg::OnUpdatetime() 
{
	// TODO: Add your control notification handler code here
//	UpdateSysTime();
	pingBaidu();
}

void CCountClockDlg::pingBaidu() 
{
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;
 
    wVersionRequested = MAKEWORD( 1, 1 );
    err = WSAStartup( wVersionRequested, &wsaData );
 
    CPing ping;
    bool bResult = false;
	bResult = ping.Ping("www.baidu.com");
	if (bResult)
	{
		m_network.m_clor = RGB(0, 0, 0);
		m_network.SetWindowText("connected");
	}
	else
	{
		m_network.m_clor = RGB(255, 255, 0);
		m_network.SetWindowText("connectless");
	}
}

void CCountClockDlg::shake() 
{
	// TODO: Add your control notification handler code here
	// ���嶶��
	RECT rect;
    int x, y, nWidth, nHeight;
    GetWindowRect(&rect);
    x = rect.left;
    y = rect.top;
    nWidth = rect.right - x;
    nHeight = rect.bottom - y;
    for (int i = 0; i < WINDOW_SHAKE_NUM; i++)
    {
        MoveWindow(x - 20, y, nWidth, nHeight, TRUE);
        Sleep(WIN_SHAKE_SLEEP_TIME);
        MoveWindow(x - 20, y - 20, nWidth, nHeight, TRUE);
        Sleep(WIN_SHAKE_SLEEP_TIME);
        MoveWindow(x, y - 20, nWidth, nHeight, TRUE);
        Sleep(WIN_SHAKE_SLEEP_TIME);
        MoveWindow(x, y, nWidth, nHeight, TRUE);
        Sleep(WIN_SHAKE_SLEEP_TIME);
    }
}


void CCountClockDlg::OnStnClickedDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCountClockDlg::OnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	m_count_time = m_count;
}


void CCountClockDlg::OnBnClickedBtnCount1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_tp1->GetRuntag()){
		KillTimer(IDT_TIME_COUNTER_1);
		this->m_btn_counter_1.SetWindowText("��ʱ1");
		m_tp1->SetRuntag(false);	
	}else{
		// ���ݳ�ʼ��
		m_tp1->InitTp();

		UpdateCounter();

		//��ʱֵ���Ժ���Ϊ��λ����
		m_tp1->SetId(SetTimer(IDT_TIME_COUNTER_1, m_tp1->GetElapTime(), NULL));    //ÿ��1����ִ��һ��OnTimer
		m_btn_counter_1.SetWindowText("ֹͣ");
		m_tp1->SetRuntag(true);		
	} 
}


void CCountClockDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_tp)
	{
		delete m_tp;
	}
	CDialog::OnClose();
}


void CCountClockDlg::OnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int index = m_count_type0.GetCurSel();
	CString str1;
	int n = m_count_type0.GetLBTextLen(index);
    m_count_type0.GetLBText(index, str1.GetBuffer(n));
    str1.ReleaseBuffer();
	CTimepiece::TYPES type;

	type = m_tp->StringToEnum(str1.GetBuffer(0));
	m_tp->SetType(type);
}


void CCountClockDlg::OnBnClickedBtnMutil()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	expand();
}

// չ��
void CCountClockDlg::expand()
{
	CRect  rect;
	this->GetWindowRect(&rect);
	int width, height;
	if(m_extend)
	{
		// �۵�
		m_btn_extend.SetWindowText(">>");
		m_extend = false;
		width = rect.Width() / 2 + 4;
		height = rect.Height();			
	}
	else
	{
		// չ��
		m_btn_extend.SetWindowText("<<");
		m_extend = true;
		width = (rect.Width() - 4) * 2;
		height = rect.Height();
	}
	::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, width, height, 
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOREPOSITION | SWP_DRAWFRAME | SWP_SHOWWINDOW );//�ı䴰�ڵĳߴ磬λ�ú�Z��
}

void CCountClockDlg::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialog::CalcWindowRect(lpClientRect, nAdjustType);
}


LRESULT CCountClockDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	return CDialog::WindowProc(message, wParam, lParam);
}


int CCountClockDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CCountClockDlg::OnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_count_type1.GetCurSel();
	CString str1;
	int n = m_count_type1.GetLBTextLen(index);
    m_count_type1.GetLBText(index, str1.GetBuffer(n));
    str1.ReleaseBuffer();
	CTimepiece::TYPES type;

	type = m_tp1->StringToEnum(str1.GetBuffer(0));
	m_tp1->SetType(type);
}


void CCountClockDlg::OnBnClickedBtnCount2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_tp2->GetRuntag()){
		KillTimer(IDT_TIME_COUNTER_2);
		this->m_btn_counter_2.SetWindowText("��ʱ2");
		m_tp2->SetRuntag(false);	
	}else{
		// ���ݳ�ʼ��
		m_tp2->InitTp();

		UpdateCounter();

		//��ʱֵ���Ժ���Ϊ��λ����
		m_tp2->SetId(SetTimer(IDT_TIME_COUNTER_2, m_tp2->GetElapTime(), NULL));    //ÿ��1����ִ��һ��OnTimer
		m_btn_counter_2.SetWindowText("ֹͣ");
		m_tp2->SetRuntag(true);		
	} 
}


void CCountClockDlg::OnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_count_type2.GetCurSel();
	CString str1;
	int n = m_count_type2.GetLBTextLen(index);
    m_count_type2.GetLBText(index, str1.GetBuffer(n));
    str1.ReleaseBuffer();
	CTimepiece::TYPES type;

	type = m_tp2->StringToEnum(str1.GetBuffer(0));
	m_tp2->SetType(type);
}


void CCountClockDlg::OnBnClickedBtnCount3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_tp3->GetRuntag()){
		KillTimer(IDT_TIME_COUNTER_3);
		this->m_btn_counter_3.SetWindowText("��ʱ2");
		m_tp3->SetRuntag(false);	
	}else{
		// ���ݳ�ʼ��
		m_tp3->InitTp();

		UpdateCounter();

		//��ʱֵ���Ժ���Ϊ��λ����
		m_tp3->SetId(SetTimer(IDT_TIME_COUNTER_3, m_tp3->GetElapTime(), NULL));    //ÿ��1����ִ��һ��OnTimer
		m_btn_counter_3.SetWindowText("ֹͣ");
		m_tp3->SetRuntag(true);		
	} 
}


void CCountClockDlg::OnSelchangeCombo4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_count_type3.GetCurSel();
	CString str1;
	int n = m_count_type3.GetLBTextLen(index);
    m_count_type3.GetLBText(index, str1.GetBuffer(n));
    str1.ReleaseBuffer();
	CTimepiece::TYPES type;

	type = m_tp3->StringToEnum(str1.GetBuffer(0));
	m_tp3->SetType(type);
}


void CCountClockDlg::OnBnClickedBtnCount4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_tp4->GetRuntag()){
		KillTimer(IDT_TIME_COUNTER_4);
		this->m_btn_counter_4.SetWindowText("��ʱ2");
		m_tp4->SetRuntag(false);	
	}else{
		// ���ݳ�ʼ��
		m_tp4->InitTp();

		UpdateCounter();

		//��ʱֵ���Ժ���Ϊ��λ����
		m_tp4->SetId(SetTimer(IDT_TIME_COUNTER_4, m_tp4->GetElapTime(), NULL));    //ÿ��1����ִ��һ��OnTimer
		m_btn_counter_4.SetWindowText("ֹͣ");
		m_tp4->SetRuntag(true);		
	} 
}


void CCountClockDlg::OnSelchangeCombo5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_count_type4.GetCurSel();
	CString str1;
	int n = m_count_type4.GetLBTextLen(index);
    m_count_type4.GetLBText(index, str1.GetBuffer(n));
    str1.ReleaseBuffer();
	CTimepiece::TYPES type;

	type = m_tp4->StringToEnum(str1.GetBuffer(0));
	m_tp4->SetType(type);
}
