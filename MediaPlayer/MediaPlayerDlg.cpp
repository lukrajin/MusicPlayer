
// MediaPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MediaPlayer.h"
#include "MediaPlayerDlg.h"
#include "afxdialogex.h"
#include "vfw.h"
#include "resource.h"
#include ".\MediaPlayerDlg.h"
#include <map>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	HWND m_Player;
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


// CMediaPlayerDlg dialog



CMediaPlayerDlg::CMediaPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MEDIAPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMediaPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, PLAY, btn_Play);
	DDX_Control(pDX, PAUSE, btn_Pause);
	DDX_Control(pDX, STOP, btn_Stop);
	DDX_Control(pDX, IDC_SLIDER1, time_Slider);
	DDX_Control(pDX, IDC_VOLUME, volume_slider);
	DDX_Control(pDX, TIME_LABEL, time_Label);
	DDX_Control(pDX, FILENAME, filenameLabel);
	DDX_Control(pDX, LOAD, btn_Load);
	DDX_Control(pDX, VOLUMECAPTION, volumeCaption);
	DDX_Control(pDX, IDC_LIST1, playlistCtrl);
}

BEGIN_MESSAGE_MAP(CMediaPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(PLAY, &CMediaPlayerDlg::OnBnClickedPlay)
	ON_BN_CLICKED(PAUSE, &CMediaPlayerDlg::OnBnClickedPause)
	ON_BN_CLICKED(STOP, &CMediaPlayerDlg::OnBnClickedStop)
	ON_BN_CLICKED(LOAD, &CMediaPlayerDlg::OnBnClickedLoad)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_WM_DROPFILES()
	ON_LBN_DBLCLK(IDC_LIST1, &CMediaPlayerDlg::OnLbnDblclkList1)
END_MESSAGE_MAP()


// CMediaPlayerDlg message handlers

BOOL CMediaPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON4),
		IMAGE_ICON,
		45, 45,
		LR_DEFAULTCOLOR
	);
	SetIcon(hIcn, TRUE);			// Set big icon
	SetIcon(hIcn, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	volume_slider.SetRangeMax(1000);
	volume_slider.SetPos(500);
	


	//HBITMAP hbit = (HBITMAP)LoadImage(NULL,MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP,0, 0,0);
	//image_Control.SetBitmap(hbit);	
	
	btn_Play.ModifyStyle(0, BS_ICON);
	btn_Play.SetIcon(hIcn);

	btn_Stop.SetIcon(hIcn);
	btn_Stop.ModifyStyle(0, BS_ICON);
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON6),
		IMAGE_ICON,
		45, 45, 
		LR_DEFAULTCOLOR
	);
	btn_Stop.SetIcon(hIcn);

	btn_Pause.ModifyStyle(0, BS_ICON);
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON3),
		IMAGE_ICON,
		45, 45, 
		LR_DEFAULTCOLOR
	);
	btn_Pause.SetIcon(hIcn);

	btn_Load.ModifyStyle(0, BS_ICON);
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON2),
		IMAGE_ICON,
		40, 40, 
		LR_DEFAULTCOLOR
	);
	btn_Load.SetIcon(hIcn);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMediaPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMediaPlayerDlg::OnPaint()
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
HCURSOR CMediaPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMediaPlayerDlg::OnBnClickedPlay()
{
	// TODO: Add your control notification handler code here

	MCIWndPlay(m_Player);
	btn_Pause.EnableWindow(true);
	btn_Play.EnableWindow(false);
	btn_Stop.EnableWindow(true);
	caption.Format(_T("Playing: %s"), filename);
	filenameLabel.SetWindowTextW(caption);
	state = PLAYING;
	
}


void CMediaPlayerDlg::OnBnClickedPause()
{
	// TODO: Add your control notification handler code here
	MCIWndPause(m_Player);
	btn_Pause.EnableWindow(false);
	btn_Play.EnableWindow(true);
	caption.Format(_T("Paused: %s"), filename);
	filenameLabel.SetWindowTextW(caption);
	state = PAUSED;
}


void CMediaPlayerDlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
	MCIWndStop(m_Player);
	MCIWndSeek(m_Player, 0);
	btn_Play.EnableWindow(true);
	btn_Stop.EnableWindow(false);
	btn_Pause.EnableWindow(false);
	CString s;
	s.Format(_T("00:00/%s"), lenght);
	time_Label.SetWindowTextW(s);
	time_Slider.SetPos(0);
	caption.Format(_T("Stopped: %s"), filename);
	filenameLabel.SetWindowTextW(caption);
	state = STOPPED;
}


void CMediaPlayerDlg::OnBnClickedLoad()
{
	
	CFileDialog dlgFile(TRUE);
	if (dlgFile.DoModal() == IDOK)
	{
		CString file = dlgFile.GetPathName();
		LoadFile(file);

		
	}
}


void CMediaPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	
	if (pScrollBar == (CScrollBar *)&time_Slider) {
		int value = time_Slider.GetPos();
		
		MCIWndSeek(m_Player, value);
		UpdateTimeCaption();
		MCIWndPlay(m_Player);
		UpdateData(FALSE);
	}
	else if (pScrollBar == (CScrollBar *)&volume_slider) {
		int position = volume_slider.GetPos();
		MCIWndSetVolume(m_Player, position);
		CString s;
		s.Format(_T("%d%s"), position / 10,"%");
		volumeCaption.SetWindowTextW(s);
	

		
	}
	else {
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}
void CMediaPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	UpdateTimeCaption();
	if (state == PLAYING) {
		if (dots == "")
			dots = ".";
		else if (dots == ".")
			dots = "..";
		else if (dots == "..")
			dots = "...";
		else
			dots = "";

		caption.Format(_T("Playing: %s %s"), filename, dots);
		filenameLabel.SetWindowTextW(caption);
	}
	UpdateData(FALSE);
	if (time_Slider.GetPos() == time_Slider.GetRangeMax())
		OnBnClickedStop();
	CDialogEx::OnTimer(nIDEvent);
}




void CMediaPlayerDlg::OnDropFiles(HDROP hDropInfo)
{
	CString sFile;
	DWORD   nBuffer = 0;

	// Get the number of files dropped 
	int nFilesDropped = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	for (int i = 0; i<nFilesDropped; i++)
	{
		// Get the buffer size of the file. 
		nBuffer = DragQueryFile(hDropInfo, i, NULL, 0);

		// Get path and name of the file 
		DragQueryFile(hDropInfo, i, sFile.GetBuffer(nBuffer + 1), nBuffer + 1);
		sFile.ReleaseBuffer();

		LoadFile(sFile);

	}


	CDialogEx::OnDropFiles(hDropInfo);
}

void CMediaPlayerDlg::LoadFile(CString filepath) 
{
	filename = filepath.Mid(filepath.ReverseFind('\\') + 1);
	if (playlist.find(filename) == playlist.end()) {
		playlist[filename] = filepath;
		playlistCtrl.AddString(filename);
	}
	caption.Format(_T("Playing: %s"), filename);
	filenameLabel.SetWindowTextW(caption);
	MCIWndClose(m_Player);
	MCIWndDestroy(m_Player);
	m_Player = MCIWndCreate(GetSafeHwnd(), AfxGetInstanceHandle(),
		WS_CHILD, filepath);
	MCIWndSetVolume(m_Player, volume_slider.GetPos());
	MCIWndPlay(m_Player);
	time_Slider.SetRangeMax(MCIWndGetLength(m_Player));
	SetTimer(1, 1000, NULL);

	int total = MCIWndGetLength(m_Player);
	total = total / 980;
	int minutes = total / 60;
	int seconds = total % 60;

	if (seconds<10 && minutes<10)
		lenght.Format(_T("0%d:0%d"), minutes, seconds);
	else if (seconds<10)
		lenght.Format(_T("%d:0%d"), minutes, seconds);
	else if (minutes<10)
		lenght.Format(_T("0%d:%d"), minutes, seconds);


	btn_Pause.EnableWindow(true);
	btn_Play.EnableWindow(false);
	btn_Stop.EnableWindow(true);
	time_Slider.EnableWindow(true);
	state = PLAYING;
	
	
}

void CMediaPlayerDlg::UpdateTimeCaption() {
	long position = MCIWndGetPosition(m_Player);
	time_Slider.SetPos(position);
	position = position / 980;
	int minutes = position / 60;
	int seconds = position % 60;
	CString a;
	if (seconds<10 && minutes<10)
		a.Format(_T("0%d:0%d/%s"), minutes, seconds, lenght);
	else if (seconds<10)
		a.Format(_T("%d:0%d/%s"), minutes, seconds, lenght);
	else if (minutes<10)
		a.Format(_T("0%d:%d/%s"), minutes, seconds, lenght);
	time_Label.SetWindowTextW(a);
}


void CMediaPlayerDlg::OnLbnDblclkList1()
{
	CString selectedFileName;
	int index;
	index = playlistCtrl.GetCurSel();
	playlistCtrl.GetText(index, selectedFileName);
	LoadFile(playlist.at(selectedFileName));
	caption.Format(_T("Playing: %s"), filename);
	filenameLabel.SetWindowTextW(caption);
	
}
