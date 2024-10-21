// CountClockDlg.h : header file
//

#if !defined(AFX_COUNTCLOCKDLG_H__F531BDDE_9B2A_46E3_A5E5_5DC0C0DCBE45__INCLUDED_)
#define AFX_COUNTCLOCKDLG_H__F531BDDE_9B2A_46E3_A5E5_5DC0C0DCBE45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCountClockDlg dialog
#include "SkinStatic.h"
#include "Timepiece.h"

class CCountClockDlg : public CDialog
{
// Construction
public:
	CCountClockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCountClockDlg)
	enum { IDD = IDD_COUNTCLOCK_DIALOG };
	CButton	m_btn_countdown;
	CButton	m_btn_count;
	CSkinStatic	m_network;
	CStatic	m_now;
	CStatic	m_countdown;
	CStatic	m_down;
	UINT	m_count;
	UINT	m_count1;
	UINT	m_times;
	CString	m_show;
	bool m_bcountdown;
	bool m_bcount;
	bool m_bcount1;		 // 计时器1运行标签
	UINT m_count_time;   // 保存输入的计时
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountClockDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CTimepiece* m_tp;
	CTimepiece* m_tp1;
	CTimepiece* m_tp2;
	CTimepiece* m_tp3;
	CTimepiece* m_tp4;

	CFont font;

	void UpdateCounter();
	void UpdateCountDown();

	void shake();
	void pingBaidu();

	// Generated message map functions
	//{{AFX_MSG(CCountClockDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCount();
	afx_msg void OnBtnCounter();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnUpdatetime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedDown();
	afx_msg void OnChangeEdit1();
	CStatic m_down1;
	CString m_show1;
	afx_msg void OnBnClickedBtnCount1();
	afx_msg void OnClose();
	CComboBox m_count_type0;
	CComboBox m_count_type1;
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBnClickedBtnMutil();

private:
	bool m_extend;   // 展开标识
	void expand();
	void InitCommbox();

public:
	CButton m_btn_extend;
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CButton m_btn_counter_1;
	afx_msg void OnSelchangeCombo2();
	CButton m_btn_counter_2;
	CComboBox m_count_type2;
	CStatic m_down2;
//	CStatic m_show2;
	afx_msg void OnBnClickedBtnCount2();
	afx_msg void OnSelchangeCombo3();
	CString m_show2;
	CComboBox m_count_type3;
	CString m_show3;
	CStatic m_down3;
	CButton m_btn_counter_3;
	afx_msg void OnBnClickedBtnCount3();
	afx_msg void OnSelchangeCombo4();
	afx_msg void OnBnClickedBtnCount4();
	afx_msg void OnSelchangeCombo5();
	CStatic m_down4;
	CString m_show4;
	CComboBox m_count_type4;
	CButton m_btn_counter_4;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTCLOCKDLG_H__F531BDDE_9B2A_46E3_A5E5_5DC0C0DCBE45__INCLUDED_)

