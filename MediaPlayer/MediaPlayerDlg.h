
// MediaPlayerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <map>
#define PLAYING 0
#define PAUSED 1
#define STOPPED 2
#define UNLOADED 3
#define ADD 4
#define CHANGE 5
#define MUTED 6
#define RECORDING 7


// CMediaPlayerDlg dialog
class CMediaPlayerDlg : public CDialogEx
{
// Construction
public:
	CMediaPlayerDlg(CWnd* pParent = NULL);	// standard constructor
	HWND m_Player;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEDIAPLAYER_DIALOG };
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
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedLoad();
	
	
	CButton buttonPlay;
	CButton btn_Play;
	CButton btn_Pause;
	CButton btn_Stop;
	CSliderCtrl time_Slider;
	CSliderCtrl volume_slider;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnTimer(UINT_PTR nIDEvent);
	CStatic time_Label;
	CString lenght;

	CStatic filenameLabel;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void LoadFile(CString filepath);
	void UpdateTimeCaption();
	CButton btn_Load;
	
	CStatic volumeCaption;
	CListBox playlistCtrl;
	std::map<CString, CString> playlist;
	int state=UNLOADED;
	CString filename;
	CString caption;
	CString dots;
	int loadMode;
	afx_msg void OnLbnDblclkList1();
	CButton vol_Btn;
	CButton rec_Btn;
	CButton bwd_Btn;
	CButton fws_Btn;
	afx_msg void OnBnClickedVolumebutton();
	long oldVolume;
	afx_msg void OnBnClickedFwdbutton();
	void NextTrack();
	afx_msg void OnBnClickedBwdbutton();
	afx_msg void OnBnClickedRecbutton();
	long recLenght;
};
