
// MFCFuzzyDlg.h : header file
//

#pragma once
#include "tchart1.h"
#include "tchart2.h"
#include "tchart3.h"
#include "tchart4.h"


// CMFCFuzzyDlg dialog
class CMFCFuzzyDlg : public CDialogEx
{
// Construction
public:
	CMFCFuzzyDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCFUZZY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void createFuzzy(int mode, int index, int input[5]);
	tchart1 m_chart1;
	afx_msg void OnBnClickedOk();
	float thresh1[4];
	float m_c2[4][101];
	float g, jarak, h;
	int i, j;
	tchart2 m_chart2;
//	int ec_battery;
//	int ec_ram;
	//Battery
//	float ec_lowbat;
//	float ec_medbat;
//	float ec_highbat;
	//float ec_upanas;
	
	//Ram
//	float ec_lowram;
//	float ec_medram;
//	float ec_highram;
	CListBox lb_minrule;
	CListBox lb_maxrule;
	tchart3 m_chart3;
	tchart4 m_chart4;
	CListBox m_mfo1;
	CString m_out1;
	
	afx_msg void OnBnClickedEvaluasi();
	afx_msg void OnBnClickedDefuzzifikasi();
//	int ec_temper;
//	int ec_humid;
//	float ec_lowhumid;
	float ec_lowtemp;
	float ec_medtemp;
	float ec_hightemp;
//	float ec_lowhumid;
//	float ec_medhumid;
//	float ec_highhumid;
	int ec_temp;
	int ec_volume;
	float ec_lowvolume;
	float ec_medvolume;
	float ec_highvolume;
};
