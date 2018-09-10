#pragma once
#include "stdafx.h"

class RecordingInfo {
public:
	int SetUpRecordingDevice(HWND player);
	long recLenght;
	CString GetTime();

 };
