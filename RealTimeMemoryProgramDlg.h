
// RealTimeMemoryProgramDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CRealTimeMemoryProgramDlg ��ȭ ����
class CRealTimeMemoryProgramDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CRealTimeMemoryProgramDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REALTIMEMEMORYPROGRAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
