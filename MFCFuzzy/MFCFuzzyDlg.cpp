
// MFCFuzzyDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCFuzzy.h"
#include "MFCFuzzyDlg.h"
#include "afxdialogex.h"
#include "CSeries.h"
#include "vector"
#include "iostream"
#include "cmath"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//========== INIT VARIABLE =============//
//Input Temperature (Batt) 
int lowTemp[5]	= { 0,0,10,20,60};//30 40 100
int medTemp[5]	= { 10,20,40,50,60};
int highTemp[5]	= { 40,50,60,0,0 };
//int maxbattery[5]	= { 60,70,100,0,0 };

//Input Humidity (Ram)
int lowVolume[5]		= {0,0,30,40,80}; //20 40 100
int medVolume[5]		= {30,40, 50,60,80}; //20 40 60 80 100
int highVolume[5]		= {50,60,80,0,0}; /// 60 80 100


//float hasil[4] = { waktu_sangatpendek[5],waktu_pendek[5],waktu_lumayan[5],waktu_lama[5] };

// CAboutDlg dialog used for App About

float LVolume, MVolume, HVolume		// MF Fuzzi Set 1
, LTemp, MTemp, HTemp				// MF Fuzzi Set 2
, LTempLow, LTempMed, LTempHigh		//List Min Table
, MTempLow, MTempMed, MTempHigh		//List Min Table
, HTempLow, HTempMed, HTempHigh		//List Min Table
, lowDurasi, medDurasi, highDurasi;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCFuzzyDlg dialog

CMFCFuzzyDlg::CMFCFuzzyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCFUZZY_DIALOG, pParent)
	, m_out1(_T(""))
	, ec_temp(0)
	, ec_lowtemp(0)
	, ec_medtemp(0)
	, ec_hightemp(0)
	, ec_volume(0)
	, ec_lowvolume(0)
	, ec_medvolume(0)
	, ec_highvolume(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCFuzzyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, m_chart1);
	DDX_Control(pDX, IDC_TCHART2, m_chart2);
	//  DDX_Text(pDX, IDC_EDIT1, ec_battery);
	//  DDX_Text(pDX, IDC_EDIT2, ec_ram);
	//  DDX_Text(pDX, IDC_EDIT3, ec_lowbat);
	//  DDX_Text(pDX, IDC_EDIT4, ec_medbat);
	//  DDX_Text(pDX, IDC_EDIT5, ec_highbat);
	//DDX_Text(pDX, IDC_EDIT10, ec_upanas);
	//  DDX_Text(pDX, IDC_EDIT6, ec_lowram);
	//  DDX_Text(pDX, IDC_EDIT7, ec_medram);
	//  DDX_Text(pDX, IDC_EDIT8, ec_highram);
	DDX_Control(pDX, IDC_LIST1, lb_minrule);
	DDX_Control(pDX, IDC_LIST2, lb_maxrule);
	DDX_Control(pDX, IDC_TCHART3, m_chart3);
	DDX_Control(pDX, IDC_TCHART4, m_chart4);
	DDX_Control(pDX, IDC_LIST4, m_mfo1);
	DDX_Text(pDX, IDC_EDIT9, m_out1);
	//  DDX_Text(pDX, IDC_EDIT1, ec_temper);
	//  DDX_Text(pDX, IDC_EDIT2, ec_humid);
	//  DDX_Text(pDX, IDC_EDIT3, ec_lowhumid);
	DDX_Text(pDX, IDC_EDIT3, ec_lowtemp);
	DDX_Text(pDX, IDC_EDIT4, ec_medtemp);
	DDX_Text(pDX, IDC_EDIT5, ec_hightemp);
	//  DDX_Text(pDX, IDC_EDIT6, ec_lowhumid);
	//  DDX_Text(pDX, IDC_EDIT7, ec_medhumid);
	//  DDX_Text(pDX, IDC_EDIT8, ec_highhumid);
	DDX_Text(pDX, IDC_EDIT1, ec_temp);
	DDX_Text(pDX, IDC_EDIT2, ec_volume);
	DDX_Text(pDX, IDC_EDIT6, ec_lowvolume);
	DDX_Text(pDX, IDC_EDIT7, ec_medvolume);
	DDX_Text(pDX, IDC_EDIT8, ec_highvolume);
}

BEGIN_MESSAGE_MAP(CMFCFuzzyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCFuzzyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCFuzzyDlg::OnBnClickedEvaluasi)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCFuzzyDlg::OnBnClickedDefuzzifikasi)
END_MESSAGE_MAP()


// CMFCFuzzyDlg message handlers

BOOL CMFCFuzzyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//Derajat Temperature
	createFuzzy(1, 0, lowTemp);
	createFuzzy(1, 1, medTemp);
	createFuzzy(1, 2, highTemp);

	//Jumlah Volume
	createFuzzy(2, 0, lowVolume);
	createFuzzy(2, 1, medVolume);
	createFuzzy(2, 2, highVolume);

	//Output MF Durasi
	for (i = 0; i <= 34; i++) m_c2[0][i] = 1;
	for (i = 35; i <= 45; i++) m_c2[0][i] = (45 - (float)i) / 10;
	for (i = 46; i <= 100; i++) m_c2[0][i] = 0;

	g = 25; jarak = 25; h = 50;
	for (i = 0; i <= 24; i++) m_c2[1][i] = 0;
	for (i = 25; i <= 75; i++) m_c2[1][i] = 1 - (2 * fabs((float)(i - g - jarak)) / h);
	for (i = 76; i <= 100; i++) m_c2[1][i] = 0;

	g = 10; jarak = 40; h = 20;
	//for (i = 0; i <= 39; i++) m_c2[2][i] = 0;
	//for (i = 40; i <= 60; i++) m_c2[2][i] = 1 - (2 * fabs((float)(i - g - jarak)) / h);
	//for (i = 61; i <= 100; i++) m_c2[2][i] = 0;

	for (i = 0; i <= 54; i++) m_c2[2][i] = 0;
	for (i = 55; i <= 65; i++) m_c2[2][i] = (10 - (65 - (float)i)) / 10;
	for (i = 66; i <= 100; i++) m_c2[2][i] = 1;

	for (j = 0; j < 3; j++) {
		for (i = 0; i <= 100; i++) {
			((CSeries)(m_chart3.Series(j))).AddXY(i, m_c2[j][i], NULL, 536870912);
		}
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCFuzzyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCFuzzyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCFuzzyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCFuzzyDlg::createFuzzy(int mode, int index, int input[5]) {
	unsigned long color = 536870912;
	if (mode == 1) {
		((CSeries)m_chart1.Series(index)).AddXY(input[0], 0, NULL, color);
		((CSeries)m_chart1.Series(index)).AddXY(input[1], 1, NULL, color);
		((CSeries)m_chart1.Series(index)).AddXY(input[2], 1, NULL, color);
		((CSeries)m_chart1.Series(index)).AddXY(input[3], 0, NULL, color);
		((CSeries)m_chart1.Series(index)).AddXY(input[4], 0, NULL, color);
	}

	
	else if (mode == 2) {
		((CSeries)m_chart2.Series(index)).AddXY(input[0], 0, NULL, color);
		((CSeries)m_chart2.Series(index)).AddXY(input[1], 1, NULL, color);
		((CSeries)m_chart2.Series(index)).AddXY(input[2], 1, NULL, color);
		((CSeries)m_chart2.Series(index)).AddXY(input[3], 0, NULL, color);
		((CSeries)m_chart2.Series(index)).AddXY(input[4], 0, NULL, color);
	}
}

float fuzzifikasi(int input, int rule[5]) {
	float output;
	float finput = (float)input;

	if (finput < rule[0])
		output = 0;
	else if (finput >= rule[0] && finput < rule[1]) {
		if (rule[1] - rule[0] == 0.0)
			output = 1;
		else
			output = (finput - rule[0]) / (rule[1] - rule[0]);
	}
	else if (finput >= rule[1] && finput <= rule[2]) {
		output = 1;
	}
	else if (finput >= rule[2] && finput <= rule[3]) {
		if (rule[3] - rule[2] == 0.0)
			output = 0;
		else
			output = (rule[3] - finput) / (rule[3] - rule[2]);
	}
	else if (finput > rule[3])
		output = 0;

	return output;
}

float minf(float a, float b) {
	if (a <= b)
		return a;
	else
		return b;
}

float maxf(float a, float b) {
	if (a >= b)
		return a;
	else
		return b;
}

float maxOfArr(float asd[], int length) {

	float maxV = 0;
	for (int i = 0; i < length; i++) {
		if (asd[i] > maxV) {
			maxV = asd[i];
		}
	}
	return maxV;
}


void CMFCFuzzyDlg::OnBnClickedOk()
{
	
	// TODO: Add your control notification handler code here
	UpdateData(true);

	((CSeries)m_chart1.get_aSeries(4)).Clear();
	((CSeries)m_chart1.get_aSeries(4)).AddXY(ec_temp, 0, NULL, 536870912);
	((CSeries)m_chart1.get_aSeries(4)).AddXY(ec_temp, 1, NULL, 536870912);
	((CSeries)m_chart1.get_aSeries(4)).AddXY(ec_temp, 0, NULL, 536870912);
	((CSeries)m_chart2.get_aSeries(3)).Clear();
	((CSeries)m_chart2.get_aSeries(3)).AddXY(ec_volume, 0, NULL, 536870912);
	((CSeries)m_chart2.get_aSeries(3)).AddXY(ec_volume, 1, NULL, 536870912);
	((CSeries)m_chart2.get_aSeries(3)).AddXY(ec_volume, 0, NULL, 536870912);

	//Proses Fuzzifikasi
	ec_lowtemp = LVolume = fuzzifikasi(ec_temp, lowTemp);
	ec_medtemp = MVolume = fuzzifikasi(ec_temp, medTemp);
	ec_hightemp = HVolume = fuzzifikasi(ec_temp, highTemp);
	//ec_upanas = uPanas = fuzzifikasi(ec_battery, highbattery);

	ec_lowvolume = LTemp = fuzzifikasi(ec_volume, lowVolume);
	ec_medvolume = MTemp = fuzzifikasi(ec_volume, medVolume);
	ec_highvolume = HTemp = fuzzifikasi(ec_volume, highVolume);
		
	UpdateData(false);
}


void CMFCFuzzyDlg::OnBnClickedEvaluasi()
{
	
	// TODO: Add your control notification handler code here
	//Proses Rule Evaluation
	// EVALUASI
	UpdateData(true);

	CString str = _T("");
	while (lb_minrule.GetCount() > 0) lb_minrule.DeleteString(0);
	while (lb_maxrule.GetCount() > 0) lb_maxrule.DeleteString(0);

	//Min rule
	LTempLow = minf(HVolume, LTemp);
	LTempMed = minf(HVolume, MTemp);
	LTempHigh = minf(HVolume, HTemp);

	MTempLow = minf(MVolume, LTemp);
	MTempMed = minf(MVolume, MTemp);
	MTempHigh = minf(MVolume, HTemp);

	HTempLow = minf(LVolume, LTemp);
	HTempMed = minf(LVolume, MTemp);
	HTempHigh = minf(LVolume, HTemp);

	str.Format(_T("HTempLow = %.3f"), LTempLow); lb_minrule.AddString(str);
	str.Format(_T("HTempMed = %.3f"), LTempMed); lb_minrule.AddString(str);
	str.Format(_T("HTempHigh = %.3f"), LTempHigh); lb_minrule.AddString(str);

	str.Format(_T("MTempLow = %.3f"), MTempLow); lb_minrule.AddString(str);
	str.Format(_T("MTempMed = %.3f"), MTempMed); lb_minrule.AddString(str);
	str.Format(_T("MTempHigh = %.3f"), MTempHigh); lb_minrule.AddString(str);

	str.Format(_T("LTempLow = %.3f"), HTempLow); lb_minrule.AddString(str);
	str.Format(_T("LTempMed = %.3f"), HTempMed); lb_minrule.AddString(str);
	str.Format(_T("LTempHigh = %.3f"), HTempHigh); lb_minrule.AddString(str);

	//Max Rule
	highDurasi = maxf(maxf(LTempHigh, MTempHigh), HTempHigh);
	str.Format(_T("highVolume = %.3f"), highVolume); lb_maxrule.AddString(str);
	medDurasi = maxf(maxf(LTempMed, MTempMed), HTempMed);
	str.Format(_T("medVolume = %.3f"), medVolume); lb_maxrule.AddString(str);
	lowDurasi = maxf(maxf(LTempLow, MTempLow), HTempLow);
	str.Format(_T("lowVolume = %.3f"), lowVolume); lb_maxrule.AddString(str);
	UpdateData(false);
}


void CMFCFuzzyDlg::OnBnClickedDefuzzifikasi()
{
	// TODO: Add your control notification handler code here
	//Proses Defuzzifikasi
	UpdateData(true);
	thresh1[0] = lowDurasi;
	thresh1[1] = medDurasi;
	thresh1[2] = highDurasi;

	CString mfformat;
	std::vector<CString> row;
	m_mfo1.ResetContent();
	((CSeries)(m_chart4.Series(0))).Clear();

	float ax[101][4], bx[101], cx[4], dx;

	float num = 0, denum = 0, coa = 0;

	for (i = 0; i < 3; i++) {
		for (j = 0; j <= 100; j++) {
			ax[j][i] = std::fmin(m_c2[i][j], thresh1[i]);
		}
	}
	for (i = 0; i <= 100; i++) {
		bx[i] = maxOfArr(ax[i], 3);
		num += (bx[i] * i);
		denum += bx[i];
	}
	coa = num / denum;
	for (i = 0; i <= 100; i++) {
		((CSeries)(m_chart4.Series(0))).AddXY(i, bx[i], NULL, 536870912);// Menggambar Titik Potong
	}

	((CSeries)m_chart4.get_aSeries(1)).Clear();
	((CSeries)m_chart4.get_aSeries(1)).AddXY(coa, 0, NULL, 536870912);
	((CSeries)m_chart4.get_aSeries(1)).AddXY(coa, 1, NULL, 536870912);
	((CSeries)m_chart4.get_aSeries(1)).AddXY(coa, 0, NULL, 536870912);


	row.push_back(L"FastDuration");
	row.push_back(L"medDuration");
	row.push_back(L"SlowDuration");
	//row.push_back(L"highPerformanceest");

	for (i = 0; i < 3; i++) {
		mfformat.Format(L"%d) %s = %f", i + 1, row[i], m_c2[i][int(coa)]);
		m_mfo1.AddString(mfformat);
		cx[i] = m_c2[i][int(coa)];
	}

	UpdateData(false);

	dx = maxOfArr(cx, 3);
	for (i = 0; i < 3; i++) {
		if (dx == cx[i]) {
			mfformat.Format(L"%s %f", row[i], coa);
			SetDlgItemText(IDC_EDIT9, mfformat);
		}
	}
}
