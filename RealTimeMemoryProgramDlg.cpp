
// RealTimeMemoryProgramDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "RealTimeMemoryProgram.h"
#include "RealTimeMemoryProgramDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_MAIN_TRAY    (WM_USER + 1)

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CRealTimeMemoryProgramDlg 대화 상자



CRealTimeMemoryProgramDlg::CRealTimeMemoryProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REALTIMEMEMORYPROGRAM_DIALOG, pParent)
	, m_strEditTotal(_T(""))
	, m_strEditAvailable(_T(""))
	, m_strEditUse(_T(""))
	, m_strSeldrv(_T(""))
	, m_strType(_T(""))
	, m_strLabel(_T(""))
	, m_strFat(_T(""))
	, m_strUsedisk(_T(""))
	, m_strFreedisk(_T(""))
	, m_strAlldisk(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_dDriver = 0;
}

void CRealTimeMemoryProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TOTAL, m_strEditTotal);
	DDX_Text(pDX, IDC_EDIT_AVAILABLE, m_strEditAvailable);
	DDX_Text(pDX, IDC_EDIT_USE, m_strEditUse);
	DDX_Control(pDX, IDC_COMBO_DRIVER, m_ctrlDriver);
	DDX_Text(pDX, IDC_STATIC_SELDRV, m_strSeldrv);
	DDX_Text(pDX, IDC_STATIC_TYPE, m_strType);
	DDX_Text(pDX, IDC_STATIC_LABEL, m_strLabel);
	DDX_Text(pDX, IDC_STATIC_FAT, m_strFat);
	DDX_Text(pDX, IDC_STATIC_USEDISK, m_strUsedisk);
	DDX_Text(pDX, IDC_STATIC_FREEDISK, m_strFreedisk);
	DDX_Text(pDX, IDC_STATIC_ALLDISK, m_strAlldisk);
	DDX_Control(pDX, IDC_LIST_PROCESS, m_ListProcess);
}

BEGIN_MESSAGE_MAP(CRealTimeMemoryProgramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CRealTimeMemoryProgramDlg::OnBnClickedButtonExit)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_DRIVER, &CRealTimeMemoryProgramDlg::OnSelchangeComboDriver)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &CRealTimeMemoryProgramDlg::OnBnClickedButtonPrint)
END_MESSAGE_MAP()


// CRealTimeMemoryProgramDlg 메시지 처리기

BOOL CRealTimeMemoryProgramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetTimer(1, 100, NULL);

	CString strTemp3;
	char szDriver[10] = "";

	m_dDriver = GetLogicalDrives();

	for (int j = 0; j <= 10; j++)
	{
		if (m_dDriver & (1 << j))
		{
			strTemp3.Format("%s Disk", szDriver);
			m_ctrlDriver.AddString(strTemp3);
			sprintf(szDriver, "%c", j + 'A');
		}
	}

	m_strSeldrv = "Selected Disk : ";
	m_strType = "Disk Type : ";
	m_strLabel = "Disk Name : ";
	m_strFat = "File System : ";
	m_strAlldisk = "All Volume : ";
	m_strUsedisk = "Use Volume : ";
	m_strFreedisk = "Free Volume : ";

	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRealTimeMemoryProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRealTimeMemoryProgramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRealTimeMemoryProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRealTimeMemoryProgramDlg::OnBnClickedButtonExit()
{
	OnOK();
}


CString CRealTimeMemoryProgramDlg::Set_ComMa(CString strNum)
{
	CString strTemp;
	int nA = 0;
	int nK = 0;

	nA = strNum.GetLength();
	nK = nA;

	for (int i = 1; i <= nA; i++)
	{
		nK--;
		strTemp += strNum.GetAt(nK);
	}

	int nO = 0;
	nA = nA / 3;

	for (int j = 1; j <= nA; j++)
	{
		if (j == 1)
		{
			strTemp.Insert(j*3,",");
		}
		else
		{
			nO++;
			strTemp.Insert(j * 3 + nO, ",");
		}
	}

	CString strTemp2;
	int z = 0;
	int u = 0;
	z = strTemp.GetLength();
	u = z;

	for (int k = 1; k <= z; k++)
	{
		u--;
		strTemp2 += strTemp.GetAt(u);
	}

	if (0 == strTemp2.Find(",", 0))
	{
		strTemp2.Delete(0, 1);
	}
	
	return strTemp2;
}


void CRealTimeMemoryProgramDlg::Get_MemoryInfo()
{
	MEMORYSTATUS MemInfo;

	MemInfo.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&MemInfo);

	int nMemoryLoad = 0;
	nMemoryLoad = MemInfo.dwMemoryLoad;
	char szMem[10] = "";

	CClientDC dc(this);

	CPen MyPenBlue(PS_SOLID, 1, RGB(0, 0, 255));
	CBrush MyBrushBlue(RGB(0, 0, 255));

	CPen *pOldPenBlue = dc.SelectObject(&MyPenBlue);
	CBrush *pOldBrushBlue = dc.SelectObject(&MyBrushBlue);

	dc.Rectangle(nMemoryLoad + 20, 50, 120, 70);

	dc.SelectObject(pOldPenBlue);
	dc.SelectObject(pOldBrushBlue);

	CPen MyPenRed(PS_SOLID, 1, RGB(255, 0, 0));
	CBrush MyBrushRed(RGB(255, 0, 0));

	CPen *pOldPenRed = dc.SelectObject(&MyPenRed);
	CBrush *pOldBrushRed = dc.SelectObject(&MyBrushRed);

	dc.Rectangle(20, 50, nMemoryLoad + 20, 70);

	dc.SelectObject(pOldPenRed);
	dc.SelectObject(pOldBrushRed);

	sprintf(szMem, "%d%%", nMemoryLoad);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(60, 52, szMem);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.TextOut(30, 32, "Use Memory");

	CString AllMemory;
	AllMemory.Format("%d", MemInfo.dwTotalPhys);
	m_strEditTotal = Set_ComMa(AllMemory);

	CString UseMemory;
	UseMemory.Format("%d", MemInfo.dwTotalPhys - MemInfo.dwAvailPhys);
	m_strEditUse = Set_ComMa(UseMemory);

	CString AvailbleMemory;
	AvailbleMemory.Format("%d", MemInfo.dwAvailPhys);
	m_strEditAvailable = Set_ComMa(AvailbleMemory);

	UpdateData(FALSE);

}

void CRealTimeMemoryProgramDlg::Get_DiskInfo(char *szDrv)
{
	int nType = 0;
	strcat(szDrv, "://\\");
	nType = GetDriveType(szDrv);

	switch (nType)
	{
	case 0:
		m_strType = "Disk Type : Unknown Disk";
		break;
	case 1:
		m_strType = "Disk Type : UnExist Disk";
		break;
	case DRIVE_CDROM:
		m_strType = "Disk Type : CD-ROM";
		break;
	case DRIVE_FIXED:
		m_strType = "Disk Type : Hard Disk";
		break;
	case DRIVE_RAMDISK:
		m_strType = "Disk Type : Ram Disk";
		break;
	case DRIVE_REMOTE:
		m_strType = "Disk Type : Network Connect Disk";
		break;
	case DRIVE_REMOVABLE:
		m_strType = "Disk Type : Floppy Disk";
		break;

	default:
		break;
	}

	char szLabel[30] = "";
	char szFat[30] = "";

	GetVolumeInformation(szDrv, szLabel, sizeof(szLabel) - 1, NULL, NULL, NULL, szFat, sizeof(szFat) - 1);
	m_strLabel.Format("Disk Name : %s", szLabel);
	m_strFat.Format("File System : %s", szFat);

	//디스크 용량
	ULARGE_INTEGER uTotal;
	ULARGE_INTEGER uFree;

	GetDiskFreeSpaceEx(szDrv, NULL, &uTotal, &uFree);

	//전체 용량
	CString strAllVolume;
	strAllVolume.Format("%I64u", uTotal);
	m_strAlldisk = "All Volume : " + Set_ComMa(strAllVolume) + " Byte";

	//남은 용량
	CString strFreeVolume;
	strFreeVolume.Format("%I64u", uFree);
	m_strFreedisk = "Free Volume : " + Set_ComMa(strFreeVolume) + " Byte";

	//사용 용량
	LONGLONG llTotal = 0, llFree = 0, llUse = 0;
	CString strUseVolume;

	llTotal = atoll(strAllVolume);
	llFree = atoll(strFreeVolume);
	llUse = llTotal - llFree;

	strUseVolume.Format("%I64u", llUse);
	m_strUsedisk = "Use Volume : " + Set_ComMa(strUseVolume) + " Byte";

	UpdateData(FALSE);
}

void CRealTimeMemoryProgramDlg::OnTimer(UINT_PTR nIDEvent)
{
	Get_MemoryInfo();
	CDialogEx::OnTimer(nIDEvent);	
}

void CAboutDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	KillTimer(1);
}

void CRealTimeMemoryProgramDlg::OnSelchangeComboDriver()
{
	int nCursel;
	char szDrv[10] = "";

	nCursel = m_ctrlDriver.GetCurSel();

	if (nCursel != 0)
	{
		nCursel += 1;
	}

	if (m_dDriver & (1 << nCursel))
	{
		sprintf(szDrv, "%c", nCursel + 'A');
		m_strSeldrv.Format("Selected Disk : %s Disk", szDrv);
		Get_DiskInfo(szDrv);
	}

	UpdateData(FALSE);
} 

#pragma region 트레이
/*
void CRealTimeMemoryProgramDlg::Create_Tray()
{
NOTIFYICONDATA nid;
ZeroMemory(&nid, sizeof(nid));

nid.cbSize = sizeof(nid);
nid.hWnd = m_hWnd;
nid.uID = IDR_MAINFRAME;
nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
nid.uCallbackMessage = WM_MAIN_TRAY;
nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
_tcscpy_s(nid.szTip, _T("Tray"));

Shell_NotifyIcon(NIM_ADD, &nid);

}

void CRealTimeMemoryProgramDlg::Destroy_Tray()
{
NOTIFYICONDATA nid;
ZeroMemory(&nid, sizeof(nid));

nid.cbSize = sizeof(nid);
nid.hWnd = m_hWnd;
nid.uID = IDR_MAINFRAME;

Shell_NotifyIcon(NIM_DELETE, &nid);

}
*/
#pragma endregion

void CRealTimeMemoryProgramDlg::Get_ProcessInfo()
{
	

}


void CRealTimeMemoryProgramDlg::OnBnClickedButtonPrint()
{
	char szBuff[255] = "";
	int nCount = 0;
	LPSTR lpVariable;
	LPSTR lpValue;

	lpVariable = GetEnvironmentStrings();

	LVITEM Item;
	Item.mask = LVIF_TEXT;

	while (*lpVariable)
	{
		lpValue = strstr(lpVariable + 1, "=");

		if (lpValue)
		{
			*lpValue = '\0';   
			lpValue++;
		}

		Item.iItem = nCount;
		Item.iSubItem = 0;
		Item.pszText = lpVariable;
		m_ListProcess.InsertItem(&Item);

		Item.iSubItem = 1;
		Item.pszText = lpValue;
		m_ListProcess.SetItem(&Item);

		lpVariable = lpVariable + strlen(lpVariable)+1 + strlen(lpValue) + 1;
		
	}
}
