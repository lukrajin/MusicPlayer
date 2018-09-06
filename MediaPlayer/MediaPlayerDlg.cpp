
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
	DDX_Control(pDX, VOLUMEBUTTON, vol_Btn);
	DDX_Control(pDX, RECBUTTON, rec_Btn);
	DDX_Control(pDX, BWDBUTTON, bwd_Btn);
	DDX_Control(pDX, FWDBUTTON, fws_Btn);
	DDX_Control(pDX, AUDIOIMAGE, audioImage);
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
	ON_BN_CLICKED(VOLUMEBUTTON, &CMediaPlayerDlg::OnBnClickedVolumebutton)
	ON_BN_CLICKED(FWDBUTTON, &CMediaPlayerDlg::OnBnClickedFwdbutton)
	ON_BN_CLICKED(BWDBUTTON, &CMediaPlayerDlg::OnBnClickedBwdbutton)
	ON_BN_CLICKED(RECBUTTON, &CMediaPlayerDlg::OnBnClickedRecbutton)
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
		MAKEINTRESOURCE(IDR_MAINFRAME),
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
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON4),
		IMAGE_ICON,
		45, 45,
		LR_DEFAULTCOLOR
	);
	btn_Play.ModifyStyle(0, BS_ICON);
	btn_Play.SetIcon(hIcn);

	btn_Stop.SetIcon(hIcn);
	btn_Stop.ModifyStyle(0, BS_ICON);
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON6),
		IMAGE_ICON,
		35, 35, 
		LR_DEFAULTCOLOR
	);
	btn_Stop.SetIcon(hIcn);

	btn_Pause.ModifyStyle(0, BS_ICON);
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON3),
		IMAGE_ICON,
		35, 35, 
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

	rec_Btn.ModifyStyle(0, BS_ICON);
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON9),
		IMAGE_ICON,
		40, 40,
		LR_DEFAULTCOLOR
	);
	rec_Btn.SetIcon(hIcn);

	vol_Btn.ModifyStyle(0, BS_ICON);
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON7),
		IMAGE_ICON,
		32, 32,
		LR_DEFAULTCOLOR
	);
	vol_Btn.SetIcon(hIcn);

	fws_Btn.ModifyStyle(0, BS_ICON);
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON,
		35, 35,
		LR_DEFAULTCOLOR
	);

	fws_Btn.SetIcon(hIcn);

	bwd_Btn.ModifyStyle(0, BS_ICON);
	hIcn = (HICON)LoadImage(
		AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDI_ICON10),
		IMAGE_ICON,
		35, 35,
		LR_DEFAULTCOLOR
	);
	bwd_Btn.SetIcon(hIcn);

	audioImage.ModifyStyle(0, SS_BITMAP);
	audioImage.SetBitmap(::LoadBitmap(
		_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(IDB_BITMAP1)));

	CFont *m_FontFileName = new CFont();
	m_FontFileName->CreateFont(22, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Bahnschrift"));
	GetDlgItem(FILENAME)->SetFont(m_FontFileName, TRUE);
	
	CFont *m_FontTime = new CFont();
	m_FontTime->CreatePointFont(90, _T("Bahnschrift"));
	GetDlgItem(TIME_LABEL)->SetFont(m_FontTime, TRUE);
	
	CFont *m_FontVol = new CFont();
	m_FontVol->CreatePointFont(70, _T("Bahnschrift"));
	GetDlgItem(VOLUMECAPTION)->SetFont(m_FontVol, TRUE);
	
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
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		//ScreenToClient(rect);
		BITMAP bmp;
		HBITMAP hBmp = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6));
		::GetObject(hBmp, sizeof(bmp), &bmp);
		HDC hDC = ::CreateCompatibleDC(NULL);
		SelectObject(hDC, hBmp);
		::BitBlt(dc.m_hDC, 0, 0, rect.Width(), rect.Height(), hDC, 0, 0, SRCCOPY);
		CDialog::OnPaint();
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
	if (state == UNLOADED) {
		OnBnClickedLoad();
		return;
	}
	MCIWndPlay(m_Player);
	btn_Pause.EnableWindow(true);
	btn_Play.EnableWindow(false);
	btn_Stop.EnableWindow(true);
	time_Slider.EnableWindow(true);
	
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
	time_Slider.EnableWindow(false);
	if (state == RECORDING) {
		if (MCIWndCanSave(m_Player)) {
			
			audioImage.SetBitmap(::LoadBitmap(
				_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(IDB_BITMAP1)));
			state = UNLOADED;
			btn_Play.EnableWindow(true);
			btn_Stop.EnableWindow(false);
			btn_Load.EnableWindow(true);
			rec_Btn.EnableWindow(true);
			vol_Btn.EnableWindow(true);
			playlistCtrl.EnableWindow(true);
			volume_slider.EnableWindow(true);
			KillTimer(1);
			time_Label.SetWindowTextW(_T("00:00/00:00"));
			caption.Format(_T("File is not loaded"));
			filenameLabel.SetWindowTextW(caption);
			MCIWndStop(m_Player);
			MCIWndSaveDialog(m_Player);
			MCIWndDestroy(m_Player);
			recLenght = 0;
			return;
		}

	}
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
		loadMode = ADD;
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
	
	if (state == RECORDING) {
		++recLenght;
		int minutes = recLenght / 60;
		int seconds = recLenght % 60;
		CString a;
		if (seconds < 10 && minutes < 10)
			a.Format(_T("0%d:0%d"), minutes, seconds);
		else if (seconds < 10)
			a.Format(_T("%d:0%d"), minutes, seconds);
		else if (minutes < 10)
			a.Format(_T("0%d:%d"), minutes, seconds);
		
		time_Label.SetWindowTextW(a);
		return;
	}	

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
	if (time_Slider.GetPos() == time_Slider.GetRangeMax()) {
		NextTrack();
	}
	CDialogEx::OnTimer(nIDEvent);
}




void CMediaPlayerDlg::OnDropFiles(HDROP hDropInfo)
{
	CString sFile;
	DWORD   nBuffer = 0;

	int nFilesDropped = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	for (int i = 0; i<nFilesDropped; i++)
	{
		 
		nBuffer = DragQueryFile(hDropInfo, i, NULL, 0);

		DragQueryFile(hDropInfo, i, sFile.GetBuffer(nBuffer + 1), nBuffer + 1);
		sFile.ReleaseBuffer();
		loadMode = ADD;
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
		UpdateData(false);
	}
	
	if (loadMode == ADD ) {
		if (state == UNLOADED) {
			playlistCtrl.SetCurSel(0);
			CString first;
			playlistCtrl.GetText(0, first);
			filename = first;
			filepath = playlist.at(first);
		}
		else {
			CString current;
			playlistCtrl.GetText(0, current);
			filename = current;
			return;
		}
		
	}
	
	caption.Format(_T("Playing: %s"), filename);
	filenameLabel.SetWindowTextW(caption);
	MCIWndClose(m_Player);
	MCIWndDestroy(m_Player);
	KillTimer(1);
	m_Player = MCIWndCreate(GetSafeHwnd(), AfxGetInstanceHandle(),
		WS_CHILD,filepath);

	MCIWndSetVolume(m_Player, volume_slider.GetPos());
	MCIWndPlay(m_Player);
	time_Slider.SetRangeMax(MCIWndGetLength(m_Player));
	SetTimer(1, 1000, NULL);

	int total = MCIWndGetLength(m_Player);
	total = total / 1000;
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
	fws_Btn.EnableWindow(true);
	bwd_Btn.EnableWindow(true);
	time_Slider.EnableWindow(true);
	state = PLAYING;
	
	
}

void CMediaPlayerDlg::UpdateTimeCaption() {

	long position = MCIWndGetPosition(m_Player);
	if(state!=RECORDING)
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
	loadMode = CHANGE;
	LoadFile(playlist.at(selectedFileName));
	caption.Format(_T("Playing: %s"), filename);
	filenameLabel.SetWindowTextW(caption);
	
}


void CMediaPlayerDlg::OnBnClickedVolumebutton()
{
	
	HICON hIcn;
	if (state == MUTED) {
		CString s;
		s.Format(_T("%d%s"), oldVolume / 10, "%");
		volumeCaption.SetWindowTextW(s);
		volume_slider.EnableWindow(true);
		MCIWndSetVolume(m_Player, oldVolume);
		volume_slider.SetPos(oldVolume);
		vol_Btn.ModifyStyle(0, BS_ICON);
		hIcn = (HICON)LoadImage(
			AfxGetApp()->m_hInstance,
			MAKEINTRESOURCE(IDI_ICON7),
			IMAGE_ICON,
			32, 32,
			LR_DEFAULTCOLOR
		);
		vol_Btn.SetIcon(hIcn);
		state = oldState;
		
	}
	else
	{
		CString s;
		s.Format(_T("%d%s"), 0, "%");
		volumeCaption.SetWindowTextW(s);
		volume_slider.EnableWindow(false);
		oldState = state;
		state = MUTED;
		oldVolume = volume_slider.GetPos();
		MCIWndSetVolume(m_Player, 0);
		vol_Btn.ModifyStyle(0, BS_ICON);
		hIcn = (HICON)LoadImage(
			AfxGetApp()->m_hInstance,
			MAKEINTRESOURCE(IDI_ICON8),
			IMAGE_ICON,
			32, 32,
			LR_DEFAULTCOLOR
		);
		vol_Btn.SetIcon(hIcn);
		volume_slider.SetPos(0);
	}

}


void CMediaPlayerDlg::OnBnClickedFwdbutton()
{
	NextTrack();
}
void CMediaPlayerDlg::NextTrack()
{
	loadMode = CHANGE;
	int currentTrack = playlistCtrl.FindString(-1, filename);
	if (currentTrack + 1 >= playlistCtrl.GetCount())
		OnBnClickedStop();
	else {
		CString next;
		playlistCtrl.SetCurSel(currentTrack + 1);
		playlistCtrl.GetText(currentTrack + 1, next);
		LoadFile(playlist.at(next));
		caption.Format(_T("Playing: %s"), filename);
		filenameLabel.SetWindowTextW(caption);
	}
	
}

void CMediaPlayerDlg::OnBnClickedBwdbutton()
{
	loadMode = CHANGE;
	int currentTrack = playlistCtrl.FindString(-1, filename);
	if (currentTrack - 1 < 0) {

		MCIWndSeek(m_Player, 0);
		OnBnClickedPlay();
	}
	else {
		CString prev;
		playlistCtrl.SetCurSel(currentTrack -1);
		playlistCtrl.GetText(currentTrack - 1, prev);
		LoadFile(playlist.at(prev));
		caption.Format(_T("Playing: %s"), filename);
		filenameLabel.SetWindowTextW(caption);
	}
	
}


void CMediaPlayerDlg::OnBnClickedRecbutton()
{
	MCIWndClose(m_Player);
	MCIWndDestroy(m_Player);
	KillTimer(1);

	m_Player = MCIWndCreate(GetSafeHwnd(), AfxGetInstanceHandle(),
		WS_CHILD | MCIWNDF_RECORD, NULL);

	MCIWndNew(m_Player,_T("waveaudio"));
	SetRecordingDevice();

	playlistCtrl.SetCurSel(-1);
	
	if (MCIWndCanRecord(m_Player))
	{
		
		MCIWndHome(m_Player);
		MCIWndRecord(m_Player);
		audioImage.SetBitmap(::LoadBitmap(
			_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(IDB_BITMAP2)));
		btn_Play.EnableWindow(false);
		btn_Stop.EnableWindow(true);
		btn_Load.EnableWindow(false);
		btn_Pause.EnableWindow(false);
		fws_Btn.EnableWindow(false);
		bwd_Btn.EnableWindow(false);
		rec_Btn.EnableWindow(false);
		vol_Btn.EnableWindow(false);
		volume_slider.EnableWindow(false);
		playlistCtrl.EnableWindow(false);
		state = RECORDING;
		time_Slider.SetPos(0);
		time_Slider.EnableWindow(false);
		caption.Format(_T("Recording..."));
		filenameLabel.SetWindowTextW(caption);
		SetTimer(1, 1000, NULL);
	}
	else
	{
		MessageBoxA(GetSafeHwnd(),
			"This device doesn't record.",
			"Error",
			MB_OK);
		btn_Play.EnableWindow(true);
		btn_Stop.EnableWindow(false);
		btn_Pause.EnableWindow(false);
		fws_Btn.EnableWindow(false);
		bwd_Btn.EnableWindow(false);
		state = UNLOADED;
		time_Label.SetWindowTextW(_T("00:00/00:00"));
		caption.Format(_T("File is not loaded"));
		filenameLabel.SetWindowTextW(caption);
		time_Slider.SetPos(0);
		

	}
}
void CMediaPlayerDlg::SetRecordingDevice() 
{
	MCI_WAVE_SET_PARMS set_parms; 
	set_parms.wFormatTag = WAVE_FORMAT_PCM;
	set_parms.wBitsPerSample = 16;
	set_parms.nChannels = 1;
	set_parms.nSamplesPerSec = 44100;
	set_parms.nBlockAlign = (set_parms.nChannels*set_parms.wBitsPerSample) / 8;
	set_parms.nAvgBytesPerSec = ((set_parms.wBitsPerSample) *
		set_parms.nChannels *
		set_parms.nSamplesPerSec) / 8;
	
	int deviceID = MCIWndGetDeviceID(m_Player);
	int result = mciSendCommandA(deviceID, MCI_SET,
		MCI_WAIT
		| MCI_WAVE_SET_FORMATTAG
		| MCI_WAVE_SET_BITSPERSAMPLE
		| MCI_WAVE_SET_CHANNELS
		| MCI_WAVE_SET_SAMPLESPERSEC
		| MCI_WAVE_SET_AVGBYTESPERSEC
		| MCI_WAVE_SET_BLOCKALIGN,
		(DWORD)(LPVOID)&set_parms);
	if (result) 
	{
		MessageBoxA(NULL, "Failed to set up recording device", "MCI_WAVE_SET_1", MB_OK);
		return;
	}
}
