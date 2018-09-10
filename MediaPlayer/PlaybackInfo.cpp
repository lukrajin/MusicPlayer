#include "stdafx.h"
#include "PlaybackInfo.h"
#include "MediaPlayerDlg.h"
#include "vfw.h"
#include "MediaPlayer.h"
#include "afxdialogex.h"
#include "resource.h"
#include <map>

void PlaybackInfo::SetLenght(HWND player)
{
	int total = MCIWndGetLength(player);
	total = total / 1000;
	int minutes = total / 60;
	int seconds = total % 60;

	if (seconds < 10 && minutes < 10)
		trackLenght.Format(_T("0%d:0%d"), minutes, seconds);
	else if (seconds < 10)
		trackLenght.Format(_T("%d:0%d"), minutes, seconds);
	else if (minutes < 10)
		trackLenght.Format(_T("0%d:%d"), minutes, seconds);
}

CString PlaybackInfo::GetTime(long position)
{
	position = position / 980;
	int minutes = position / 60;
	int seconds = position % 60;
	CString a;
	if (seconds < 10 && minutes < 10)
		a.Format(_T("0%d:0%d/%s"), minutes, seconds, trackLenght);
	else if (seconds < 10)
		a.Format(_T("%d:0%d/%s"), minutes, seconds, trackLenght);
	else if (minutes < 10)
		a.Format(_T("0%d:%d/%s"), minutes, seconds, trackLenght);

	return a;
}

CString PlaybackInfo::GetStateCaption(unsigned id)
{
	TCHAR cap[100];
	LoadString(0, id, cap, 100);

	return cap;
}
