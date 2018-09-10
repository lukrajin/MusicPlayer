
// MediaPlayerDlg.h : header file
//
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MP3TAG.h"
#include <map>
#include <list>
#include "PlaybackInfo.h"
#include "RecordingInfo.h"

#define DELAY 100


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

	CStatic filenameLabel;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void LoadFile(CString filepath);
	int AddPlaylistItem(CString filepath);
	void UpdateTimeCaption();
	CButton btn_Load;
	
	CStatic volumeCaption;
	CListBox playlistCtrl;
	std::map<CString, CString> playlist;
	CString filename;
	CString oldFilename;
	CString caption;
	afx_msg void OnLbnDblclkList1();
	CButton vol_Btn;
	CButton rec_Btn;
	CButton bwd_Btn;
	CButton fws_Btn;
	afx_msg void OnBnClickedVolumebutton();
	long oldVolume=500;
	afx_msg void OnBnClickedFwdbutton();
	void NextTrack();
	afx_msg void OnBnClickedBwdbutton();
	afx_msg void OnBnClickedRecbutton();

	
	CStatic audioImage;
	CStatic mp3Tag_caption;
	MP3TAG mp3Tag;
	int tagTimer = 0;
	PlaybackInfo playbackInfo;
	RecordingInfo rinfo;
	enum Tags{ Title, Artist, Album, Year };
	Tags currentTag;
};
