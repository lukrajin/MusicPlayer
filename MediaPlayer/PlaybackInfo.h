#pragma once
#include "stdafx.h"

#include <list>

class PlaybackInfo {
public:

	enum state{PLAYING,PAUSED,STOPPED,MUTED,UNLOADED,RECORDING};
	enum loadMode{ADD,CHANGE};
	void SetLenght(HWND player);
	CString GetTime(long position);
	CString GetStateCaption(unsigned id);


	CString trackLenght;
	state currentState = UNLOADED;
	state oldState;
	loadMode currentLoadMode = CHANGE;
	std::list<CString> extensions = { _T("mp3"),_T("wma"), _T("wav"),_T("aac"),_T("aif"),_T("aifc"),_T("aiff"),_T("cda"),_T("m4a"),_T("mid"),_T("mp2") };
};