
// RealTimeMemoryProgramDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CRealTimeMemoryProgramDlg 대화 상자
class CRealTimeMemoryProgramDlg : public CDialogEx
{
// 생성입니다.
public:
	CRealTimeMemoryProgramDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REALTIMEMEMORYPROGRAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	CString m_strEditTotal;
	CString m_strEditAvailable;
	CString m_strEditUse;
	CString Set_ComMa(CString strNum);
	void Get_MemoryInfo();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox m_ctrlDriver;
	CString m_strSeldrv;
	CString m_strType;
	CString m_strLabel;
	CString m_strFat;
	CString m_strUsedisk;
	CString m_strFreedisk;
	CString m_strAlldisk;
	DWORD m_dDriver;
	void Get_DiskInfo(char *szDrv);
	//void Create_Tray();
	//void Destroy_Tray();
	afx_msg void OnSelchangeComboDriver();
	afx_msg void OnBnClickedButtonPrint();
	void Get_ProcessInfo();


	CListCtrl m_ListProcess;
};
