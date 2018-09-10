#include "stdafx.h"
#include "RecordingInfo.h"
#include "vfw.h"


int RecordingInfo::SetUpRecordingDevice(HWND player)
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

	int deviceID = MCIWndGetDeviceID(player);
	int result = mciSendCommand(deviceID, MCI_SET,
		MCI_WAIT
		| MCI_WAVE_SET_FORMATTAG
		| MCI_WAVE_SET_BITSPERSAMPLE
		| MCI_WAVE_SET_CHANNELS
		| MCI_WAVE_SET_SAMPLESPERSEC
		| MCI_WAVE_SET_AVGBYTESPERSEC
		| MCI_WAVE_SET_BLOCKALIGN,
		reinterpret_cast<DWORD_PTR>(&set_parms));

	return result;
}

CString RecordingInfo::GetTime()
{
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

	return a;
}
